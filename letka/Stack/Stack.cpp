#include"Stack.h"

const double My_Left_Canareika = 0xbeefaaaa;
const long long int My_Right_Canareika = 0xdeaddeed;
const double Poison = 0xdeadbeef;

#define STACK_ASSERT(stk)  StackAssert(stk, __FILE__, __LINE__)


FILE *logfile = fopen("log.txt", "w");
int StackPush(Stack_t* stk, StackElem_t elem)
{
    int err = 0;//проверка на ошибки в будущем

    STACK_ASSERT(stk);
    if ((stk->stk_size) >= (stk->stk_capacity))
    {
        (stk->stk_capacity) = 2*(stk->stk_capacity);
        (stk->stk_array) = (StackElem_t*)realloc((stk->stk_array), (stk->stk_capacity + 2)*sizeof(StackElem_t));
        for (int i = stk->stk_size + 1; i < stk->stk_capacity; i++)
        {
            memcpy(&(stk->stk_array[i]), &Poison, 8);
        }
        
    }
    (stk->stk_array)[stk->stk_capacity + 1] = My_Right_Canareika;
    (stk->stk_size)++;
    (stk->stk_array)[stk->stk_size] = elem;
    (stk->stk_hash) = StackHaschFunc(stk);
    
    STACK_ASSERT(stk);

    return err;//сделать проверку на ошибки
}

int StackPop(Stack_t* stk, StackElem_t* elem)
{
    int err = 0;//сделать проверки на ошибки
    
    
    if ((stk->stk_size) && (stk->stk_capacity))
    {
        if ((stk->stk_capacity)/(stk->stk_size) >= 4)
        {
            (stk->stk_capacity) = (stk->stk_capacity)/3;

           (stk->stk_array) = (StackElem_t*)realloc((stk->stk_array), ((stk->stk_capacity + 2))*sizeof(StackElem_t));
           for (int i = stk->stk_size + 1; i < stk->stk_capacity; i++)
            {
                memcpy(&(stk->stk_array[i]), &Poison, 8);
            }
        }
    }

    if (stk->stk_size)
    {
        *elem = (stk->stk_array)[stk->stk_size];
        (stk->stk_array)[stk->stk_size] = Poison;
        (stk->stk_array)[stk->stk_size + 1] = Poison;
        (stk->stk_array)[stk->stk_capacity + 1] = My_Right_Canareika;
        (stk->stk_size)--;
        stk->stk_hash = StackHaschFunc(stk);
    }
    else
    {
        STACK_ASSERT(stk);
        printf("\nyour stack is empty!\n");
        return 1;
    }
    
    STACK_ASSERT(stk);
    return err;
}

int StackCtor(Stack_t* stk, StackElem_t fst_elem)
{
    int err = 0;//сделать как-нибудь

    
    (stk->stk_array) = (StackElem_t*)calloc(4, sizeof(StackElem_t));
    (stk->stk_size) = 1;
    (stk->stk_capacity) = 2;
    
    //
    (stk->stk_array)[0] = My_Left_Canareika;
    (stk->stk_array)[1] = fst_elem;
    (stk->stk_array)[stk->stk_capacity + 1] = My_Right_Canareika;
    (stk->stk_hash) = StackHaschFunc(stk);

    STACK_ASSERT(stk);
    return err;
}

int StackDtor(Stack_t* stk)
{
    int err = 0;

    free(stk->stk_array);
    stk->stk_size = 0;
    stk -> stk_capacity = 0;

    return err;
}

// void* 
int StackDump(Stack_t* stk)
{
    int err = 0;
    fprintf(logfile, "Stack capacity: %zu\n", (stk->stk_capacity));
    fprintf(logfile, "Stack size: %zu\n", (stk->stk_size));
    fprintf(logfile, "Stack:\n");
    
    for (size_t elem = 0; elem < (stk->stk_capacity + 2); elem++)
    {
        fprintf(logfile, "%x ", (u_int32_t)(stk->stk_array)[elem]);
    }
    printf("\n");
    return err;
}

enum errors_t StackError(Stack_t* stk)//
{
    errors_t err = VSE_HOROSHO;
    if(stk->stk_capacity < stk->stk_size)
    {
        err = STACK_SIZE_ZALUPA;
    }
    if((stk->stk_array)[0] != My_Left_Canareika)
    {
        err = LEFT_KANAREIKA_ZALUPA;
    }
    if(((stk->stk_array)[stk->stk_capacity + 1]) != My_Right_Canareika)
    {
        err = RIGHT_KANAREIKA_ZALUPA;
    }
    if (StackHaschFunc(stk) != (stk->stk_hash))
    {
        err = HASH_ZALUPA;
    }
    
    return err;
}


void StackAssert(Stack_t* stk, const char *file_name, const int line)
{
    if (errors_t ERROR = StackError(stk))
    {
        fprintf(logfile,"\n\n-----FILE: %s-----linе: %d-----\n\n", file_name, line);
        
        switch (ERROR)
        {
        case STACK_SIZE_ZALUPA:
            fprintf(logfile, "\n\n------STACK_SIZE_ZALUPA------ == %lg\n\n", (stk->stk_array)[0]);
            break;
        case LEFT_KANAREIKA_ZALUPA:
            fprintf(logfile, "\n\n------LEFT_KANAREIKA_ZALUPA------%lg\n\n", (stk->stk_array)[0]);
            break;
        case RIGHT_KANAREIKA_ZALUPA:
            fprintf(logfile, "\n\n------RIGHT_KANAREIKA_ZALUPA------ == %x\n\n", (u_int32_t)(stk->stk_array)[stk->stk_capacity + 1]);
            break;   
        case HASH_ZALUPA:
            fprintf(logfile, "\n\n------HASH_ZALUPA------\n"
                    "------EXPECTED:  %lld\n"
                    "------RETURND:  %lld\n", (stk->stk_hash), StackHaschFunc(stk));
            break; 
        default:
        printf("\n\n------POLNYI_PIZDEC------\n\n");
            break;
        }
        StackDump(stk);
        assert(0);
    }
}

hash_t StackHaschFunc(Stack_t* stk)
{
    double  hash = 0;
    for (size_t i = 0; i < (stk->stk_size+1); i++)
    {
        hash += (stk->stk_array)[i]*i;
    }
    hash = (hash_t)hash;
    return hash;
}