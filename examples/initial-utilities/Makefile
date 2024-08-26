SRCS = jcat.c
TARG = bin/jcat

CC = gcc
OPTS = -Wall -O -Werror
LIBS = -lm


jcat: $(OBJS)
	$(CC) $(SRCS) $(OPTS) -o $(TARG) $(LIBS)

clean:
	rm -rf $(TARG)