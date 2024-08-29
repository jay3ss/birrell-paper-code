CC = gcc
OPTS = -Wall -O -Werror
LIBS = -pthread


create_thread:
	$(CC) create_thread.c $(OPTS) -o create_thread $(LIBS)

mutual_exclusion:
	$(CC) mutual_exclusion.c $(OPTS) -o mutual_exclusion $(LIBS) -lm linked_list.c

clean:
	rm -rf create_thread mutual_exclusion