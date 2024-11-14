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

void  TreeDumpFromStringNode   (node* root, size_t* nPic)
{
    *(nPic) +=1;

    char graphName[128];
    sprintf(graphName, "dotfiles/%llu.dot", *nPic);

    FILE* newGraph = fopen(graphName, "w");
    fprintf(newGraph, "digraph G\n\t" "{\n\t");

    MakeGraphStringNode(root, newGraph);
    fprintf(newGraph, "\n\t");
    MakeEdgeToChildren(root, newGraph);

    fprintf(newGraph, "}");
    char buffer[512] = {'\0'};

    char pictureName[128];
    sprintf(pictureName, "tree_pictures/%llu.png", *nPic);

    sprintf(buffer, "dot -Tpng %s -o %s\n", graphName, pictureName);
    fprintf(stderr, "%s", buffer);
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
            printf("I am vert smart\n");
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
            AddQuestion(root, root->child_left);
        }
    }
}

void AddQuestion(node* root, node* answer)
{
    printf("Enter the question: ");
    char* question = (char*)calloc(256, sizeof(char));
    scanf("%s", question);
    
}