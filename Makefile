VPATH = src:example/lander
ASM_SRCS = plot.s
C_SRCS = matrix.c matrix2.c transform.c angle.c toplevel.c render.c
LIB = aline.a

LANDER_SRCS = lander.c
LANDER_OBJS = $(LANDER_SRCS:%.c=%.o)

OBJS = $(ASM_SRCS:%.s=%.o) $(C_SRCS:%.c=%.o)

%.o: %.s
	as6502 --cpu=65c02 --list-file=$(@:%.o=obj/%.lst) -o obj/$@ $<

%.o: %.c
	cc6502 --cpu=65c02 -O2 --list-file=$(@:%.o=obj/%.lst) -o obj/$@ $< -Iinclude -I../goabby/lib/clib/include -I../goaby/nuttx/include

all: $(LIB) lander

$(LIB): $(OBJS)
	(cd obj ; nlib ../$@ $^)

lander: $(LANDER_OBJS)
	(cd obj ; ln6502 ../$@ $^)

clean:
	-rm $(OBJS) $(LIB)
