#include "list.h"
const int    poison   = 0xdeadbeef;
const size_t fic_elem = 0;   

int ListCtor(List_t *lst, size_t lstSize)
{
    lst->data = NULL;
    lst->data = (ListElem_t*)calloc(lstSize + 1, sizeof(ListElem_t));
    if (lst->data == NULL)
    {
        fprintf(stderr, "\n\t data array allocation problem!!!\n");
        return 0;
    }
    lst->data[0] = poison; 

    lst->next = NULL;
    lst->next = (size_t*)calloc(lstSize + 1, sizeof(size_t));
    if (lst->next == NULL)
    {
        fprintf(stderr, "\n\t next array allocation problem!!!\n");
        return 0;
    }
    lst->next[0]       = 0;
    lst->next[lstSize] = 1;
    for (size_t i = 1; i < lstSize - 1; i++)
    {
        lst->next[i] = i+1;
        //fprintf(stderr, "lst->next.ar_next[%lu] = %d\n", i, lst->next[i]);
    }
    lst->freeElem = lstSize;



    lst->prev = NULL;
    lst->prev = (size_t*)calloc(lstSize + 1, sizeof(size_t));
    if (lst->prev == NULL)
    {
        fprintf(stderr, "\n\t prev array allocation problem!!!\n");
        return 0;
    }
    lst->prev[0] = 0;

    #ifdef debug_m
    for (size_t i = 1; i <= lstSize; i++)
    {
        lst->prev[i] = -0;
    }
    #endif


    lst->listSize = 0;
    lst->listMaxSize = lstSize;
//fprintf(stderr, "ListMaxSize = %lu\n", lst->listMaxSize);

    lst->nPictures = 0;
    return 1;
}

void ListDtor(List_t *lst)
{
    lst->freeElem    = 0;
    lst->listMaxSize = 0;
    lst->listSize    = 0;
    
    free(lst->data);
    free(lst->next);
    free(lst->prev);
}

int ListInsert(List_t *lst, size_t elemNumber, ListElem_t elem)
{
    if (elemNumber == 0)
    {
        return 1;
        //elemNumber = 1;
    }
    
    
    lst->listSize += 1;
    if (elemNumber > lst->listSize)
    {
        return 1;
        //elemNumber = lst->listSize;
    }


    if (lst->next[lst->freeElem] == 0)
    {
        lst->listMaxSize *= 2;
        lst->data = (ListElem_t*)realloc(lst->data, (lst->listMaxSize + 2)*sizeof(ListElem_t));

        lst->next =     (size_t*)realloc(lst->next, (lst->listMaxSize + 2)*sizeof(size_t));
        
        for (size_t i = lst->listSize + 1; i < lst->listMaxSize - 1; i++)
        {
            lst->next[i] = i + 1;
        }

        lst->next[lst->listMaxSize] = lst->listSize + 1;
        lst->next[lst->freeElem] = lst->listMaxSize;


        lst->prev =     (size_t*)realloc(lst->prev, (lst->listMaxSize + 2)*sizeof(size_t));
        
        for (size_t i = lst->listSize + 1; i < lst->listMaxSize; i++)
        {
            lst->prev[i] = -0;
        }

    }


    size_t before = fic_elem;
    for (size_t i = 1; i < elemNumber; i++)
    {
        before = lst->next[before];
    }
    size_t after = lst->next[before];


    lst->data[lst->next[lst->freeElem]] = elem;
    elemNumber                          = lst->next[lst->freeElem];
    lst->next[lst->freeElem]            = lst->next[elemNumber];
    lst->next[before]                   = elemNumber;
    lst->next[elemNumber]               = after;
    lst->prev[after]                    = elemNumber;
    lst->prev[elemNumber]               = before;   

    return 0; 
}

