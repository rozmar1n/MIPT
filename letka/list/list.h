#ifndef list_h
#define list_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FirstElem lst->tail
#define LastElem  lst->head

typedef int ListElem_t;

const int poison = -911119;  

struct nextArray_t
{
    ListElem_t* ar_next;
    size_t      firstFreeElem;
};

struct List_t
{
    size_t      listSize;
    ListElem_t* ar_data;
    size_t      head;
    size_t      tail;

    nextArray_t next;
    
    ListElem_t* ar_prev;
};

int  ListCtor(List_t *lst, size_t lstSize);
void ListDtor(List_t *lst);

int ListInsertAfter(List_t *lst, size_t elemNumber, int  elem);
int ListDelete     (List_t *lst, size_t elemNumber, int *elem);
#endif //list_h