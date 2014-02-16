#include "genetics.h"



unsigned char*
allocate_gene ( unsigned int const gene_size )
{
  /*
   * Allocate a character array of size gene_size and return its
   * address. Not currently aligned.
   */
  return malloc ( sizeof ( unsigned char ) * gene_size );
};



void
free_gene ( unsigned char* gene )
{
  /*
   * This function just calls free on gene. Strictly speaking, this
   * function may not be necessary, but I don't know if this is all
   * I need to do to free up a __m128 array and if there is more to
   * doing this it should be abstracted away from the user.
   */
  free ( gene );
};



unsigned char*
generate_random_gene ( unsigned char* const gene, unsigned int const gene_size )
{
  /*
   * Declare array of gene bases.
   */
  unsigned char bases [5] = BASES;

  /*
   * Assign a random base to each spot in the gene.
   * There might be a fast way to do this using SIMD.
   */
  for ( unsigned int i = 0 ; i < gene_size ; ++i )
    gene[i] = bases[ rand () % 5 ];

  /*
   * Return the gene pointer, now with random bases.
   */
  return gene;
};



unsigned char*
convert_str_to_gene ( unsigned char* const str, unsigned int const gene_size )
{
  /*
   * This just loops over each character in the given string and does
   * a simple substitution to generate the corresponding gene.
   */
  for ( unsigned int i = 0 ; i < gene_size ; ++i )
    switch ( str[i] )
      {
      case 'A':
      case 'a':
        str[i] = A_BASE;
        break;

      case 'C':
      case 'c':
        str[i] = C_BASE;
        break;

      case 'G':
      case 'g':
        str[i] = G_BASE;
        break;

      case 'T':
      case 't':
        str[i] = T_BASE;
        break;

      case '-':
      case '_':
        str[i] = U_BASE;
        break;


      default:
        /*
         * Add some default behavior here.
         */
        break;
      }

  return str;
};



unsigned char*
convert_gene_to_str ( unsigned char* const gene, unsigned int const gene_size )
{
  /*
   * This just loops over each base in the given gene and does a
   * simple substitution to generate a coresponding string. Note that
   * bases are always converted to uppercase.
   */
  for ( unsigned int i = 0 ; i < gene_size ; ++i )
    switch ( gene[i] )
      {
      case A_BASE:
        gene[i] = 'A';
        break;

      case C_BASE:
        gene[i] = 'C';
        break;

      case G_BASE:
        gene[i] = 'G';
        break;

      case T_BASE:
        gene[i] = 'T';
        break;

      case U_BASE:
        gene[i] = '-';
        break;

      default:
        /*
         * Add some default behavior here.
         * This code is temporary.
         */
        gene[i] = 'Z';
        break;
      }

  return gene;
};



unsigned char*
load_gene_from_file ( unsigned char* const gene, unsigned int const gene_size, char const * const filename )
{
  /*
   * Open the file given in filename for reading. This is where we
   * will read the gene.
   */
  FILE* infile = fopen ( filename, "r");

  /*
   * If we couldn't open the file for whatever reason, then return
   * NULL to indicate an issue.
   */
  if ( ! infile )
    return NULL;

  /*
   * Just avoiding a unused variable error here.
   */
  int x = gene_size;
  ++x;

  /*
   * I don't know what input files look like yet, so I'm going to
   * implement the rest of this function later.
   */

  /*
   * Close the input file (of course).
   */
  fclose ( infile );

  /*
   * Return the pointer to the output gene to indicate success.
   */
  return gene;
};



unsigned char const *
dump_gene_to_file ( unsigned char const * const gene, unsigned int const gene_size, char const * const filename )
{
  /*
   * Open the file given in filename for appending. This is where we
   * will dump the string form of the gene.
   */
  FILE* outfile = fopen ( filename, "a");

  /*
   * If we couldn't open the file for whatever reason, then return
   * NULL to indicate an issue.
   */
  if ( ! outfile )
    return NULL;

  /*
   * If we got to here, we have the dump file open, so we need to
   * allocate memory to hold the temporary string representation of
   * the gene.
   */
  //unsigned char* str = malloc ( sizeof ( unsigned char ) * gene_size );
  unsigned char* str = allocate_gene ( gene_size );

  /*
   * Copy the unsigned char*into str.
   */
  memcpy ( str, gene, gene_size );

  /*
   * Convert str to the string representation.
   */
  convert_gene_to_str ( str, gene_size );

  /*
   * As it so happens, str isn't a real string (null-terminated), so
   * we need to do a write to file using fputc and a loop. Note that
   * the loop terminates, the file is closed and NULL is returned if
   * an error is detected via EOF return. I may need to fix this
   * error condition.
   */
  for ( unsigned int i = 0 ; i < gene_size ; ++i )
    if ( fputc ( str[i] , outfile ) == EOF )
      {
        fclose ( outfile );
        return NULL;
      }

  /*
   * Write a newline to the file, as these should delineate genes.
   * Same error checking as before.
   */
  if ( fputc ( '\n' , outfile ) == EOF )
    {
      fclose ( outfile );
      return NULL;
    }

  /*
   * We're done with str now, so we can deallocate it. Might do this
   * before writing the newline to the file.
   */
  //free ( str );
  free_gene ( str );

  /*
   * Close the output file (of course).
   */
  fclose ( outfile );

  /*
   * Return the pointer to the input gene to indicate success, just
   * because we can.
   */
  return gene;
};



