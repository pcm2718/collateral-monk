#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "genetics.h"



#define GENE_COUNT 4
#define BASE_COUNT 8



int
main ( int argc, char** argv )
{
  /*
   * Declare array to hold GENE_COUNT genes (random character
   * sequences), each of size BASE_COUNT.
   */
  char genes [GENE_COUNT][BASE_COUNT];

  /*
   * Seed random number generator with the current time.
   * Find a better way to do this.
   */
  srand ( time (NULL) );

  /*
   * For each gene in genes, fill the gene with random bases.
   */
  for ( int i = 0 ; i < GENE_COUNT ; ++i )
    generate_random_gene ( genes[i], BASE_COUNT );

  for ( int i = 0 ; i < 2 ; ++i )
    {
      for ( int j = 0 ; j < BASE_COUNT ; ++j )
        printf("%x ", genes[i][j] & 0xff);
      printf("\n");
    }

  printf( "Serial mutation score: %u\n", serial_compute_mutation_score ( genes[0], genes[1] , BASE_COUNT ) );
  printf( "Parallel mutation score: %u\n", parallel_compute_mutation_score ( genes[0], genes[1] , BASE_COUNT ) );

  /*
   * Do magic here.
   */

  /*
   * Probably generate some sort of report with timing information
   * here.
   */

  /*
   * Return success!
   */
  return EXIT_SUCCESS;
};
