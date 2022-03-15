#include "ccvector.h"
#include "common.h"
#include "string.h"
#include "stdio.h"
#include "time.h"
#include "stdlib.h"

#define INITIAL_SIZE    101

int VecCreate(CC_VECTOR **Vector)
{
    CC_VECTOR *vec = NULL;
    CC_UNREFERENCED_PARAMETER(Vector);

    if (NULL == Vector)
    {
        return -1;
    }

    if (0 != VecDestroy(Vector))
    {
        return -1;
    }

    vec = (CC_VECTOR*)malloc(sizeof(CC_VECTOR));

    if (NULL == vec)
    {
        return -1;
    }

    memset(vec, 0, sizeof(*vec));

    vec->Count = 0;
    vec->Size = INITIAL_SIZE;
    vec->Array = (int*)malloc( sizeof(int) * INITIAL_SIZE );
    if (NULL == vec->Array) 
    {
        free(vec);
        return -1;
    }

    *Vector = vec;

    return 0;
}

int VecDestroy(CC_VECTOR **Vector)
{
    CC_VECTOR *vec = *Vector;

    if (NULL == Vector)
    {
        return -1;
    }
    if (NULL != vec)
    {
        free(vec->Array);
    }

    free(vec);

    *Vector = NULL;

    return 0;
}

int VecRealloc(CC_VECTOR* Vector, int NewSize)
{
    if (NULL == Vector)
    {
        return -1;
    }

    Vector->Size = NewSize;
    int* vecArray = (int*)realloc(Vector->Array, NewSize * sizeof(int));
    if (NULL == vecArray) {
        return -1;
    }
    Vector->Array = vecArray;
    return 0;
}

int VecInsertTail(CC_VECTOR *Vector, int Value)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Vector)
    {
        return -1;
    }

    if (Vector->Count >= Vector->Size)
    {
        //REALLOC
        if (0 != VecRealloc(Vector, Vector->Size * 2))
        {
            return -1;
        }
    }

    Vector->Array[Vector->Count] = Value;
    Vector->Count++;

    return 0;
}

int VecInsertHead(CC_VECTOR *Vector, int Value)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Vector)
    {
        return -1;
    }

    if (Vector->Count >= Vector->Size)
    {
        /// REALLOC
        if (0 != VecRealloc(Vector, Vector->Size * 2))
        {
            return -1;
        }
    }

    for (int i = Vector->Count-1; i >= 0; i--)
    {
        Vector->Array[i + 1] = Vector->Array[i];
    }
    Vector->Array[0] = Value;
    Vector->Count++;

    return 0;
}

int VecInsertAfterIndex(CC_VECTOR *Vector, int Index, int Value)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    CC_UNREFERENCED_PARAMETER(Index);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Vector)
    {
        return -1;
    }
    if ( VecIndexOutOfBounds(Vector, Index) )
    {
        return -1;
    }

    if (Vector->Count >= Vector->Size)
    {
        /// REALLOC
        if (0 != VecRealloc(Vector, Vector->Size * 2))
        {
            return -1;
        }
    }

    for (int i = Vector->Count - 1; i > Index; i--)
    {
        Vector->Array[i + 1] = Vector->Array[i];
    }
    Vector->Array[Index+1] = Value;
    Vector->Count++;

    return 0;
}

int VecRemoveByIndex(CC_VECTOR *Vector, int Index)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    CC_UNREFERENCED_PARAMETER(Index);

    if (NULL == Vector)
    {
        return -1;
    }
    if (VecIndexOutOfBounds(Vector, Index))
    {
        return -1;
    }

    for (int i = Index; i < Vector->Count-1; i++)
    {
        Vector->Array[i] = Vector->Array[i + 1];
    }

    Vector->Count--;

    return 0;
}

int VecGetValueByIndex(CC_VECTOR *Vector, int Index, int *Value)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    CC_UNREFERENCED_PARAMETER(Index);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Vector || NULL == Value)
    {
        return -1;
    }

    if ( VecIndexOutOfBounds(Vector, Index) ) 
    {
        return -1;
    }

    *Value = Vector->Array[Index];

    return 0;
}

