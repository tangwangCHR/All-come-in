all:
	arm-linux-gcc -c -o led.o led.c
	arm-linux-gcc -c -o usart.o usart.c
	arm-linux-gcc -c -o start.o start.S
	arm-linux-gcc -c -o main.o main.c
	
	arm-linux-ld -Ttext 0 start.o  main.o led.o usart.o -o usart.elf
	arm-linux-objcopy -O binary -S usart.elf usart.bin
	arm-linux-objdump -D usart.elf > usart.dis
clean:
	rm *.bin *.o *.elf *.dis
	
