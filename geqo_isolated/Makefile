CC=gcc
CFLAGS=-O2 -Wall

SRCS=src/main.c src/geqo_main.c src/geqo_eval.c src/geqo_pool.c
OBJS=$(SRCS:.c=.o)

geqo: $(SRCS)
	$(CC) $(CFLAGS) -o $@ $(SRCS)

clean:
	rm -f geqo
