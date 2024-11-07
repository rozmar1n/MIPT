#include "list.h"

int main()
{
    List_t list;
    ListCtor(&list, 3);

    for (size_t i = 0; i < 20; i++)
    {
        ListInsert(&list, 1, (i+1)*10);
        MakeListGraph(&list);
    }

    *(ListTakeElemPtr(&list, 2)) += 1000;
    MakeListGraph(&list);
    
    ListDtor(&list);
}