#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void swap_f(void* a, void* b, size_t nBytes);
void BubbleSort(int* arr, size_t size, size_t* nChanges);
void ShakerSort(int* array, size_t array_size, size_t* nChanges);
void ImplicSort(int* array, size_t array_size, size_t* nChanges);
void mergesort(size_t array_size, int* array);
int main()
{
    size_t array_size;
    size_t nChanges = 0;

    printf("Enter amount of elements:   ");
    scanf("%lu", &array_size);
    
    int orig_array[array_size];
    printf("Enter elems:\n");
    for (size_t i = 0; i < array_size; i++)
    {
        scanf("%d", &orig_array[i]);
    }


    int temp_array[array_size];
    for (size_t i = 0; i < array_size; i++)
    {
        temp_array[i] = orig_array[i];
    }
    
    BubbleSort(temp_array, array_size, &nChanges);
    printf("Bubble Sort:\n");
    for (size_t i = 0; i < array_size; i++)
    {
        printf("%d ", temp_array[i]);
    }
    printf("\namount of changes:    %lu\n", nChanges);

    for (size_t i = 0; i < array_size; i++)
    {
        temp_array[i] = orig_array[i];
    }
    
    ShakerSort(temp_array, array_size, &nChanges);
    printf("Shaker Sort:\n");
    for (size_t i = 0; i < array_size; i++)
    {
        printf("%d ", temp_array[i]);
    }
    printf("\namount of changes:    %lu\n", nChanges);

    for (size_t i = 0; i < array_size; i++)
    {
        temp_array[i] = orig_array[i];
    }
    
    mergesort(array_size, temp_array);
    printf("Merge Sort:\n");
    for (size_t i = 0; i < array_size; i++)
    {
        printf("%d ", temp_array[i]);
    }
}

void swap_f(void* a, void* b, size_t nBytes)
{
    char* temp_elem = (char*)malloc(nBytes);
    memcpy(temp_elem, a, nBytes);
    memcpy(a, b, nBytes);
    memcpy(b, temp_elem, nBytes);
    free(temp_elem);
}

void BubbleSort(int* array, size_t array_size, size_t* nChanges)
{
        for (size_t i = 0; i < array_size; i++)
    {
        for (size_t i = 0; i < array_size - 1; i++)
        {
            if (array[i] > array[i+1])
            {
                swap_f(&array[i], &array[i+1], sizeof(int));
            }
            (*nChanges)++;
        }   
    }
}

void ShakerSort(int* array, size_t array_size, size_t* nChanges)
{
    size_t leftMark = 1;
    size_t rightMark = array_size - 1;
    size_t i = 0;
    while(leftMark <= rightMark)
    {
        for (i = rightMark; i > leftMark; i--)
        {
            if (array[i - 1] > array[i]) 
                swap_f(&array[i - 1], &array[i], sizeof(int));
            (*nChanges)++;
        }
        leftMark++;
        for (i = leftMark; i < rightMark; i++)
        {
            if (array[i] > array[i + 1]) 
                swap_f(&array[i], &array[i + 1], sizeof(int));
            (*nChanges)++;
        }
        rightMark--;   
    }
}
void mergesort(size_t array_size, int* array)
{
    int rght, rend;
    int i, j, m;
 
    int* temp_array = (int*)calloc(array_size, sizeof(int));
    for (int k = 1; k < array_size; k *= 2)
    {
        for (int left = 0; left + k < array_size; left += k * 2)
        {
            rght = left + k;
            rend = rght + k;
            if (rend > array_size) rend = array_size;
            m = left; i = left; j = rght;
            while (i < rght && j < rend)
            {
                if (array[i] <= array[j])
                {
                    temp_array[m] = array[i]; i++;
                }
                else
                {
                    temp_array[m] = array[j]; j++;
                }
                m++;
            }
            while (i < rght)
            {
                temp_array[m] = array[i];
                i++; m++;
            }
            while (j < rend)
            {
                temp_array[m] = array[j];
                j++; m++;
            }
            for (m = left; m < rend; m++)
            {
                array[m] = temp_array[m];
            }
        }
    }
    free(temp_array);
}
