#ifndef list_h
#define list_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define debug_m //<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<->


typedef int ListElem_t;


struct List_t
{
    size_t      listSize;
    size_t      listMaxSize;
    size_t      freeElem;
    ListElem_t* data;
    size_t*     next; //elem_t -> size_t
    size_t*     prev;
    
    #ifdef debug_m
    u_int8_t nPictures;
    #endif
};

int  ListCtor(List_t *lst, size_t lstSize);
void ListDtor(List_t *lst);

int  ListInsert           (List_t *lst, size_t elemNumber, int  elem);
int  ListDeleteElem       (List_t *lst, size_t elemNumber);

int*   ListTakeElemPtr       (List_t *lst, size_t elemNumber);
int*   ListTakeFirstElemPtr  (List_t *lst);
int*   ListTakeLastElemPtr   (List_t *lst);
size_t ListTakeFirstElemIndex(List_t *lst);
size_t ListTakeLastElemIndex (List_t *lst);
size_t ListTakeNextElemIndex (List_t *lst, size_t index);
int*   ListTakeElemByIndex   (List_t *lst, size_t index);

void MakeListGraph        (List_t *lst);
void CleanCmdBuffer       (void);
#endif //list_h
