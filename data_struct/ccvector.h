#pragma once

typedef struct _CC_VECTOR {
    int *Array;
    int Size;
    int Count;
} CC_VECTOR;

int VecCreate(CC_VECTOR **Vector);
int VecDestroy(CC_VECTOR **Vector);

int VecInsertTail(CC_VECTOR *Vector, int Value);
int VecInsertHead(CC_VECTOR *Vector, int Value);
int VecInsertAfterIndex(CC_VECTOR *Vector, int Index, int Value);
int VecRemoveByIndex(CC_VECTOR *Vector, int Index);
int VecGetValueByIndex(CC_VECTOR *Vector, int Index, int *Value);

// Finds the index where a value appears first. If a value is not found
// "Index" will be -1
// Returns:
//      0 - Success
//     -1 - Error
int VecGetIndexByValue(CC_VECTOR* Vector, int Value, int *Index);

// Swaps two elements by index
// Returns:
//      0 - Success
//     -1 - Error
int VecSwapByIndex(CC_VECTOR* Vector, int FirstIndex, int SecondIndex);

// Verifies if a given index is out of vector's bounds
// Returns:
//      1 - Index is out of vector's bounds
//      0 - Index is NOT out of vector's bounds
//     -1 - Error
int VecIndexOutOfBounds(CC_VECTOR* Vector, int Index);

// Prints all elements in Vector
// Returns:
//      0 - Success
//     -1 - Error
int VecPrintAll(CC_VECTOR* Vector);

// Returns the number of element in Vector or -1 in case of error or invalid parameters
int VecGetCount(CC_VECTOR *Vector);
int VecClear(CC_VECTOR *Vector);

// Sort the vector in decreasing order
int VecSort(CC_VECTOR *Vector);

// Appends all the elements in DestVector to SrcVector
int VecAppend(CC_VECTOR *DestVector, CC_VECTOR *SrcVector);
