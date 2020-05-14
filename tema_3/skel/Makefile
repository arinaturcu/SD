CC=gcc
CFLAGS= -g -Wall -Wextra -Wpedantic -m32
PUBL=publications
HASHTABLE=Hashtable
LINKEDLIST=LinkedList
QUEUE=Queue

.PHONY: build clean

build: $(PUBL).o $(HASHTABLE).o $(LINKEDLIST).o $(QUEUE).o

$(LINKEDLIST).o: $(LINKEDLIST).c $(LINKEDLIST).h
	$(CC) $(CFLAGS) $^ -c

$(HASHTABLE).o: $(HASHTABLE).c $(HASHTABLE).h
	$(CC) $(CFLAGS) $^ -c

$(QUEUE).o: $(QUEUE).c $(QUEUE).h
	$(CC) $(CFLAGS) $^ -c

$(PUBL).o: $(PUBL).c $(PUBL).h
	$(CC) $(CFLAGS) $^ -c

clean:
	rm -f *.o *.h.gch
