export OMPI_CC=clang

MPI_C="mpicc"
CFLAGS="-std=c99 -I src -g -Wall -Wextra -Werror"
LFLAGS="-std=c99 -L obj"

all: obj/main.o obj/genetics.o
	$(MPI_C) $(FLAGS) -L obj obj/main.o obj/genetics.o -o bin/collateral-monk

obj/main.o: src/main.c src/genetics.h
	$(MPI_C) $(FLAGS) -I src -c src/main.c -o obj/main.o

obj/genetics.o: src/genetics.c src/genetics.h
	$(MPI_C) $(FLAGS) -I src -c src/genetics.c -o obj/genetics.o

clean:
	rm -rf obj/*.o
	rm bin/collateral-monk
