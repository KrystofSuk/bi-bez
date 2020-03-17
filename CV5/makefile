CC = g++
CFLAGS = -g
LDFLAGS = -lcrypto

all: hash stream run
run:
	./hash
	./stream < data.txt
hash: hash.o
	$(CC) -o $@ $< $(LDFLAGS)
stream: stream.o
	$(CC) -o $@ $< $(LDFLAGS)
%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
clear: 
	rm hash.o hash stream stream.o
