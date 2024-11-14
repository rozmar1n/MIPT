#include "akinator.h"

node* MakeStringNode(char* string, node* child_left, node* child_right)
{
    node* node_ptr = (node*)calloc(1, sizeof(node));
    node_ptr->data = string;  

    node_ptr->child_left = child_left;
    node_ptr->child_right = child_right;

    return node_ptr;
}

void MakeGraphStringNode(node* node, FILE* newGraph)
{
    if (node == NULL)
    {
        fprintf(stderr, "node is null!!!\n");
        return;
    }    
    fprintf(newGraph, "node%p [shape=Mrecord; label = \" {%p"
                      "| data = %s | left = %p | right = %p }\"];\n\t", 
                       node, node, (char*)(node->data), node->child_left, node->child_right);

    if (node->child_left)
    {
        MakeGraphStringNode(node->child_left, newGraph);
    }
    if (node->child_right)
    {
        MakeGraphStringNode(node->child_right, newGraph);
    }
}

void  TreeDumpFromStringNode(node* root, size_t* nPic)
{
    *(nPic) +=1;

    char graphName[128];
    sprintf(graphName, "dump/dotfiles/%lu.dot", *nPic);
    FILE* newGraph = fopen(graphName, "w");
    fprintf(newGraph, "digraph G\n\t" "{\n\t");

    MakeGraphStringNode(root, newGraph);
    fprintf(newGraph, "\n\t");
    MakeEdgeToChildren(root, newGraph);

    fprintf(newGraph, "}");
    char buffer[512] = {'\0'};

    char pictureName[128];
    sprintf(pictureName, "dump/tree_pictures/%lu.png\n", *nPic);
    sprintf(buffer, "dot -Tpng %s -o %s\n", graphName, pictureName);
    //fprintf(stderr, "%s", buffer);
    fclose(newGraph);
    system(buffer);
}

void GuessTheWord(node* root, node* parent)
{
    printf("%s?\n", (char*)(root->data));
    char answer[32] = {'\0'};
    scanf("%s", answer);
    if (strcmp(answer, "yes") == 0)
    {
        if(root->child_right) 
        {
            GuessTheWord(root->child_right, root);
        }
        else    
        {
            printf("I am very smart\n");
            return;
        }
    }
    if (strcmp(answer, "no") == 0)
    {
        if(root->child_left) 
        {
            GuessTheWord(root->child_left, root);
        }
        else    
        {
            AddQuestion(parent, root);
        }
    }
}

void AddQuestion(node* root, node* left_answer)
{
    printf("Enter the question: ");
    char* question = (char*)calloc(256, sizeof(char));
    scanf("%s", question);

    printf("Enter the answer: ");
    char* answer = (char*)calloc(256, sizeof(char));
    scanf("%s", answer);

    node* right_answer = MakeStringNode(answer, NULL, NULL);

    if (WhichChild(root, left_answer) == -1)
    {
        root->child_left = MakeStringNode(question, left_answer, right_answer);
        return; 
    }
    if (WhichChild(root, left_answer) == 1)
    {
        root->child_right = MakeStringNode(question, left_answer, right_answer); 
        return;
    }
    fprintf(stderr, "Something is getting wrong. We don't know what it is\n");
    
}

char WhichChild(node* root, node* child)
{
    if (child == root->child_left)
        return -1;
    if  (child == root->child_right)
        return 1;
    return 0;
}

void FreeStringTree(node* Tree_Root)
{
    if (Tree_Root->child_right)
    {
        FreeStringTree(Tree_Root->child_right);
    }
    if (Tree_Root->child_left)
    {
        FreeStringTree(Tree_Root->child_left);
    }
    free(Tree_Root->data);
    free(Tree_Root);
}