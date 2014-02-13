#ifndef MONK_GENETICS_H
#define MONK_GENETICS_H



#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>



#define U_BASE 0
#define A_BASE 1
#define C_BASE 2
#define G_BASE 4
#define T_BASE 8



char*
generate_random_gene ( char* const gene, unsigned int const size );



char* const
convert_str_to_gene ( char* const str, unsigned int const size );



char* const
convert_gene_to_str ( char* const gene, unsigned int const size );



char* const
load_gene_from_file ( char* const gene, unsigned int const size, char const * const filename );



char const * const
dump_gene_to_file ( char const * const gene, unsigned int const size, char const * const filename );



unsigned int
serial_compute_mutation_score ( char const * const gene_a, char const * const gene_b, unsigned int const size );



unsigned int
parallel_compute_mutation_score ( char const * const gene_a, char const * const gene_b, unsigned int const size );



#endif
