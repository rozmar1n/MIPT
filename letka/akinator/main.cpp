#include "akinator.h"

int main(void)
{
    system("cd dump/dotfiles/ \nrm * \n");
    system("cd dump/tree_pictures/ \nrm * \n");
    size_t nPic = 0;
    // char* first_question = (char*)calloc(64, sizeof(char));
    // strcpy(first_question, "Рома");
    // node* Tree_Root = MakeStringNode(first_question, NULL, NULL);
//fprintf(stderr, "first question: %s\n", (char*)(Tree_Root->data));
    // TreeDumpFromStringNode(Tree_Root, &nPic);

    // FILE* first_tree = fopen("tree_1.txt", "w");
    // WriteTreeTxt(Tree_Root, first_tree);
    // fclose(first_tree);


    // TreeDumpFromStringNode(Tree_Root, &nPic);
    
    // GuessTheWord(Tree_Root, NULL);
    // TreeDumpFromStringNode(Tree_Root, &nPic);

    // FILE* second_tree = fopen("tree_2.txt", "w");
    // WriteTreeTxt(Tree_Root, second_tree);
    // fclose(second_tree);

    long text_size = 0;
    char* text = PutText("tree.txt", &text_size);
    fprintf(stderr, "tree: %s\n", text);
    node *Tree_Root = TakeTreeFromTxt(&text);
    GuessTheWord(Tree_Root, NULL);
    
    FILE* second_tree = fopen("tree.txt", "w");
    WriteTreeTxt(Tree_Root, second_tree);
    fclose(second_tree);

    TreeDumpFromStringNode(Tree_Root, &nPic);

    FreeTree(Tree_Root);
}