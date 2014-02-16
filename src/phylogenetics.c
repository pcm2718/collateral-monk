#include "phylogenetics.h"



Node*
build_node ( Node const * const left , Node const * const right , unsigned char const * const gene )
{
  Node* new_node = malloc ( sizeof ( Node* ) );

  new_node->left = left;
  new_node->right = right;
  new_node->gene = gene;

  return new_node;
};



void
free_node ( Node* node )
{
  free ( node );
};



Node*
build_phylogenetic_tree ( unsigned char const * const * const gene_list , unsigned int const gene_size, unsigned int const gene_count )
{
  /*
   * Allocate a queue of nodes of size gene_count.
   */
  Node** gene_queue = malloc ( sizeof ( Node* ) * gene_count );

  /*
   * Fill the queue with genes from gene_list.
   */
  for ( int i = 0 ; i < gene_count ; ++i )
    {
      gene_queue[i] = build_node ( NULL , NULL , gene_list[i] ); 
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
  for ( int i = 0 ; i < ; ++i )
    {
    }

  /*
   * Return the pointer to one Node to rule them all.
   * In the land of Unix, where shadows lie.
   */
  return gene_queue[0];
};

{
  /*
   * Allocate the queue.
   */
  Node** gene_queue = malloc ( sizeof ( Node* ) * gene_count );

  /*
   * Load the queue with nodes.
   */
  for ( int i = 0 ; i < gene_count ; ++i )
    {
      gene_queue[i] = malloc ( sizeof ( Node ) );
      gene_queue[i]->left = NULL;
      gene_queue[i]->right = NULL;
      gene_queue[i]->gene = genes[i];
    }

  /*
   * Do a sort here.
   *
   * Need some sort of priority queue.
   */

  /*
   * Build the tree from the queue.
   */
  for ( int i = 0 ; i < gene_count ; ++i )
    {
      Node* new_node = malloc ( sizeof ( Node* ) );

      node_new_
    }

  return;
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
  destroy_phylogenetic_tree ( node->left );
  destroy_phylogenetic_tree ( node->right );
  //free_gene ( node->gene );

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

  print_tree_in_order ( node->left , depth + 1 );

  for ( int i = 0 ; i < depth ; ++i )
    puts ( "    " );

  unsigned char* str = malloc ( sizeof ( unsigned char ) * STR_PRINT_LENGTH );
  memcpy ( str , node->gene , STR_PRINT_LENGTH );

  printf ( "%.16s" , str );

  free ( str );

  print_tree_in_order ( node->right , depth + 1 );
};



unsigned int
score_phylogenetic_tree ( Node* node )
{
};
