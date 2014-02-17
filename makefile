CC=clang
CFLAGS=-g -O0 -std=c99 -Wall -Wextra -Werror -I src
LFLAGS=-g -O0 -std=c99 -L obj

all: obj/main.o obj/genetics.o obj/phylogenetics.o
	$(CC) $(LFLAGS) obj/main.o obj/genetics.o obj/phylogenetics.o -o bin/collateral-monk

obj/main.o: src/main.c src/genetics.h src/phylogenetics.h
	$(CC) $(CFLAGS) -c src/main.c -o obj/main.o

obj/genetics.o: src/genetics.c src/genetics.h
	$(CC) $(CFLAGS) -c src/genetics.c -o obj/genetics.o

obj/phylogenetics.o: src/phylogenetics.c src/phylogenetics.h src/genetics.h
	$(CC) $(CFLAGS) -c src/phylogenetics.c -o obj/phylogenetics.o

clean:
	rm -rf obj/*.o
	rm bin/collateral-monk
