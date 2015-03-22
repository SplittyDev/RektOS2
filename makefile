SRCS	= $(shell find -name '*.[cS]')
OBJS	= $(addsuffix .o, $(basename $(SRCS)))

CC = i686-elf-gcc
LD = i686-elf-ld

ASFLAGS	=
CFLAGS	= -ffreestanding -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -lgcc
LDFLAGS	= -T kernel.ld
INFLAGS = -I includes -I io -I hal

kernel:	$(OBJS)
		$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
		$(CC) $(CFLAGS) $(INFLAGS) -c -o $@ $^

%.o: %.S
		$(CC) $(ASFLAGS) -c -o $@ $^

clean:
		rm $(OBJS)

.PHONY: clean
