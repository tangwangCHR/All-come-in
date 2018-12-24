objs =start.o main.o Relocate.o  my_printf.o lib1funcs.o usart.o SDRAM.o led.o interrupt.o exti.o timer.o string_utils.o nor_flash.o nand_flash.o
objs += lcd/s3c2440_lcd_controller.o
objs += lcd/geometry.o
objs += lcd/framebuff.o
objs += lcd/font.o
objs += lcd/lcd.o
objs += lcd/lcd_controller.o
objs += lcd/lcd_test.o
objs += lcd/lcd_4.3.o
objs += lcd/font_8x16.o


all: $(objs)
	arm-linux-ld -T Relocate.lds $^ libgcc.a -o lcd.elf
	arm-linux-objcopy -O binary -S lcd.elf lcd.bin
	arm-linux-objdump -D lcd.elf > lcd.dis
clean:
	rm *.bin *.o *.elf *.dis lcd/*.o
clear:
	rm *.o *.elf lcd/*.o	
%.o : %.c
	arm-linux-gcc -march=armv4t -c -o $@ $<

%.o : %.S
	arm-linux-gcc -march=armv4t -c -o $@ $<