int ListDeleteElem(List_t *lst, size_t elemNumber)
{
    if (elemNumber > lst->listMaxSize)
    {
        return 1;
    }

    if (lst->listSize == 0)
    {
        //fprintf(stderr, "List is empty!!!\n");
        return 1;
    }
    
    if (elemNumber == 0)
    {
        return 1;
    }
    
    if (elemNumber > lst->listSize)
    {
        return 1;
        elemNumber = lst->listSize;
    }

    size_t before = fic_elem;
    for (size_t i = 1; i < elemNumber; i++)
    {
        before = lst->next[before];
    }

    elemNumber = lst->next[before];
    size_t after = lst->next[elemNumber];

    lst->next[before]     = after;
    lst->prev[after]      = before;
    
    lst->next[elemNumber] = lst->freeElem;
    lst->freeElem         = elemNumber;

    lst->listSize -= 1;
    
    return 0;
}

int* ListTakeElemPtr(List_t *lst, size_t elemNumber) 
{
    if (elemNumber > lst->listMaxSize)
    {
        return NULL;
    }
    
    if (elemNumber == 0)
    {
        return NULL;
    }
    
    if (elemNumber > lst->listSize)
    {
        return NULL;
    }
    
    size_t numberInList = fic_elem;
    for (size_t i = 0; i < elemNumber; i++)
    {
        numberInList = lst->next[numberInList];
    }
    return &(lst->data[numberInList]);
}

void MakeListGraph(List_t *lst)
{
    lst->nPictures += 1;
    
    char graphName[128];
    sprintf(graphName, "dotfiles/%d.dot", lst->nPictures);

    FILE* newGraph = fopen(graphName, "w");
    fprintf(newGraph, "digraph G\n\t{\n\t");
    fprintf(newGraph, "rankdir = LR\n\t");
    int elem = 0;
    for (size_t i = 0; i <= lst->listMaxSize; i++)
    {
        fprintf(newGraph, "node%0*lu [shape=Mrecord; label = \" {%0*lu}"
                          "| {data = %d} | {next = %lu} |{ prev = %lu }\"];\n\t", 
                           3, i, 3, i, lst->data[i], lst->next[i], lst->prev[i]);
    }

    elem = 0;
    for (size_t i = 0; i <= lst->listMaxSize; i++)
    {
        fprintf(newGraph, "node%03lu -> node%03lu [weight = 1000; color = white; ];\n\t",
                           lst->next[i], lst->next[lst->next[i]]);
        elem = lst->next[elem];
    }
    elem = 0;
    for (size_t i = 0; i <= lst->listSize; i++)
    {
        fprintf(newGraph, "node%03d -> node%03lu [color = blue;]\n\t",
                           elem, lst->prev[elem]);
        elem = lst->prev[elem];
    }
    elem = 0;
    for (size_t i = 0; i <= lst->listSize; i++)
    {
        fprintf(newGraph, "node%03d ->node%03lu [weight = 100000; color = red;]\n\t",
                           elem, lst->next[elem]);
        elem = lst->next[elem];
    }

    fprintf(newGraph, "FREE -> node%03lu [color = green;]\n\t", 
                       lst->freeElem);

    fprintf(newGraph, "}");
    char buffer[512] = {'\0'};

    char pictureName[128];
    sprintf(pictureName, "list_pictures/%d.png", lst->nPictures);

    sprintf(buffer, "dot -Tpng %s -o %s\n", graphName, pictureName);
    fprintf(stderr, "%s", buffer);
    fclose(newGraph);
    system(buffer);
}

void CleanCmdBuffer(void)
{
    while(getchar() != EOF)
    {
        true;
    }
}

int* ListTakeFirstElemPtr (List_t *lst)
{
    return &(lst->data[lst->next[fic_elem]]);
}

int* ListTakeLastElemPtr  (List_t *lst)
{
    return &(lst->data[lst->prev[fic_elem]]);
}

size_t ListTakeFirstElemIndex(List_t *lst)
{
    return lst->next[0];
}

size_t ListTakeLastElemIndex (List_t *lst)
{
    return lst->prev[0];
}

size_t ListTakeNextElemIndex (List_t *lst, size_t index)
{
    return lst->next[index];
}

int*   ListTakeElemByIndex   (List_t *lst, size_t index)
{
    return &(lst->data[index]);
}

//TODO: get next by index 