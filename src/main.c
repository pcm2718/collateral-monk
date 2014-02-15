#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "genetics.h"



#define GENE_COUNT 4
#define BASE_COUNT 10



int
main ( int argc, char** argv )
{
  /*
   * Declare array to hold GENE_COUNT genes (random character
   * sequences), each of size BASE_COUNT.
   *
   * May need function to grab __m128 from method in header.
   * This is going to get ugly.
   * This comment not currently accurate.
   */
  char** genes = malloc ( sizeof( char* ) * GENE_COUNT );
  for ( int i = 0 ; i < GENE_COUNT ; ++i )
    genes[i] = allocate_gene ( BASE_COUNT );

  /*
   * Seed random number generator with the current time.
   * Find a better way to do this, maybe with a genetics_init method.
   */
  srand ( time ( NULL ) );

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

  printf( "Serial mutation score: %u\n", serial_compute_mutation ( genes[0], genes[1], NULL , BASE_COUNT ) );
  //printf( "Parallel mutation score: %u\n", parallel_compute_mutation ( genes[0], genes[1], NULL , BASE_COUNT ) );

  /*
   * Do magic here.
   */

  /*
   * Probably generate some sort of report with timing information
   * here.
   */

  /*
   * genes is now dynamically allocated, so I have to deallocate it
   * myself, along with its contents. The call to a library function
   * may be unnecesary, but I'm keeping it until I can show
   * otherwise.
   *
   * This is a hack.
   */
  for ( int i = 0 ; i < GENE_COUNT ; ++i )
    free_gene ( genes[i] );
  free ( genes );

  /*
   * Return success!
   */
  return EXIT_SUCCESS;
};
