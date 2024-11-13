#ifndef  bin_tree
#define  bin_tree

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int(*compar_func_t)(void* elem_1, void* elem_2, int MaxLine);
typedef long long int lli; 

struct node
{
    void* data;
    node* child_left;
    node* child_right;
};

node* MakeLongIntNode    (lli data, node* child_left, node* child_right);
void  TreeDumpFromNode   (node* root, size_t* nPic);
void  InsertLongIntNode  (node* leaf, node* root);

void FreeTree(node* root);

#endif //bin_tree