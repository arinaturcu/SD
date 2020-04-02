CC=gcc
CFLAGS=-Wall -Wextra -g

build: stack_mod

stack_mod:
	$(CC) $(CFLAGS) main.c ../src/Queue.c ../src/LinkedList.c -o stack_mod
run:
	./stack_mod
clean :
	rm stack_mod
