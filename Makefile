VPATH = src
ASM_SRCS = plot.s
C_SRCS = matrix.c matrix2.c shape.c
LIB = aline.a

OBJS = $(ASM_SRCS:%.s=%.o) $(C_SRCS:%.c=%.o)

%.o: %.s
	as6502 --cpu=65c02 --list-file=$(@:%.o=obj/%.lst) -o obj/$@ $<

%.o: %.c
	cc6502 --cpu=65c02 -O2 --list-file=$(@:%.o=obj/%.lst) -o obj/$@ $< -Iinclude -I../goabby/lib/clib/include -I../goaby/nuttx/include

all: $(LIB)

$(LIB): $(OBJS)
	(cd obj ; nlib ../$@ $^)

clean:
	-rm $(OBJS) $(LIB)
