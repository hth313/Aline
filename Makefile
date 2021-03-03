VPATH = src:example/lander
ASM_SRCS = plot.s
C_SRCS = angle.c matrix.c matrix2.c transform.c angle.c toplevel.c render.c
LIB = aline.a

LANDER_SRCS = lander.c
LANDER_OBJS = $(LANDER_SRCS:%.c=obj/%.o)

OBJS = $(ASM_SRCS:%.s=obj/%.o) $(C_SRCS:%.c=obj/%.o)

obj/%.o: %.s
	as6502 --core=65c02 --target=x16 --list-file=$(@:%.o=%.lst) -o $@ $<

obj/%.o: %.c
	cc6502 --core=65c02 --target=x16 -O2 --list-file=$(@:%.o=%.lst) -o $@ $< -Iinclude

all: $(LIB) lander

$(LIB): $(OBJS)
	nlib $@ $^

lander: $(LANDER_OBJS) $(LIB)
	ln6502 --target=x16 --list-file=lander.lst --cross-reference -o $@ $^ x16.scm lib65c02.a module/retrolib/x16.a --rtattr exit=simplified --output-format prg

clean:
	-rm $(OBJS) $(LIB) $(LANDER_OBJS) lander
