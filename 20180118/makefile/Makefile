SOURCES:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,$(SOURCES))
main:$(OBJS)
	gcc $^ -o $@
.PHONY:clean
	clean -f rm $(OBJS)

