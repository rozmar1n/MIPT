#ifndef akinator_h
#define akinator_h

#include "bin_tree/tree.h"

node* MakeStringNode(char* string, node* child_left, node* child_right);

void GuessTheWord          (node* root, node* parent);
void MakeGraphStringNode   (node* node, FILE* newGraph);
void TreeDumpFromStringNode(node* root, size_t* nPic);
void AddQuestion           (node* root, node* answer);
char WhichChild(node* root, node* child);
void FreeStringTree(node* Tree_Root);


#endif