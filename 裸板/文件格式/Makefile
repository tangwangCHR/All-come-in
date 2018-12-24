objs = USER/start.o
objs += USER/main.o 

objs += led/led.o

objs += usart/usart.o

objs +=	printf/my_printf.o
objs +=	printf/lib1funcs.o

objs += SDRAM/SDRAM.o

objs += Relocate/Relocate.o

onjs += interrupt/interrupt.o

deq_files := $(patsubst %,.%.d,$(objs))
deq_files := $(wildcard $(deq_files))
CFLAGS = -Werror


all: $(objs)
	arm-linux-ld -T Relocate/Relocate.lds $^ libgcc.a -o OBJ/swi.elf
	arm-linux-objcopy -O binary -S OBJ/swi.elf OBJ/swi.bin
	arm-linux-objdump -D OBJ/swi.elf > OBJ/swi.dis

ifneq ($(deq_files),)
include $(deq_files)
endif	
	


%.o : %.c
	arm-linux-gcc -c -o $@ $< -MD -MF .$@.d
%.o : %.S
	arm-linux-gcc -c -o $@ $<

clean:
	rm *.bin *.o *.elf *.dis $(deq_files)
distclean:
.PHONY:clean

clear:
	rm *.o *.elf $(deq_files)