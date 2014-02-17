#include "phylogenetics.h"



Node*
build_node ( Node * const left , Node * const right , unsigned char const * const gene, unsigned int const gene_size )
{
  Node* new_node = malloc ( sizeof ( Node ) );

  new_node->left = left;
  new_node->right = right;

  new_node->gene = allocate_gene ( gene_size );
  memcpy ( new_node->gene , gene , gene_size );

  return new_node;
};



void
free_node ( Node* node )
{
  free_gene ( node->gene );
  free ( node );
};



Node*
build_phylogenetic_tree ( unsigned char ** gene_list , unsigned int const gene_size, unsigned int const gene_count )
{
  /*
   * Allocate a queue of nodes of size gene_count.
   */
  Node** gene_queue = malloc ( sizeof ( Node* ) * gene_count );

  /*
   * Fill the queue with genes from gene_list.
   */
  for ( unsigned int i = 0 ; i < gene_count ; ++i )
    {
      gene_queue[i] = build_node ( NULL , NULL , gene_list[i] , gene_size ); 
    }

  /*
   * Process the queue until it has one root node in it. Magic here.
   * 
   * Some Poetry:
   *
   * In the land of Unix, where shadows lie.
   * One Node to rule them all, one Node to find them.
   * One Node to take them all and within the tree bind them.
   * In the land of Unix, where shadows lie.
   */
  for ( unsigned int j = 1 ; j < gene_count ; j*=2 )
    {
      for ( unsigned int i = j - 1 ; i + j < gene_count ; i += ( 2 * j ) )
        {
          unsigned char* new_gene = allocate_gene ( gene_size );
          parallel_compute_mutation ( gene_queue[i]->gene , gene_queue[i+j]->gene , new_gene , gene_size );

          gene_queue[i+j] = build_node ( gene_queue[i] , gene_queue[i+j] , new_gene, gene_size );
          gene_queue[i] = NULL;

          free ( new_gene );
        }
    }

  /*
   * We are now done with gene queue. Move the root node of the new
   * tree to a variable.
   */
  Node* root = gene_queue[gene_count-1];
  free ( gene_queue );

  /*
   * Return the pointer to the one Node to rule them all.
   * In the land of Unix, where shadows lie.
   */
  return root;
};



void
free_phylogenetic_tree ( Node* node )
{
  /*
   * If the node is NULL, return void.
   */
  if ( ! node )
    return;

  /*
   * Destroy^H^H^H^H^H^H^H LIBERATE the left and right subtrees.
   */
  free_phylogenetic_tree ( node->left );
  free_phylogenetic_tree ( node->right );

  /*
   * Commit suicide.
   */
  free_node ( node );

  /*
   * I guess the node wasn't NULL after all, return void anyways.
   */
  return;
};



void
print_phylogenetic_tree ( Node const * const node , int depth )
{
  if ( ! node )
    return;

  print_phylogenetic_tree ( node->left , depth + 1 );

  for ( int i = 0 ; i < depth - 1 ; ++i )
    printf ( "    " );
  printf ( "|-> " );

  unsigned char* str = malloc ( sizeof ( unsigned char ) * STR_PRINT_LENGTH );
  memcpy ( str , node->gene , STR_PRINT_LENGTH );
  convert_gene_to_str ( str , STR_PRINT_LENGTH );

  printf ( "%.16s" , str );

  free ( str );

  putchar ( '\n' );

  print_phylogenetic_tree ( node->right , depth + 1 );
};



unsigned int
score_phylogenetic_tree ( Node* node )
{
  Node* x = node;
  ++x;

  return 0;
};
