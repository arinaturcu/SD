CC=gcc
CFLAGS=-Wall -Wextra -std=c99

TARGETS=tema1

build:$(TARGETS)

tema1:
	$(CC) $(CFLAGS) -g playlist.c commands.c playlist_utils.c -o tema1

run:$(TARGETS)
	./tema1 media.in media.out

pack:
	zip -FSr 313CA_ArinaEmanuelaTurcu_Tema1.zip README.txt Makefile *.c *.h

clean:
	rm -f $(TARGETS) media.out