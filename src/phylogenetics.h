#ifndef MONK_PHYLOGENETICS_H
#define MONK_PHYLOGENETICS_H



#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <genetics.h>



#define STR_PRINT_LENGTH 16



typdef struct
{
  unsigned char* gene;

  struct Node* left;
  struct Node* right;
} Node;



Node*
allocate_node ( );



void
free_phylogenetic_tree ( Node const * const node );



void
print_tree_in_order ( Node const * const node , int depth );



#endif