int VecGetIndexByValue(CC_VECTOR* Vector, int Value, int* Index)
{
    if (NULL == Vector || NULL == Index)
    {
        return -1;
    }

    int found = 0;
    int retValue = -1;

    for (int i = 0; i < Vector->Count && !found; i++) 
    {
        if (Value == Vector->Array[i])
        {
            retValue = i;
            found = 1;
        }
    }

    *Index = retValue;

    return 0;
}

int VecSwapByIndex(CC_VECTOR* Vector, int FirstIndex, int SecondIndex) {
    if (NULL == Vector)
    {
        return -1;
    }
    if (VecIndexOutOfBounds(Vector, FirstIndex) || VecIndexOutOfBounds(Vector, SecondIndex))
    {
        return -1;
    }

    int aux = Vector->Array[FirstIndex];
    Vector->Array[FirstIndex] = Vector->Array[SecondIndex];
    Vector->Array[SecondIndex] = aux;

    return 0;
}

int VecIndexOutOfBounds(CC_VECTOR* Vector, int Index)
{
    if (NULL == Vector)
    {
        return -1;
    }

    if (Index < 0 || Index >= Vector->Count)
    {
        return 1;
    }

    return 0;
}

int VecPrintAll(CC_VECTOR* Vector) 
{
    if (NULL == Vector)
    {
        return -1;
    }

    if (0 == Vector->Count)
    {
        printf("empty");
    }

    for (int i = 0; i < Vector->Count; i++) {
        int x = 0;
        if (VecGetValueByIndex(Vector, i, &x) == -1)
        {
            return -1;
        }
        printf("%d ", x);
    }
    printf("\n");

    return 0;
}

int VecGetCount(CC_VECTOR *Vector)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    if (NULL == Vector)
    {
        return -1;
    }

    return Vector->Count;
}

int VecClear(CC_VECTOR *Vector)
{
    CC_UNREFERENCED_PARAMETER(Vector);

    if (NULL == Vector)
    {
        return -1;
    }

    Vector->Count = 0;
    
    if (0 != VecRealloc(Vector, INITIAL_SIZE))
    {
        return -1;
    }

    return 0;
}

int VecPartition(int* Arr, int Low, int High)
{
    //srand(time(NULL));
    int random = rand()%(High-Low)+Low;
    int aux = Arr[random];
    Arr[random] = Arr[High];
    Arr[High] = aux;

    int pivot = Arr[High];

    int i = Low - 1;
    for (int j = Low; j < High; j++)
    {
        if (Arr[j] > pivot)
        {
            i++;
            aux = Arr[i];
            Arr[i] = Arr[j];
            Arr[j] = aux;
        }
    }
    aux = Arr[i + 1];
    Arr[i + 1] = Arr[High];
    Arr[High] = aux;
    return i + 1;
}

void VecQuickSort(int* Arr, int Low, int High) 
{
    if (Low < High)
    {
        int pi = VecPartition(Arr, Low, High);

        VecQuickSort(Arr, Low, pi - 1);
        VecQuickSort(Arr, pi + 1, High);
    }
}

int VecSort(CC_VECTOR *Vector)
{
    CC_UNREFERENCED_PARAMETER(Vector);

    if (NULL == Vector)
    {
        return -1;
    }

    if (Vector->Count > 1)
    {
        VecQuickSort(Vector->Array, 0, Vector->Count - 1);
    }

    return 0;
}

int VecAppend(CC_VECTOR *DestVector, CC_VECTOR *SrcVector)
{
    CC_UNREFERENCED_PARAMETER(DestVector);
    CC_UNREFERENCED_PARAMETER(SrcVector);

    if (NULL == DestVector || NULL == SrcVector)
    {
        return -1;
    }

    for (int i = 0; i < DestVector->Count; i++)
    {
        int x = 0;
        if (-1 == VecGetValueByIndex(DestVector, i, &x))
        {
            return -1;
        }
        if (-1 == VecInsertTail(SrcVector, x))
        {
            return -1;
        }
    }

    return 0;
}
