#ifndef AKINATOR_H
#define AKINATOR_H

#include "bin_tree/tree.h"
#include "cctype"

//#define alphabet "%[abcdefghigklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ?\'\"!\32\255\?.\n]"

node* MakeStringNode(char* string, node* child_left, node* child_right);
const int Max_String_For_Node = 256;


void GuessTheWord          (node* root, node* parent);
void MakeGraphStringNode   (node* node, FILE* newGraph);
void TreeDumpFromStringNode(node* root, size_t* nPic);
void AddQuestion           (node* root, node* answer);
char WhichChild            (node* root, node* child);

void  WriteTreeTxt   (node* root, FILE* tree_file);
node* TakeTreeFromTxt(char** filename);

void ClearBuffer(void);

char* PutText(const char *TextFile, long* TextSize);

#endif //AKINATOR_H
