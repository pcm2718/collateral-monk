#include "genetics.h"



char*
generate_random_gene ( char* gene, unsigned int const size )
{
  /*
   * Declare array of gene bases.
   */
  char bases [4] = { A_BASE, C_BASE, G_BASE, T_BASE };

  /*
   * Seed random number generator with current time.
   */
  //srand ( time ( NULL ) );

  /*
   * Assign a random base to each spot in the gene.
   * There might be a fast way to do this using SIMD.
   */
  for ( int i = 0 ; i < size ; ++i )
    gene[i] = bases[ rand () % 4 ];

  /*
   * Return the gene pointer, now with random bases.
   */
  return gene;
};



unsigned int
serial_compute_mutation_score ( char const * gene_a, char const * gene_b, unsigned int const gene_size )
{
  /*
   * Initialize the score to be zero.
   */
  unsigned int score = 0;

  /*
   * Allocate the results gene.
   */
  char* out = malloc ( sizeof ( char ) * gene_size );

  /*
   * Run the comparison with conventional constructs.
   */
  for ( int i = 0 ; i < gene_size ; ++i )
    {
      out[i] = gene_a[i] & gene_b[i];

      if ( ! out[i] )
        {
          ++score;
          out[i] = gene_a[i] | gene_b[i];
        }
    }

  /*
   * Deallocate the results gene.
   */
  free ( out );

  /*
   * Return the mutation score.
   */
  return score;
};



unsigned int
parallel_compute_mutation_score ( char const * gene_a, char const * gene_b, unsigned int const gene_size )
{
  /*
   * Initialize the score to be zero.
   */
  unsigned int score = 0;

  /*
   * Allocate the results gene.
   */
  char* out = malloc ( sizeof ( char ) * gene_size );

  /*
   * Run the comparison with SPECIAL MAGIC SIMD FUN!!!
   * Fix this later.
   */
  for ( int i = 0 ; i < gene_size ; ++i )
    {
      out[i] = gene_a[i] & gene_b[i];

      if ( ! out[i] )
        {
          ++score;
          out[i] = gene_a[i] | gene_b[i];
        }
    }

  /*
   * Deallocate the results gene.
   */
  free ( out );

  /*
   * Return the mutation score.
   */
  return score;
};
