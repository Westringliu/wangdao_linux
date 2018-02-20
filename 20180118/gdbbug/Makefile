SOURCES:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,$(SOURCES))
CFLAGS:= -g -Wall
main:$(OBJS)
	gcc $^ -o $@
.PHONY:clean
	clean -f rm $(OBJS)
