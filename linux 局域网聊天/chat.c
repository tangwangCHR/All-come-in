#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <poll.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <netdb.h>
#include <sys/sem.h>
#include <signal.h>



#define username "tangwang"
#define PORT 4321

const char *msg[3] = 
{
	"[online]"username,
	"[offline]"username,
	"[iknow]"username,
};




typedef struct _msg_table
{
	char name[20];
	char IP_ADDR[20];
	int flag;
	struct _msg_table *end;
	
}_msg_table;
_msg_table *bufstart;
_msg_table *bufcur;

#define member  50
#define shmsize (sizeof(_msg_table)*member)

void get_myipaddr(char *buf)
{
	struct addrinfo hints,*res = NULL;
	
	int rc;
	
	memset(&hints,0,sizeof(hints));
	
	hints.ai_flags = AI_CANONNAME;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;
	
	rc = getaddrinfo("172.20.10.6",NULL,&hints,&res);
	if(rc < 0)
	{
			perror("getaddrinfo");
			exit(1);
	}
	else
	{
			strcpy(buf,inet_ntoa( ((struct sockaddr_in *)res->ai_addr)->sin_addr));
	}

}


union semun {
       int              val;    /* Value for SETVAL */
       struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
       unsigned short  *array;  /* Array for GETALL, SETALL */
       struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                /*     (Linux-specific) */
          	 };


int sem_v(int semid)
{
        struct sembuf   semopt;
        semopt.sem_num = 0;
        semopt.sem_op = 1;
        semopt.sem_flg = SEM_UNDO;
        if( semop(semid,&semopt,1) < 0)
        {
                printf("sem_v error!\n");
                exit(0);
        }
        return 0;
}

int sem_p(int semid)
{
        struct sembuf   semopt;
        semopt.sem_num = 0;
        semopt.sem_op = -1;
        semopt.sem_flg = SEM_UNDO;
        if( semop(semid,&semopt,1) < 0)
        {
                printf("sem_p error!\n");
                exit(0);
        }
        return 0;
}
int sem_del(int semid)
{
        union semun semu;
        if( semctl(semid,0,IPC_RMID,semu) < 0 )
        {
                printf("del semctl error!\n");
                exit(1);
        }
        return 0;
}
int sem_init(int semid,int num)
{
        union semun ss;
        ss.val = num;
        if( semctl(semid,0,SETVAL,ss) < 0 )
        {
                printf("init semctl error!\n");
                exit(1);
        }
        return 0;
}

int strsearch(char *src,char dest)
{
	int i=0;
	while(*src)
	{
		if(*src == dest)
		{
			return i;
		}
		i++;
		src++;
	}
	return -1;

}

int extra_strhead(char *msg1)
{
	int i=0,flag=1;
	for(i=0;i<3;i++)
	{
		if(strncmp(msg1,msg[i],6) == 0)
		{
			flag = 0;
			break;
		}

	}

	if (strncmp(msg1,"all:",4) == 0)
	{	
		flag = 0;
		i = 3;
	}
	if(flag)
		i=4;


	return i;

}

int extra_str(char *dest , char *src,int whhd)
{


	switch(whhd)
	{
		case 0: src+=8;break;
		case 1: src+=9;break;
		case 2: src+=7;break;
		case 3: src+=4;break;
		case 4:	 src=src+1+strsearch(src,':');break;
		default : break;

	}
		
	strcpy(dest,src );

}






int deal_strhead(int whhd,char *ms,char *ipaddr, _msg_table * set)
{
	char msg2[40];
	extra_str(msg2,ms,whhd);
	_msg_table * head = bufstart;
//	printf("deal_strhead %s\n",msg2);
	switch(whhd)
	{

		case 0:													//online
		{
			if( strcmp(msg2 ,username) == 0)
			{
				
				bufstart->flag = 1;
				bufstart->end = bufcur;
				strcpy(bufstart->name , username);
				strcpy(bufstart->IP_ADDR, ipaddr);
				return 0;

			}
			else
			{
				while(head <= (bufstart -> end))
				{
					if(strcmp(msg2,head->name) ==0)
					{
						return 6;
					}
					head ++;

				}
				head = bufstart;
				
				if(head->flag < 2)								//中间没位置了
				{
					
					set ++;
					set ->flag = 1;
					head -> end = set;
					strcpy(set->IP_ADDR,ipaddr);
					strcpy(set->name,msg2);
//					printf("none : %s  %s\n",set->name,set->IP_ADDR);
					return 1;
				}
				else											//有位置
				{

					
					while(head <= (bufstart -> end))
					{
						if(head->flag == 0)
						{
							strcpy(head->IP_ADDR,ipaddr);
							strcpy(head->name,msg2);	
							head ->flag = 1;
							bufstart->flag --;
//							printf("have : %s  %s\n",set->name,set->IP_ADDR);
							return 2;
						}
						head++;

					}

				}
				
			}
			
		}


		case 1:											//offline
		{
			while(head <= bufstart->end)	
			{
				if( strcmp(head ->IP_ADDR , ipaddr) == 0 )
				{
					bzero((char *)head,sizeof(_msg_table));
					bufstart->flag++;
					return 3;
				}
				head++;
			}
			return -1;
			
		}


		case 2:										//iknow
		{
			set ++;
			set ->flag = 1;
			head -> end = set;
			strcpy(set->IP_ADDR,ipaddr);
			strcpy(set->name,msg2);
			bufcur++;
			return 4;

		}

		case 3:
		{
			while(head <= bufstart->end)
			{
				if(strcmp(head->IP_ADDR,ipaddr) == 0)
					break;
				head++;
			}
			
			printf("%s: %s\n",head->name,msg2);
			return 5;

		}

		case 4:
		{
			while(head <= bufstart->end)
			{
				if(strcmp(head->IP_ADDR,ipaddr) == 0)
					break;
				head++;
			}
			
			printf("%s: %s\n",head->name,msg2);
			return 5;

		}

		default : break;


	}


	return 0;
}




