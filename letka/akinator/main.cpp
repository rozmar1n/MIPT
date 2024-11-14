#include "akinator.h"

int main(void)
{
    system("cd dump/dotfiles/ \nrm -i *\n");
    system("cd dump/tree_pictures/ \nrm -i *\n");
    size_t nPic = 0;
    char* first_question = (char*)calloc(64, sizeof(char));
    strcpy(first_question, "Is_it_Phystech");
    node* Tree_Root = MakeStringNode(first_question, NULL, NULL);
//fprintf(stderr, "first question: %s\n", (char*)(Tree_Root->data));
    TreeDumpFromStringNode(Tree_Root, &nPic);

    char* first_left_answer = (char*)calloc(64, sizeof(char));
    strcpy(first_left_answer, "It's_Danila");
    Tree_Root->child_left = MakeStringNode(first_left_answer, NULL, NULL);

    char* first_right_answer = (char*)calloc(64, sizeof(char));
    strcpy(first_right_answer, "It's_me");
    Tree_Root->child_right = MakeStringNode(first_right_answer, NULL, NULL);

    TreeDumpFromStringNode(Tree_Root, &nPic);
    
    GuessTheWord(Tree_Root, NULL);
    TreeDumpFromStringNode(Tree_Root, &nPic);

    GuessTheWord(Tree_Root, NULL);
    TreeDumpFromStringNode(Tree_Root, &nPic);

    GuessTheWord(Tree_Root, NULL);
    TreeDumpFromStringNode(Tree_Root, &nPic);

    FreeTree(Tree_Root);
}