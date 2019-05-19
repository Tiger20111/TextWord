SRC  = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRC))

COMPILER= gcc
CFLAGS= -std=c89 -Wall -Wextra -pedantic -g

all: editor

clear_style: $(patsubst %.c, %.c.orig, $(SRC)) 	 


editor: $(OBJS)
	gcc -o editor $^

%.o: %.c %.h
	$(COMPILER) $(CFLAGS) -c $<

%.c.orig: %.c
	astyle --style=ansi $<

clean:
	rm -f $(OBJS) editor

.PHONY: clear_style
