CC=clang
CFLAGS=-g -O0 -std=c99 -Wall -Wextra -Werror -I src
LFLAGS=-g -O0 -std=c99 -L obj

all: obj/main.o obj/genetics.o
	$(CC) $(LFLAGS) obj/main.o obj/genetics.o -o bin/collateral-monk

obj/main.o: src/main.c src/genetics.h
	$(CC) $(CFLAGS) -c src/main.c -o obj/main.o

obj/genetics.o: src/genetics.c src/genetics.h
	$(CC) $(CFLAGS) -c src/genetics.c -o obj/genetics.o

clean:
	rm -rf obj/*.o
	rm bin/collateral-monk
