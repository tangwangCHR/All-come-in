all:
	arm-linux-gcc -c -o led.o led.c
	arm-linux-gcc -c -o SDRAM.o SDRAM.c
	arm-linux-gcc -c -o uart.o usart.c
	arm-linux-gcc -c -o lib1funcs.o lib1funcs.S
	arm-linux-gcc -c -o my_printf.o my_printf.c
	arm-linux-gcc -c -o main.o main.c
	arm-linux-gcc -c -o start.o start.S
	arm-linux-ld -Ttext 0  -Tdata 0xf00 start.o led.o uart.o lib1funcs.o my_printf.o main.o SDRAM.o -o SDRAM.elf
	arm-linux-objcopy -O binary -S SDRAM.elf SDRAM.bin
	arm-linux-objdump -D SDRAM.elf > SDRAM.dis
clean:
	rm *.bin *.o *.elf *.dis
	
