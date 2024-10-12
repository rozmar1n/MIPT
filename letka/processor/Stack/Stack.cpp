#include"Stack.h"

const double Left_Canary = 0xbeefaaaa;
const long long int Right_Canary = 0xdeaddeed;
const double Poison = 0xdeadbeef;
const char nCanaries = 2;
const int upcoef = 2;

#define STACK_ASSERT(stk)  StackAssert(stk, __FILE__, __LINE__)

    //TODO: а вдруг не откроет

int StackPush(Stack_t* stk, StackElem_t elem)
{
    int err = 0;

    STACK_ASSERT(stk);
    if ((stk->stk_size) >= (stk->stk_capacity))
    {
        (stk->stk_capacity) = upcoef*(stk->stk_capacity);
        (stk->stk_array) = (StackElem_t*)realloc((stk->stk_array), (stk->stk_capacity + nCanaries)*sizeof(StackElem_t));
        
        //проверить реалок


        if (stk->stk_array == NULL)
            err = 1;
        
        for (int i = stk->stk_size + 1; i < stk->stk_capacity; i++)
        {
            if (memcpy(&(stk->stk_array[i]), &Poison, 8))
            {
                err = 2;    
            }
        }
    }
    (stk->stk_array)[stk->stk_capacity + 1] = Right_Canary;
    (stk->stk_size)++;
    (stk->stk_array)[stk->stk_size] = elem;
    (stk->stk_hash) = StackHashFunc(stk);
    
    STACK_ASSERT(stk);

    return err;
}

int StackPop(Stack_t* stk, StackElem_t* elem)
{
    int err = 0;
    
    STACK_ASSERT(stk);
    if ((stk->stk_size) && (stk->stk_capacity))
    {
        if ((stk->stk_capacity)/(stk->stk_size) >= 4)
        {
            (stk->stk_capacity) = (stk->stk_capacity)/3;

            (stk->stk_array) = (StackElem_t*)realloc((stk->stk_array), ((stk->stk_capacity + nCanaries))*sizeof(StackElem_t));
            
            //утечет память
            
            
            for (int i = stk->stk_size + 1; i < stk->stk_capacity; i++)
            {
                if (memcpy(&(stk->stk_array[i]), &Poison, 8))
                    err = 1;
            }
        }
    }

    if (stk->stk_size)
    {
        *elem = (stk->stk_array)[stk->stk_size];
        (stk->stk_array)[stk->stk_size] = Poison;
        (stk->stk_array)[stk->stk_size + 1] = Poison;
        (stk->stk_array)[stk->stk_capacity + 1] = Right_Canary;
        (stk->stk_size)--;
        stk->stk_hash = StackHashFunc(stk);
    }
    else
    {
        fprintf(stk->logfile, "\nyour stack is empty!\n");

        STACK_ASSERT(stk);
        
        return 1;
    }
    
    STACK_ASSERT(stk);
    return err;
}

int StackCtor(Stack_t* stk, StackElem_t fst_elem)
{
    int err = 0;//TODO: сделать как-нибудь

    
    if ((stk->stk_array) = (StackElem_t*)calloc(4, sizeof(StackElem_t)))
    {
        err = 1;
    }
    
    (stk->stk_size) = 1;
    (stk->stk_capacity) = 2;

    (stk->stk_array)[0] = Left_Canary;
    (stk->stk_array)[1] = fst_elem;
    (stk->stk_array)[stk->stk_capacity + 1] = Right_Canary;
    (stk->stk_hash) = StackHashFunc(stk);

    stk->logfile = fopen("log.txt", "w");
    if (stk->logfile == NULL)
    {
        fprintf(stderr, "we couldn't open your logfile");
    }

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

int StackDump(const Stack_t* stk)
{
    int err = 0;
    fprintf(stk->logfile, "Stack capacity: %zu\n", (stk->stk_capacity));
    fprintf(stk->logfile, "Stack size: %zu\n", (stk->stk_size));
    fprintf(stk->logfile, "Stack:\n");
    
    for (size_t elem = 0; elem < (stk->stk_capacity + nCanaries); elem++)
    {
        fprintf(stk->logfile, "%x ", (u_int32_t)(stk->stk_array)[elem]);
    }
    fprintf(stk->logfile, "\n");
    return err;
}


enum errors_t StackError(const Stack_t* stk)
{
    errors_t err = good_stack;
    if(stk->stk_capacity < stk->stk_size)
    {
        err = bad_stk_size;
    }
    if((stk->stk_array)[0] != Left_Canary)
    {
        err = left_canary_died;
    }
    if(((stk->stk_array)[stk->stk_capacity + 1]) != Right_Canary)
    {
        err = right_canary_died;
    }
    if (StackHashFunc(stk) != (stk->stk_hash))
    {
        err = hash_was_died;
    }
    if (stk->logfile == NULL)
    {
        err = bad_log_file;
    }
    
    return err;
}


void StackAssert(const Stack_t* stk, const char *file_name, const int line)
{
    if (errors_t ERROR = StackError(stk))//ERROR->error init in if!!! можно оставить
    {
        fprintf(stk->logfile,"\n\n-----FILE: %s-----linе: %d-----\n\n", file_name, line);
        
        switch (ERROR)
        {
        case bad_stk_size:
            fprintf(stk->logfile, "\n\n------stack_size_error------ == %lg\n\n", 
            (stk->stk_array)[0]);
            break;
        case left_canary_died:
            fprintf(stk->logfile, "\n\n------left_canary_died------%lg\n\n", 
            (stk->stk_array)[0]);
            break;
        case right_canary_died:
            fprintf(stk->logfile, "\n\n------right_canary_died------ == %x\n\n", 
            (u_int32_t)(stk->stk_array)[stk->stk_capacity + 1]);
            break;   
        case hash_was_died:
            fprintf(stk->logfile, "\n\n------hash_was_died------\n"
                    "------EXPECTED:  %lld\n"
                    "------RETURND:  %lld\n", (stk->stk_hash), StackHashFunc(stk));
            break; 
        default:
        fprintf(stderr,"\n\n------POLNYI_PIZDEC------\n\n");
            break;
        }
        StackDump(stk);
        assert(0);
    }
}

hash_t StackHashFunc(const Stack_t* stk)
{
    double  hash = 0;
    for (size_t i = 0; i < (stk->stk_size+1); i++)
    {
        hash += (stk->stk_array)[i]*i;
    }
    hash = (hash_t)hash;
    return hash;
}