#include "ccheap.h"
#include "common.h"
#include "string.h"
#include "stdio.h"

#define INITIAL_SIZE    100

enum {
    MAX_HEAP,
    MIN_HEAP
};


void HpHeapifyDown(CC_HEAP* Heap, int Index)
{
    int size = VecGetCount(Heap->Vector);

    int indexLargest = Index;
    int indexLeft = 2 * Index + 1;
    int indexRight = 2 * Index + 2;

    int largest = 0;
    int left = 0;
    int right = 0;

    VecGetValueByIndex(Heap->Vector, indexLargest, &largest);
    VecGetValueByIndex(Heap->Vector, indexLeft, &left);
    VecGetValueByIndex(Heap->Vector, indexRight, &right);

    if (MAX_HEAP == Heap->Type)
    {
        if (indexLeft < size && left > largest)
        {
            indexLargest = indexLeft;
        }

        VecGetValueByIndex(Heap->Vector, indexLargest, &largest);

        if (indexRight < size && right > largest)
        {
            indexLargest = indexRight;
        }
    }
    else
    {
        if (indexLeft < size && left < largest)
        {
            indexLargest = indexLeft;
        }

        VecGetValueByIndex(Heap->Vector, indexLargest, &largest);

        if (indexRight < size && right < largest)
        {
            indexLargest = indexRight;
        }
    }

    if (indexLargest != Index)
    {
        VecSwapByIndex(Heap->Vector, Index, indexLargest);

        HpHeapifyDown(Heap, indexLargest);
    }
}

void HpHeapifyUp(CC_HEAP* Heap, int Index)
{
    int currentIndex = Index;

    if (currentIndex != 0)
    {
        int parentIndex = (currentIndex - 1) / 2;
        int current = 0;
        int parent = 0;

        VecGetValueByIndex(Heap->Vector, currentIndex, &current);
        VecGetValueByIndex(Heap->Vector, parentIndex, &parent);

        if (MIN_HEAP == Heap->Type)
        {
            while (parent > current && 0 != currentIndex)
            {
                VecSwapByIndex(Heap->Vector, parentIndex, currentIndex);
                currentIndex = parentIndex;
                parentIndex = (currentIndex - 1) / 2;
                VecGetValueByIndex(Heap->Vector, currentIndex, &current);
                VecGetValueByIndex(Heap->Vector, parentIndex, &parent);
            }
        }
        else
        {
            while (parent < current && 0 != current)
            {
                VecSwapByIndex(Heap->Vector, parentIndex, currentIndex);
                currentIndex = parentIndex;
                parentIndex = (currentIndex - 1) / 2;
                VecGetValueByIndex(Heap->Vector, currentIndex, &current);
                VecGetValueByIndex(Heap->Vector, parentIndex, &parent);
            }
        }

    }
}

int HpCreateMaxHeap(CC_HEAP **MaxHeap, CC_VECTOR* InitialElements)
{
    CC_UNREFERENCED_PARAMETER(MaxHeap);
    CC_UNREFERENCED_PARAMETER(InitialElements);

    CC_HEAP* hp = *MaxHeap;

    if (NULL == MaxHeap)
    {
        return -1;
    }

    if (0 != HpDestroy(MaxHeap))
    {
        return -1;
    }

    hp = (CC_HEAP*)malloc(sizeof(CC_HEAP));

    if (NULL == hp)
    {
        return -1;
    }

    memset(hp, 0, sizeof(*hp));

    hp->Type = MAX_HEAP;

    if (0 != VecCreate(&hp->Vector))
    {
        return -1;
    }


    if (NULL == InitialElements)
    {
        *MaxHeap = hp;
        return 0;
    }

    VecAppend(InitialElements, hp->Vector);

    int startIndex = (VecGetCount(InitialElements) / 2) - 1;

    for (int i = startIndex; i >= 0; i--)
    {
        HpHeapifyDown(hp, i);
    }

    *MaxHeap = hp;

    return 0;
}

int HpCreateMinHeap(CC_HEAP **MinHeap, CC_VECTOR* InitialElements)
{
    CC_UNREFERENCED_PARAMETER(MinHeap);
    CC_UNREFERENCED_PARAMETER(InitialElements);

    CC_HEAP* hp = *MinHeap;

    if (NULL == MinHeap)
    {
        return -1;
    }

    if (0 != HpDestroy(MinHeap))
    {
        return -1;
    }

    hp = (CC_HEAP*)malloc(sizeof(CC_HEAP));

    if (NULL == hp)
    {
        return -1;
    }

    memset(hp, 0, sizeof(*hp));

    hp->Type = MIN_HEAP;

    if (0 != VecCreate(&hp->Vector))
    {
        return -1;
    }

    if (NULL == InitialElements)
    {
        *MinHeap = hp;
        return 0;
    }

    VecAppend(InitialElements, hp->Vector);

    int startIndex = (VecGetCount(InitialElements) / 2) - 1;

    for (int i = startIndex; i >= 0; i--)
    {
        HpHeapifyDown(hp, i);
    }

    *MinHeap = hp;

    return 0;
}

int HpDestroy(CC_HEAP **Heap)
{
    CC_UNREFERENCED_PARAMETER(Heap);

    if (NULL == Heap)
    {
        return -1;
    }

    CC_HEAP* hp = *Heap;

    if (NULL != *Heap)
    {
        if (0 != VecDestroy(&(hp->Vector)))
        {
            return -1;
        }
    }

    free(hp);

    *Heap = NULL;

    return 0;
}

