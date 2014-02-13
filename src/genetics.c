#include "genetics.h"



char*
generate_random_gene ( char* const gene, unsigned int const size )
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



char* const
convert_str_to_gene ( char* const str, unsigned int const gene_size )
{
  /*
   * This just loops over each character in the given string and does
   * a simple substitution to generate the corresponding gene.
   */
  for ( int i = 0 ; i < gene_size ; ++i )
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

        /*
         * This case is interesting, I can't decide whether this
         * should be default behavior of the case statement or
         * perhaps not implemented at all.
         * I'll fix that later.
         */
      case '-':
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



char* const
convert_gene_to_str ( char* const gene, unsigned int const gene_size )
{
  /*
   * This just loops over each base in the given gene and does a
   * simple substitution to generate a coresponding string. Note that
   * bases are always converted to uppercase.
   */
  for ( int i = 0 ; i < gene_size ; ++i )
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

        /*
         * Much like its counterpart in convert_to_gene, I can't
         * decide whether this is correct, whether this should be
         * the default behavior of this case statement, or if this
         * shouldn't be implemented at all.
         * Time will tell.
         */
      case U_BASE:
        gene[i] = '-';
        break;

      default:
        /*
         * Add some default behavior here.
         */
        break;
      }

  return gene;
};



char* const
load_gene_from_file ( char* const gene, unsigned int const gene_size, char const * const filename )
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



char const * const
dump_gene_to_file ( char const * const gene, unsigned int const gene_size, char const * const filename )
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
  char* str = malloc ( sizeof ( char ) * gene_size );

  /*
   * Copy the gene into str.
   */
  strncpy ( str, gene, gene_size );

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
  for ( int i = 0 ; i < gene_size ; ++i )
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
  free ( str ) ;

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
serial_compute_mutation_score ( char const * const gene_a, char const * const gene_b, unsigned int const gene_size )
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
parallel_compute_mutation_score ( char const * const gene_a, char const * const gene_b, unsigned int const gene_size )
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
