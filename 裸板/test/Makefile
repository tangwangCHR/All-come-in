objs = main.o a.o b.o c.o

deq_files := $(patsubst %,.%.d,$(objs))
deq_files := $(wildcard $(deq_files))


CFLAGS = -Werror

test: $(objs)
	gcc -o $@ $^

ifneq ($(deq_files),)
include $(deq_files)
endif


%.o: %.c
	gcc $(CFLAGS) -c -o $@ $< -MD -MF .$@.d
	

clean:
	rm *.o test
distclean:

.PHONY:clean 