unsigned int
serial_compute_mutation ( unsigned char const * const gene_a, unsigned char const * const gene_b, unsigned char * const gene_out, unsigned int const gene_size )
{
  /*
   * Initialize the score to be zero.
   */
  unsigned int score = 0;

  /*
   * If the user has passed in a value for gene_out, then use that in
   * the scoring algorithm for storing the parent gene. Otherwise,
   * allocate a new gene of size gene_size for use in the scoring
   * algorithm, as the user doesn't want a copy of the parent gene.
   *
   * Technically speaking, no gene_out array is necessary if we don't
   * want to remember the parent gene, but making provisions to
   * accommodate this optimization would be ugly and unclear, so I
   * have decided not to do so unless absolutely necessary.
   */
  unsigned char* out = gene_out ? gene_out : allocate_gene ( gene_size );

  /*
   * Run the serial scoring algorithm with conventional constructs.
   */
  for ( unsigned int i = 0 ; i < gene_size ; ++i )
    {
      out[i] = gene_a[i] & gene_b[i];

      if ( ! out[i] )
        {
          ++score;
          out[i] = gene_a[i] | gene_b[i];
        }
    }

  /*
   * Deallocate the parent gene if gene_out is NULL, otherwise we
   * have a *definite* memory leak (whereas returning the parent gene
   * via gene_out only introduces the *possibility* of a memory leak,
   * which would be the user's fault anyways).
   */
  if ( ! gene_out )
    free_gene ( out );

  /*
   * Return the mutation score.
   */
  return score;
};



unsigned int
parallel_compute_mutation ( unsigned char const * const gene_a, unsigned char const * const gene_b, unsigned char * const gene_out, unsigned int const gene_size )
{
  /*
   * Initialize the score to be zero.
   */
  unsigned int score = 0;

  /*
   * If the user has passed in a value for gene_out, then use that in
   * the scoring algorithm for storing the parent gene. Otherwise,
   * allocate a new gene of size gene_size for use in the scoring
   * algorithm.
   *
   * See the corresponding comment in serial_compute_mutation for a
   * more through explanation of this line.
   */
  unsigned char* out = gene_out ? gene_out : allocate_gene ( gene_size );

  /*
   * Allocate a few temporary variables as static to improve
   * perfomrance. May need to allocate more variables.
   */
  //static __m128 BIG_ZERO = 0;
  __m128 BIG_ZERO = _mm_set1_pd (0.0);
  static __m128 x, a, b;

  /*
   * Run the comparison with SPECIAL MAGIC SSE2 FUN!!!
   */
  int i = 0;
  for ( ; gene_size - i >= 16 ; i+=16 )
    {
      memcpy ( &a , gene_a + i , sizeof ( __m128 ) );
      memcpy ( &b , gene_b + i , sizeof ( __m128 ) );

      x = _mm_and_si128 ( a , b );

      /*
       * There might be a better way to do this.
       */
      for ( int j = 0 ; j < 16 ; ++j )
        score += ! ( (unsigned char*)(&x) )[j];

      x = _mm_or_si128 ( _mm_and_si128 ( _mm_cmpeq_epi8 ( BIG_ZERO , x ) , _mm_or_si128 ( a , b ) ) , x );
      memcpy ( out + i , &x , sizeof( __m128 ) );
    }

  /*
   * Finish off the comparison by running any remaining bases through
   * the serial_compute_mutation, as SSE can only process blocks of 
   * 16 bases.
   */
  score += serial_compute_mutation ( gene_a + i , gene_b + i , out + i , gene_size - i );

  /*
   * If gene_out is NULL, free out to avoid a memory leak.
   *
   * See the corresponding comment in serial_compute_mutation for a
   * more through explanation of this line (and lulz).
   */
  if ( ! gene_out )
    free_gene ( out );

  /*
   * Return the mutation score.
   */
  return score;
};
