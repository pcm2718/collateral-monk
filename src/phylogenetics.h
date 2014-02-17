#ifndef MONK_PHYLOGENETICS_H
#define MONK_PHYLOGENETICS_H



#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "genetics.h"



#define STR_PRINT_LENGTH 16



typedef struct Node
{
  unsigned char* gene;

  struct Node* left;
  struct Node* right;
} Node;



Node*
build_node ( Node * const left , Node * const right , unsigned char const * const gene, unsigned int const gene_size );



void
free_node ( Node* node );



Node*
build_phylogenetic_tree ( unsigned char ** gene_list , unsigned int const gene_size, unsigned int const gene_count );



void
free_phylogenetic_tree ( Node* node );



void
print_phylogenetic_tree ( Node const * const node , int depth );



unsigned int
score_phylogenetic_tree ( Node* node );



#endif
