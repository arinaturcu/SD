.PHONY: build clean

build: freq hash

freq: freq.c
	gcc -std=c11 -o $@ -Wall -Wextra $<

hash: hash.c
	gcc -std=c11 -g -Wall -Wextra hash.c hash_utils.c -o hash

clean:
	rm freq
	rm hash