int HpInsert(CC_HEAP *Heap, int Value)
{
    CC_UNREFERENCED_PARAMETER(Heap);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Heap)
    {
        return -1;
    }

    if (0 != VecInsertTail(Heap->Vector, Value))
    {
        return -1;
    }

    HpHeapifyUp(Heap, VecGetCount(Heap->Vector) - 1);

    return 0;
}

int HpPrintAll(CC_HEAP* Heap)
{
    if (NULL == Heap)
    {
        return -1;
    }

    if (MIN_HEAP == Heap->Type)
    {
        printf("Min Heap: ");
    }
    else
    {
        printf("Max Heap: ");
    }

    VecPrintAll(Heap->Vector);

    return 0;
}

int HpRemoveByIndexUtil(CC_HEAP* Heap, int Index)
{
    if (NULL == Heap)
    {
        return -1;
    }

    if (0 != VecIndexOutOfBounds(Heap->Vector, Index))
    {
        return -1;
    }

    VecSwapByIndex(Heap->Vector, Index, VecGetCount(Heap->Vector) - 1);

    VecRemoveByIndex(Heap->Vector, VecGetCount(Heap->Vector) - 1);

    int parentIndex = (Index - 1) / 2;
    int current = 0;
    int parent = 0;

    VecGetValueByIndex(Heap->Vector, Index, &current);
    VecGetValueByIndex(Heap->Vector, parentIndex, &parent);

    if (MIN_HEAP == Heap->Type)
    {
        if (parent > current)
        {
            HpHeapifyUp(Heap, Index);
        }
        else
        {
            HpHeapifyDown(Heap, Index);
        }
    }
    else
    {
        if (parent < current)
        {
            HpHeapifyUp(Heap, Index);
        }
        else
        {
            HpHeapifyDown(Heap, Index);
        }
    }

    return 0;
}

int HpRemove(CC_HEAP *Heap, int Value)
{
    CC_UNREFERENCED_PARAMETER(Heap);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Heap)
    {
        return -1;
    }

    int index = 0;
    VecGetIndexByValue(Heap->Vector, Value, &index);

    while (index != -1)
    {
        HpRemoveByIndexUtil(Heap, index);
        VecGetIndexByValue(Heap->Vector, Value, &index);
    }

    return 0;
}

int HpGetExtreme(CC_HEAP *Heap, int* ExtremeValue)
{
    CC_UNREFERENCED_PARAMETER(Heap);
    CC_UNREFERENCED_PARAMETER(ExtremeValue);

    if (NULL == Heap || NULL == ExtremeValue)
    {
        return -1;
    }

    int retValue = 0;
    if (0 != VecGetValueByIndex(Heap->Vector, 0, &retValue))
    {
        return -1;
    }

    *ExtremeValue = retValue;

    return 0;
}

int HpPopExtreme(CC_HEAP *Heap, int* ExtremeValue)
{
    CC_UNREFERENCED_PARAMETER(Heap);
    CC_UNREFERENCED_PARAMETER(ExtremeValue);

    if (NULL == Heap || NULL == ExtremeValue)
    {
        return -1;
    }

    int foundValue = 0;
    if (0 != VecGetValueByIndex(Heap->Vector, 0, &foundValue))
    {
        return -1;
    }

    *ExtremeValue = foundValue;

    HpRemove(Heap, foundValue);

    return 0;
}

int HpGetElementCount(CC_HEAP *Heap)
{
    CC_UNREFERENCED_PARAMETER(Heap);

    if (NULL == Heap)
    {
        return -1;
    }

    return VecGetCount(Heap->Vector);
}

int HpRemoveSort(CC_HEAP* Heap, int Value)
{
    CC_UNREFERENCED_PARAMETER(Heap);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Heap)
    {
        return -1;
    }

    int index = 0;
    VecGetIndexByValue(Heap->Vector, Value, &index);

    if (index != -1)
    {
        HpRemoveByIndexUtil(Heap, index);
    }

    return 0;
}

int HpPopExtremeSort(CC_HEAP* Heap, int* ExtremeValue)
{
    CC_UNREFERENCED_PARAMETER(Heap);
    CC_UNREFERENCED_PARAMETER(ExtremeValue);

    if (NULL == Heap || NULL == ExtremeValue)
    {
        return -1;
    }

    int foundValue = 0;
    if (0 != VecGetValueByIndex(Heap->Vector, 0, &foundValue))
    {
        return -1;
    }

    *ExtremeValue = foundValue;

    HpRemoveSort(Heap, foundValue);

    return 0;
}

int HpSortToVector(CC_HEAP* Heap, CC_VECTOR* SortedVector)
{
    CC_UNREFERENCED_PARAMETER(Heap);
    CC_UNREFERENCED_PARAMETER(SortedVector);

    if (NULL == Heap || NULL == SortedVector)
    {
        return -1;
    }

    VecClear(SortedVector);

    CC_HEAP* auxHp = NULL;

    if (0 != HpCreateMinHeap(&auxHp, Heap->Vector))
    {
        return -1;
    }

    int foundVal = 0;
    while (0 == HpPopExtremeSort(auxHp, &foundVal))
    {
        VecInsertTail(SortedVector, foundVal);
    }

    if (0 != HpDestroy(&auxHp))
    {
        return -1;
    }

    return 0;
}