int main()
{
	int shmid,semid;
	int pipe_fd[2];
	pid_t i;
	shmid = shmget( ftok(".",'a'),shmsize,IPC_CREAT|0666);
	if(shmid < 0)
	{
		perror("shmget");
		exit(0);
	}

	semid = semget(ftok(".",'b'),1,IPC_CREAT|0666);
	sem_init(semid,0);

	if (pipe(pipe_fd) < 0)
	{
		perror("pipe");
		exit(1);
	}

	i=fork();
	if(i < 0)
	{
		perror("fork");
		exit(1);
	}
	else if( !i )		//子进程
	{
	
		struct pollfd pollfds;

		close(pipe_fd[0]);				//子进程关闭读
		
		struct sockaddr_in addrto;
		bzero(&addrto,sizeof(struct sockaddr_in));
		addrto.sin_family=AF_INET;
		addrto.sin_addr.s_addr=htonl(INADDR_ANY);
		addrto.sin_port=htons(PORT);
		socklen_t len=sizeof(addrto);

		char *bufaddr = shmat(shmid,0 ,0);		//可读可写
		if(bufaddr == (void *)-1)
		{
			perror("shmat");
			exit(1);

		}
		bzero(bufaddr,shmsize);
		bufstart = (_msg_table *)bufaddr;
		bufcur = (_msg_table *)bufaddr;
		
		char msg1[100];
//		get_myipaddr(msg1);


		
		int sock = -1;
		sock = socket(AF_INET,SOCK_DGRAM,0);
		if(sock < 0)
		{
				perror("socket");
				exit(0);
		}
		
		int i = 1;/* 允许重复使用本地地址与套接字进行绑定 */
		setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(i));
		
		if(bind(sock,(struct sockaddr*)&(addrto),len)==-1)
		{
				perror("bind");
				exit(1);
		}
		pollfds.fd = sock;
		pollfds.events = POLLIN;
		
		sem_v(semid);				//释放信号量
		close(0);					//关闭标准输入
		
		int ret,whhead=-1;
		char ipbuf[40];
		while(1)
		{

			 	ret = poll(&pollfds, 1 , 1000);
				if(ret > 0)
				{
					 bzero(msg1,100);
					 int ret=recvfrom(sock,msg1,100,0,(struct sockaddr*)&addrto,&len);
//					 printf("recv: %s\n",msg1);
					 
										
					 if(ret <= 0)
					 {
					
							printf("read error\n");
					 }
					 else
					 {

							inet_ntop(AF_INET , &(addrto.sin_addr.s_addr), ipbuf ,40);
							ret = deal_strhead(extra_strhead(msg1),msg1, ipbuf, bufcur);
//							printf("ret1= %d\n",ret);
							if(ret == 1 )
							{
								bufcur++;
//								printf("test\n");
								write(pipe_fd[1],ipbuf,40);
//								printf("ret2 = %d  %d\n",ret,strlen(msg[2]));
								if(ret < 0)
									printf("error!\n");
											
							}
							if(ret == 6)
							{
								write(pipe_fd[1],ipbuf,40);
								if(ret < 0)
									printf("error!\n");

							}
					
					 }
					
				}		

		}

		

	}
	else				//主进程
	{
//		char masg[1024];
		int matcharnum=0;


		sem_p(semid);

		close(pipe_fd[1]);				//父进程关闭写

		struct pollfd pollfds[2];
		
		struct hostent *host;
		
		struct sockaddr_in addrto,serv_addr;
		bzero(&addrto,sizeof(struct sockaddr_in));
		addrto.sin_family=AF_INET;
		addrto.sin_addr.s_addr=htonl(INADDR_BROADCAST);
		addrto.sin_port=htons(PORT);
		socklen_t len=sizeof(addrto);

		bzero(&serv_addr,sizeof(struct sockaddr_in));
		serv_addr.sin_family=AF_INET;
		serv_addr.sin_port=htons(PORT);
		socklen_t len1=sizeof(addrto);



		

		char *bufaddr = shmat(shmid,0,SHM_RDONLY);		//可读
		if(bufaddr == (void *)-1)
		{
			perror("shmat");
			exit(1);

		}
		bufstart = (_msg_table *)bufaddr;
		bufcur = (_msg_table *)bufaddr;

		int BROAD_sockfd = -1;
		BROAD_sockfd = socket(AF_INET,SOCK_DGRAM,0);
		if(BROAD_sockfd < 0)
		{
			perror("socket");
			exit(0);
		}

		int send_sockfd = -1;
		send_sockfd = socket(AF_INET,SOCK_DGRAM,0);
		if(send_sockfd < 0)
		{
			perror("socket");
			exit(0);
		}		

		const int opt = 1;
		if(setsockopt(BROAD_sockfd,SOL_SOCKET,SO_BROADCAST,(char*)&opt,sizeof(opt)) < 0)
		{
			perror("setsockopt");
			exit(1);
		}


		int ret=sendto(BROAD_sockfd,msg[0],strlen(msg[0]),0,(struct sockaddr*)&addrto,len);
		if( ret < 0)
		{
			printf("send error!\n");
		}

		pollfds[0].fd = 0;
		pollfds[0].events = POLLIN;
		pollfds[1].fd = pipe_fd[0];
		pollfds[1].events = POLLIN;
		char inbuf[100];
		char *stinbuf;
		char *machar;
		char pipeipbuf[40];
		_msg_table *head = bufstart;
		_msg_table *p2p = NULL;
		char matchr[20];
		while(1)
		{
			ret = poll(pollfds, 2 , 3000);
			if(ret > 0)
			{
					if(pollfds[0].revents)
					{
						 bzero(inbuf,100);
						 bzero(matchr,20);
						 fgets(inbuf , 100 , stdin);
//						 printf("%s\n",inbuf);
						 if(strncmp(inbuf,"menu",4) == 0)
						 {
						 	ret = 0;
//						 	printf("menu :ret = %d\n",ret);
						
						 }
						 if(strncmp(inbuf,msg[1],strlen(msg[1])-1) == 0)			//offline
						 {
						 	ret = 2;
//							printf("offline :ret = %d\n",ret);
						 }

						 if(strncmp(inbuf,"all:",4) == 0)
						 {
						 	stinbuf = inbuf;
							ret=3;
//							printf("all :ret = %d\n",ret);

						 }


						machar = inbuf;
						matcharnum = strsearch(inbuf,':');
						
						
						

						if(matcharnum>=0)
						{
							machar += matcharnum;
							strncpy(matchr,inbuf,matcharnum);
							while(head <= bufstart->end)
							{
								if(strncmp(head->name,matchr,matcharnum) == 0)
								{
									ret=4;
									p2p = head;
									
									break;

								}

								if(strncmp(head->IP_ADDR,matchr,matcharnum) == 0)
								{
									ret=4;
									p2p = head;									
									break;

								}
								head++;

							}

													

						}
						 

						
						 
						 switch(ret)
						 {
								case 0:
								{
									head = bufstart;
									while(head <= bufstart->end)
									{
										if(head->flag)
										{
											printf("name :%s  IP:%s\n",head->name,head->IP_ADDR);

										}
										head++;
									}

									ret = -1;
									head = bufstart;
									break;
								}

								case 2:						//offline
								{
									int ret=sendto(BROAD_sockfd,msg[1],strlen(msg[1]),0,(struct sockaddr*)&addrto,len);
									if( ret < 0)
									{
										perror("sendto");
									}

									kill(i,SIGKILL);
									exit(1);


								}

								case 3:
								{
									int ret=sendto(BROAD_sockfd,stinbuf,strlen(stinbuf),0,(struct sockaddr*)&addrto,len);
									
									if( ret < 0)
									{
										perror("sendto");
									}
									break;

								}

								case 4:
								{
									if( (host = gethostbyname( p2p->IP_ADDR)) ==NULL )
									{
											perror( "gethostbyname");
											exit(1);
									}
									
									serv_addr.sin_addr = *( (struct in_addr *)host->h_addr);
									if( sendto(send_sockfd,inbuf,strlen(inbuf),0, (struct sockaddr*)& serv_addr, len1) < 0)
							        {
							                perror("send");
							                exit(1);
							        }
									break;

								}

								default :break;

						 }


						
					}



					if(pollfds[1].revents)
					{
						read(pipe_fd[0], pipeipbuf, 40);
						if( (host = gethostbyname( pipeipbuf)) ==NULL )
						{
								perror( "gethostbyname");
								exit(1);
						}
						
						serv_addr.sin_addr = *( (struct in_addr *)host->h_addr);
						if( sendto(send_sockfd,msg[2],strlen(msg[2]),0, (struct sockaddr*)& serv_addr, len1) < 0)
				        {
				                perror("send");
				                exit(1);
				        }


					}


					
				}



		}
		

	}





}
























