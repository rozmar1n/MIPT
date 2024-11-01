#include "list.h"

int ListCtor(List_t *lst, size_t lstSize)
{
    lst->ar_data = NULL;
    lst->ar_data = (int*)calloc(lstSize + 1, sizeof(ListElem_t));
    if (lst->ar_data == NULL)
    {
        fprintf(stderr, "\n\t ar_data array allocation problem!!!\n");
        return 0;
    }
    lst->ar_data[0] = poison; 

    lst->next.ar_next = NULL;
    lst->next.ar_next = (int*)calloc(lstSize + 1, sizeof(ListElem_t));
    if (lst->next.ar_next == NULL)
    {
        fprintf(stderr, "\n\t ar_next array allocation problem!!!\n");
        return 0;
    }
    lst->next.firstFreeElem    = 1;
    lst->next.ar_next[0]       = 0;
    lst->next.ar_next[lstSize] = 0;
    for (size_t i = 1; i < lstSize; i++)
    {
        lst->next.ar_next[i] = -(i+1);
        fprintf(stderr, "%lu: lst->next.ar_next[i] = %d\n", i, lst->next.ar_next[i]);
    }
    
    lst->ar_prev = NULL;
    lst->ar_prev = (int*)calloc(lstSize + 1, sizeof(ListElem_t));
    if (lst->ar_prev == NULL)
    {
        fprintf(stderr, "\n\t ar_prev array allocation problem!!!\n");
        return 0;
    }
    lst->ar_prev[0] = 0;
    for (size_t i = 1; i < lstSize; i++)
    {
        lst->ar_prev[i] = -1;
    }
    for (size_t i = 0; i < lstSize; i++)
    {
        lst->ar_prev[i] = -1;
    }
    
    
    
    lst->head = 0;
    lst->tail = 0;
    lst->listSize = lstSize;
    return 1;
}

void ListDtor(List_t *lst)
{
    free(lst->ar_data);
    free(lst->next.ar_next);
    free(lst->ar_prev);
}

int ListInsertAfter(List_t *lst, size_t elemNumber, int elem)
{
    if (elemNumber > lst->listSize)
    {
        fprintf(stderr, "The entered item number is greater"
                        " than the specified list size!\n");
            return 1;
    }
    if ((elemNumber > lst->head))
    {        
        fprintf(stderr, "The list item before yours has "
                        "not yet been entered.\n"
                        "Do you want to insert the item "
                        "at the end of the list? (y/n)\n");
        
        char answer = '\0';
        scanf("%c", &answer);
        answer = tolower(answer);
        if (answer == 'y')
        {
            elemNumber = lst->head;
        }
        else
        {
            fprintf(stderr, "ok, it's yout choise\n");
            return 1;
        }
    }
    
    if (lst->head == 0 && lst->tail == 0)
    {
        lst->head                = 1;
        lst->tail                = 0;
        lst->ar_data[elemNumber] = elem; 

        lst->ar_prev[1] = 0;
    }
    if (elemNumber == lst->head)
    {
        lst->ar_data[-1*(lst->next.firstFreeElem)] = elem; 
        lst->next.firstFreeElem = lst->next.ar_next[-1*(lst->next.firstFreeElem)];
        lst->next.ar_next[lst->head] *= -1;
        lst->head = lst->next.ar_next[lst->head];
        
        //lst->next.ar_next[lst->head] = -1*(lst->next.firstFreeElem);
        //lst->next.firstFreeElem = -1*( lst->next.ar_next[lst->next.firstFreeElem]);


        
        // lst->ar_data[lst->head] = elem;
        
        // lst->next.ar_next[lst->head] = lst->next.firstFreeElem;
        // lst->head = lst->next.firstFreeElem;
        // lst->next.firstFreeElem = -lst->next.ar_next[lst->next.firstFreeElem];

        // lst->ar_prev[lst]
    }
    
}