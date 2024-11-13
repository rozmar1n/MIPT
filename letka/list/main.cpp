#include "list.h"

int main()
{
    List_t list;
    ListCtor(&list, 10);

    for (size_t i = 0; i < 100; i++)
    {
        ListInsert(&list, 1, (i+1)*10);
        //fprintf(stderr, "elem: %d\n", *(ListTakeElemByIndex(&list, ListTakeFirstElemIndex(&list))));
        MakeListGraph(&list);
    }

    // *(ListTakeElemPtr(&list, 2)) += 1000;
    // MakeListGraph(&list);
    
    ListDtor(&list);
}