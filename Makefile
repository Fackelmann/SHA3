all: sha3

sha3: round.o keccak_f.o
	gcc round.o keccak_f.o -o sha3

round.o: round.c
	gcc -c round.c -std=c99 -Wall

keccak_f.o: keccak_f.c
	gcc -c keccak_f.c -std=c99 -Wall

clean:
	rm -rf *o sha3