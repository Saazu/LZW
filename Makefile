CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -g3

all: encode

encode: lzw.o hash.o stack.o code.o
	${CC} ${CFLAGS} -o $@ $^ -lm 
	ln -f encode decode

clean: 
	rm -rf *.o