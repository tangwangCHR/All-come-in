objs =start.o main.o Relocate.o  my_printf.o lib1funcs.o usart.o SDRAM.o led.o interrupt.o exti.o timer.o

deq_files := $(patsubst %,.%.d,$(objs))
deq_files := $(wildcard $(deq_files))
CFLAGS = -Werror


all: $(objs)
	arm-linux-ld -T Relocate.lds $^ -o timer.elf
	arm-linux-objcopy -O binary -S timer.elf timer.bin
	arm-linux-objdump -D timer.elf > timer.dis

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