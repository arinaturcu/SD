CC = gcc
CFLAGS = -Wall -g

.PHONY:
all:	treap
	
run:	treap
	./treap

treap:	src/main.c src/treap.c
	$(CC) $(CFLAGS) -o $@ $^

.PHONY:
clean:
	-rm treap
