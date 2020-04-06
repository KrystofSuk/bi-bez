CC = g++
CFLAGS = -g
LDFLAGS = -lcrypto

all: aes_encryptor aes_decryptor run
run:
	./aes_encryptor "Mad_scientist"
	./aes_decryptor "Mad_scientist_cbc" "cbc"
	./aes_decryptor "Mad_scientist_ecb" "ecb"
aes_encryptor: aes_encryptor.o
	$(CC) -o $@ $< $(LDFLAGS)
aes_decryptor: aes_decryptor.o
	$(CC) -o $@ $< $(LDFLAGS)
%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
clear: 
	rm aes_encryptor.o aes_encryptor aes_decryptor.o aes_decryptor Mad_scientist_cbc.bmp Mad_scientist_ecb.bmp Mad_scientist_cbc_dec.bmp Mad_scientist_ecb_dec.bmp
