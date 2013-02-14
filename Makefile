all: sha3

sha3: round.o keccak_f.o sponge.o main.o
	gcc round.o keccak_f.o sponge.o main.o -o sha3.out -g

round.o: round.c
	gcc -c round.c -std=c99 -Wall -g

keccak_f.o: keccak_f.c
	gcc -c keccak_f.c -std=c99 -Wall -g

sponge.o: sponge.c
	gcc -c sponge.c -std=c99 -Wall -g

main.o: main.c
	gcc -c main.c -std=c99 -Wall -g

clean:
	rm -rf *o sha3