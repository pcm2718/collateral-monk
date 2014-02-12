#ifndef MONK_GENETICS_H
#define MONK_GENETICS_H



#include <time.h>
#include <stdlib.h>



#define U_BASE 0
#define A_BASE 1
#define C_BASE 2
#define G_BASE 4
#define T_BASE 8



char*
generate_random_gene ( char* gene, unsigned int const size );



unsigned int
serial_compute_mutation_score ( char const * gene_a, char const * gene_b, unsigned int const size );



unsigned int
parallel_compute_mutation_score ( char const * gene_a, char const * gene_b, unsigned int const size );



#endif
