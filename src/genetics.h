#ifndef MONK_GENETICS_H
#define MONK_GENETICS_H



#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*
 * SPECIAL MAGIC SSE2 FUN!!!
 */
#include <emmintrin.h>



#define A_BASE 1
#define C_BASE 2
#define G_BASE 4
#define T_BASE 8
#define U_BASE 16

#define BASES { A_BASE, C_BASE, G_BASE, T_BASE, U_BASE };



unsigned char*
allocate_gene ( unsigned int const size );



void
free_gene ( unsigned char* gene );



unsigned char*
generate_random_gene ( unsigned char* const gene, unsigned int const size );



unsigned char* const
convert_str_to_gene ( unsigned char* const str, unsigned int const size );



unsigned char* const
convert_gene_to_str ( unsigned char* const gene, unsigned int const size );



unsigned char* const
load_gene_from_file ( unsigned char* const gene, unsigned int const size, char const * const filename );



unsigned char const * const
dump_gene_to_file ( unsigned char const * const gene, unsigned int const size, char const * const filename );



unsigned int
serial_compute_mutation ( unsigned char const * const gene_a, unsigned char const * const gene_b, unsigned char * const gene_out, unsigned int const gene_size );



unsigned int
parallel_compute_mutation ( unsigned char const * const gene_a, unsigned char const * const gene_b, unsigned char * const gene_out, unsigned int const gene_size );



#endif
