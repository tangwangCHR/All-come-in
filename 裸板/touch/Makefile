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
objs += touch/touch.o
objs += touch/tslib.o

all: $(objs)
	arm-linux-ld -T Relocate.lds $^ libgcc.a -o touch.elf
	arm-linux-objcopy -O binary -S touch.elf touch.bin
	arm-linux-objdump -D touch.elf > touch.dis
clean:
	rm *.bin *.o *.elf *.dis lcd/*.o touch/*.o
clear:
	rm *.o *.elf lcd/*.o touch/*.o	
%.o : %.c
	arm-linux-gcc -march=armv4t -c -o $@ $<

%.o : %.S
	arm-linux-gcc -march=armv4t -c -o $@ $<

