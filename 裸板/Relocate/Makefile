all:
	arm-linux-gcc -c -o led.o led.c
	arm-linux-gcc -c -o SDRAM.o SDRAM.c
	arm-linux-gcc -c -o uart.o usart.c
	arm-linux-gcc -c -o main.o main.c
	arm-linux-gcc -c -o start.o start.S
	arm-linux-gcc -c -o Relocate.o Relocate.c
	arm-linux-ld -T Relocate.lds start.o Relocate.o led.o uart.o  main.o SDRAM.o -o SDRAM.elf
	arm-linux-objcopy -O binary -S SDRAM.elf SDRAM.bin
	arm-linux-objdump -D SDRAM.elf > SDRAM.dis
clean:
	rm *.bin *.o *.elf *.dis
	
