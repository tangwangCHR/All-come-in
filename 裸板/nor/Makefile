objs =start.o main.o Relocate.o  my_printf.o lib1funcs.o usart.o SDRAM.o led.o interrupt.o exti.o timer.o string_utils.o nor_flash.o

deq_files := $(patsubst %,.%.d,$(objs))
deq_files := $(wildcard $(deq_files))
CFLAGS = -Werror


all: $(objs)
	arm-linux-ld -T Relocate.lds $^ -o nor.elf
	arm-linux-objcopy -O binary -S nor.elf nor.bin
	arm-linux-objdump -D nor.elf > nor.dis

ifneq ($(deq_files),)
include $(deq_files)
endif	
	


%.o : %.c
	arm-linux-gcc -march=armv4t -c -o $@ $< -MD -MF .$@.d
%.o : %.S
	arm-linux-gcc -march=armv4t -c -o $@ $<

clean:
	rm *.bin *.o *.elf *.dis $(deq_files)
distclean:
.PHONY:clean

clear:
	rm *.o *.elf $(deq_files)