#include"Stack.h"
//стоит ли сделать два хэша в структуре один реальный, другой для передачи во время ошибок???

const double My_Left_Canareika = 0xbeefbeef;
const double My_Right_Canareika = 0xdeaddeed;
const double Poison = 0xdeadbeef; // hexspeak (ex: 0xdeadbeef...)

#define STACK_ASSERT(stk)  StackAssert(stk, __FILE__, __LINE__)



int StackPush(Stack_t* stk, StackElem_t elem)
{
    int err = 0;//проверка на ошибки в будущем

    STACK_ASSERT(stk);
    if ((stk->stk_size) >= (stk->stk_capacity - 2))
    {
        (stk->stk_capacity) = 2*(stk->stk_capacity + 2);
        (stk->stk_array) = (StackElem_t*)realloc((stk->stk_array), (stk->stk_capacity)*sizeof(StackElem_t));
        for (int i = stk->stk_size + 1; i < stk->stk_capacity; i++)
        {
            memcpy(&(stk->stk_array[i]), &Poison, 8);
        }
        
    }
    memcpy(&(stk->stk_array)[stk->stk_capacity - 1], &My_Right_Canareika, 8);
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
            (stk->stk_capacity) = (stk->stk_capacity)/4 + 2;

           (stk->stk_array) = (StackElem_t*)realloc((stk->stk_array), ((stk->stk_capacity))*sizeof(StackElem_t));
           for (int i = stk->stk_size + 1; i < stk->stk_capacity; i++)
            {
                memcpy(&(stk->stk_array[i]), &Poison, 8);
            }
        }
    }
    //STACK_ASSERT(stk);
    if (stk->stk_size)
    {
        *elem = (stk->stk_array)[stk->stk_size];
        (stk->stk_array)[stk->stk_size] = Poison;
        (stk->stk_array)[stk->stk_size + 1] = Poison;
        memcpy(&(stk->stk_array)[stk->stk_capacity - 1], &My_Right_Canareika, 8);
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

    
    (stk->stk_array) = (StackElem_t*)calloc(3, sizeof(StackElem_t));
    (stk->stk_size) = 1;
    (stk->stk_capacity) = 3;
    
    //
    (stk->stk_array)[0] = My_Left_Canareika;//put with memcpy;
    (stk->stk_array)[1] = fst_elem;
    memcpy(&(stk->stk_array)[stk->stk_capacity -1], &My_Right_Canareika, 8);
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
// more info
int StackDump(Stack_t* stk)
{
    int err = 0;
    fprintf(stderr, "Stack capacity: %zu\n", (stk->stk_capacity));
    fprintf(stderr, "Stack size: %zu\n", (stk->stk_size));
    fprintf(stderr, "Stack:\n");
    
    for (size_t elem = 0; elem < (stk->stk_capacity); elem++)
    {
        fprintf(stderr, "%x ", (u_int32_t)(stk->stk_array)[elem]);
    }
    printf("\n");
    return err;
}

enum errors_t StackError(Stack_t* stk)//
{
    errors_t err = USE_HOROSHO; // STACK_ASS
    if(stk->stk_capacity < stk->stk_size)
    {
        err = STACK_SIZE_ZALUPA;
    }
    if((stk->stk_array)[0] != My_Left_Canareika)
    {
        err = LEFT_KANAREIKA_ZALUPA;
    }
    if(((stk->stk_array)[stk->stk_capacity - 1]) != My_Right_Canareika)
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
        fprintf(stderr,"\n\n-----FILE: %s-----linе: %d-----\n\n", file_name, line);
        
        switch (ERROR)
        {
        case STACK_SIZE_ZALUPA:
            fprintf(stderr, "\n\n------STACK_SIZE_ZALUPA------ == %lg\n\n", (stk->stk_array)[0]);
            break;
        case LEFT_KANAREIKA_ZALUPA:
            fprintf(stderr, "\n\n------LEFT_KANAREIKA_ZALUPA------%lg\n\n", (stk->stk_array)[0]);
            break;
        case RIGHT_KANAREIKA_ZALUPA:
            fprintf(stderr, "\n\n------RIGHT_KANAREIKA_ZALUPA------ == %lg\n\n", (stk->stk_array)[stk->stk_capacity - 1]);
            break;   
        case HASH_ZALUPA:
            fprintf(stderr, "\n\n------HASH_ZALUPA------\n"
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