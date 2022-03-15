#include <stdio.h>
#include <string.h>
#include "common.h"
#include "ccvector.h"
#include "ccstack.h"
#include "cchashtable.h"
#include "ccheap.h"
#include "cctree.h"

int TestVector();
int TestStack();
int TestHashTable();
int TestHeap();
int TestTree();

void RunTests();

int main(void)
{
    RunTests();
    return 0;
}

void RunTests()
{
    /// NOTE: The tests provided here are by no means exhaustive and are only
    /// provided as a starting point (not all functions are tested, not all use cases
    /// and failure scenarios are covered). You are encouraged to expand these tests
    /// to include missing scenarios.
    if (0 == TestVector())
    {
        printf("Vector test passed\n\n");
    }
    else
    {
        printf("Vector test failed\n\n");
    }

    if (0 == TestStack())
    {
        printf("Stack test passed\n\n");
    }
    else
    {
        printf("Stack test failed\n\n");
    }

    if (0 == TestHashTable())
    {
        printf("HashTable test passed\n\n");
    }
    else
    {
        printf("HashTable test failed\n\n");
    }

    if (0 == TestHeap())
    {
        printf("Heap test passed\n\n");
    }
    else
    {
        printf("Heap test failed\n\n");
    }

    if (0 == TestTree())
    {
        printf("Tree test passed\n\n");
    }
    else
    {
        printf("Tree test failed\n\n");
    }
}


int TestTree()
{
    int retVal = -1, foundVal = -1;
    CC_TREE* usedTree = NULL;

    retVal = TreeCreate(&usedTree);
    if (0 != retVal)
    {
        printf("TreeCreate failed!\n");
        goto cleanup;
    }

    retVal = TreeInsert(usedTree, 20);
    if (0 != retVal)
    {
        printf("TreeInsert failed!\n");
        goto cleanup;
    }

    retVal = TreeInsert(usedTree, 10);
    if (0 != retVal)
    {
        printf("TreeInsert failed!\n");
        goto cleanup;
    }

    retVal = TreeInsert(usedTree, 5);
    if (0 != retVal)
    {
        printf("TreeInsert failed!\n");
        goto cleanup;
    }

    retVal = TreeInsert(usedTree, 15);
    if (0 != retVal)
    {
        printf("TreeInsert failed!\n");
        goto cleanup;
    }

    retVal = TreeInsert(usedTree, 14);
    if (0 != retVal)
    {
        printf("TreeInsert failed!\n");
        goto cleanup;
    }

    retVal = TreeInsert(usedTree, 17);
    if (0 != retVal)
    {
        printf("TreeInsert failed!\n");
        goto cleanup;
    }

    retVal = TreeInsert(usedTree, 16);
    if (0 != retVal)
    {
        printf("TreeInsert failed!\n");
        goto cleanup;
    }

    retVal = TreeInsert(usedTree, 21);
    if (0 != retVal)
    {
        printf("TreeInsert failed!\n");
        goto cleanup;
    }

    if (1 != TreeContains(usedTree, 20))
    {
        printf("TreeContains invalid return value!\n");
        retVal = -1;
        goto cleanup;
    }

    if (1 != TreeContains(usedTree, 10))
    {
        printf("TreeContains invalid return value!\n");
        retVal = -1;
        goto cleanup;
    }

    if (1 != TreeContains(usedTree, 5))
    {
        printf("TreeContains invalid return value!\n");
        retVal = -1;
        goto cleanup;
    }

    if (8 != TreeGetCount(usedTree))
    {
        printf("TreeGetCount invalid return value!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = TreeGetNthPreorder(usedTree, 2, &foundVal);
    if (-1 == retVal)
    {
        printf("TreeGetNthPreorder failed!\n");
        goto cleanup;
    }

    if (5 != foundVal)
    {
        printf("Invalid value returned!\n");
        goto cleanup;
    }

    retVal = TreeGetNthInorder(usedTree, 2, &foundVal);
    if (-1 == retVal)
    {
        printf("TreeGetNthInorder failed!\n");
        goto cleanup;
    }

    if (14 != foundVal)
    {
        printf("Invalid value returned!\n");
        goto cleanup;
    }

    retVal = TreeGetNthPostorder(usedTree, 2, &foundVal);
    if (-1 == retVal)
    {
        printf("TreeGetNthPostorder failed!\n");
        goto cleanup;
    }

    if (10 != foundVal)
    {
        printf("Invalid value returned!\n");
        goto cleanup;
    }

    retVal = TreeGetHeight(usedTree);
    if (-1 == retVal)
    {
        printf("TreeGetHeight failed!\n");
        goto cleanup;
    }
    if (3 != retVal)
    {
        printf("Invalid height returned!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = TreeRemove(usedTree, 15);
    if (0 != retVal)
    {
        printf("TreeRemove failed!\n");
        goto cleanup;
    }

    if (0 != TreeContains(usedTree, 15))
    {
        printf("TreeContains invalid return value after remove!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = TreeRemove(usedTree, 5);
    if (0 != retVal)
    {
        printf("TreeRemove failed!\n");
        goto cleanup;
    }

    if (0 != TreeContains(usedTree, 5))
    {
        printf("TreeContains invalid return value after remove!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = TreeRemove(usedTree, 14);
    if (0 != retVal)
    {
        printf("TreeRemove failed!\n");
        goto cleanup;
    }

    if (0 != TreeContains(usedTree, 14))
    {
        printf("TreeContains invalid return value after remove!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = TreeRemove(usedTree, 10);
    if (0 != retVal)
    {
        printf("TreeRemove failed!\n");
        goto cleanup;
    }

    if (0 != TreeContains(usedTree, 10))
    {
        printf("TreeContains invalid return value after remove!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = TreeRemove(usedTree, 17);
    if (0 != retVal)
    {
        printf("TreeRemove failed!\n");
        goto cleanup;
    }

    if (0 != TreeContains(usedTree, 17))
    {
        printf("TreeContains invalid return value after remove!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = TreeInsert(usedTree, 16);
    if (0 != retVal)
    {
        printf("TreeInsert failed!\n");
        goto cleanup;
    }

    if (1 != TreeContains(usedTree, 16))
    {
        printf("TreeContains invalid return value!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = TreeRemove(usedTree, 16);
    if (0 != retVal)
    {
        printf("TreeRemove failed!\n");
        goto cleanup;
    }

    if (0 != TreeContains(usedTree, 16))
    {
        printf("TreeContains invalid return value after remove!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = TreeGetHeight(usedTree);
    if (-1 == retVal)
    {
        printf("TreeGetHeight failed!\n");
        goto cleanup;
    }
    if (1 != retVal)
    {
        printf("Invalid height returned!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = TreeClear(usedTree);
    if (-1 == retVal)
    {
        printf("TreeClear failed!\n");
        goto cleanup;
    }

    if (0 != TreeGetCount(usedTree))
    {
        printf("TreeGetCount invalid return value!\n");
        retVal = -1;
        goto cleanup;
    }

cleanup:
    if (NULL != usedTree)
    {
        if (0 != TreeDestroy(&usedTree))
        {
            printf("TreeDestroy failed!\n");
            retVal = -1;
        }
    }
    return retVal;
}

int TestHeap()
{
    int retVal = -1;
    int foundVal = -1;
    CC_HEAP* usedHeap = NULL;

    retVal = HpCreateMinHeap(&usedHeap, NULL);
    if (0 != retVal)
    {
        printf("HpCreateMinHeap failed!\n");
        goto cleanup;
    }

    retVal = HpInsert(usedHeap, 20);
    if (0 != retVal)
    {
        printf("HpInsert failed!\n");
        goto cleanup;
    }

    retVal = HpInsert(usedHeap, 10);
    if (0 != retVal)
    {
        printf("HpInsert failed!\n");
        goto cleanup;
    }

    retVal = HpInsert(usedHeap, 5);
    if (0 != retVal)
    {
        printf("HpInsert failed!\n");
        goto cleanup;
    }

    if (3 != HpGetElementCount(usedHeap))
    {
        printf("Invalid element count!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = HpGetExtreme(usedHeap, &foundVal);
    if (0 != retVal)
    {
        printf("HpGetExtreme failed!\n");
        goto cleanup;
    }

    if (5 != foundVal)
    {
        printf("Invalid minimum value returned!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = HpInsert(usedHeap, 10);
    if (0 != retVal)
    {
        printf("HpInsert failed!\n");
        goto cleanup;
    }

    retVal = HpRemove(usedHeap, 10);
    if (0 != retVal)
    {
        printf("HpRemove failed!\n");
        goto cleanup;
    }

    if (2 != HpGetElementCount(usedHeap))
    {
        printf("Invalid element count!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = HpPopExtreme(usedHeap, &foundVal);
    if (0 != retVal)
    {
        printf("HpPopExtreme failed!\n");
        goto cleanup;
    }

    if (5 != foundVal)
    {
        printf("Invalid minimum value returned!\n");
        retVal = -1;
        goto cleanup;
    }

    CC_HEAP* usedHeap2 = NULL;

    retVal = HpCreateMaxHeap(&usedHeap2, NULL);
    if (0 != retVal)
    {
        printf("HpCreateMaxHeap failed!\n");
        goto cleanup;
    }

    retVal = HpInsert(usedHeap2, 20);
    if (0 != retVal)
    {
        printf("HpInsert failed!\n");
        goto cleanup;
    }

    retVal = HpInsert(usedHeap2, 10);
    if (0 != retVal)
    {
        printf("HpInsert failed!\n");
        goto cleanup;
    }

    retVal = HpInsert(usedHeap2, 5);
    if (0 != retVal)
    {
        printf("HpInsert failed!\n");
        goto cleanup;
    }

    if (3 != HpGetElementCount(usedHeap2))
    {
        printf("Invalid element count!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = HpGetExtreme(usedHeap2, &foundVal);
    if (0 != retVal)
    {
        printf("HpGetExtreme failed!\n");
        goto cleanup;
    }

    if (20 != foundVal)
    {
        printf("Invalid maximum value returned!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = HpInsert(usedHeap2, 10);
    if (0 != retVal)
    {
        printf("HpInsert failed!\n");
        goto cleanup;
    }

    CC_VECTOR* sortedVector = NULL;

    retVal = VecCreate(&sortedVector);
    if (0 != retVal)
    {
        printf("VecCreate failed!\n");
        goto cleanup;
    }

    retVal = HpSortToVector(usedHeap2, sortedVector);
    if (0 != retVal)
    {
        printf("HpSortToVector failed!\n");
        goto cleanup;
    }

    retVal = VecGetValueByIndex(sortedVector, 2, &foundVal);
    if (0 != retVal)
    {
        printf("VecGetValueByIndex failed!\n");
        goto cleanup;
    }

    if (10 != foundVal)
    {
        printf("Invalid value found at position 2\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = HpRemove(usedHeap2, 10);
    if (0 != retVal)
    {
        printf("HpRemove failed!\n");
        goto cleanup;
    }

    if (2 != HpGetElementCount(usedHeap2))
    {
        printf("Invalid element count!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = HpPopExtreme(usedHeap2, &foundVal);
    if (0 != retVal)
    {
        printf("HpPopExtreme failed!\n");
        goto cleanup;
    }

    if (20 != foundVal)
    {
        printf("Invalid maximum value returned!\n");
        retVal = -1;
        goto cleanup;
    }

cleanup:
    if (NULL != usedHeap)
    {
        if (0 != HpDestroy(&usedHeap))
        {
            printf("HpDestroy failed!\n");
            retVal = -1;
        }
    }
    return retVal;
}

int TestHashTable()
{
    int retVal = -1;
    int foundVal = -1;
    CC_HASH_TABLE* usedTable = NULL;

    retVal = HtCreate(&usedTable);
    if (0 != retVal)
    {
        printf("HtCreate failed!\n");
        goto cleanup;
    }

    retVal = HtSetKeyValue(usedTable, "mere", 20);
    if (0 != retVal)
    {
        printf("HtSetKeyValue failed!\n");
        goto cleanup;
    }

    if (1 != HtHasKey(usedTable, "mere"))
    {
        printf("Invalid answer to HtHasKey!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = HtSetKeyValue(usedTable, "pere", 15);
    if (0 != retVal)
    {
        printf("HtSetKeyValue failed!\n");
        goto cleanup;
    }

    if (1 != HtHasKey(usedTable, "pere"))
    {
        printf("Invalid answer to HtHasKey!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = HtGetKeyValue(usedTable, "mere", &foundVal);
    if (0 != retVal)
    {
        printf("HtGetKeyValue failed!\n");
        goto cleanup;
    }

    if (foundVal != 20)
    {
        printf("Invalid value after get!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = HtGetKeyCount(usedTable);
    if (2 != retVal)
    {
        printf("HtGetKeyCount failed!\n");
        goto cleanup;
    }

    char* foundKey = (char*)malloc(sizeof(char) * 10);
    CC_HASH_TABLE_ITERATOR* iterator = (CC_HASH_TABLE_ITERATOR*)malloc(sizeof(CC_HASH_TABLE_ITERATOR));
    retVal = HtGetFirstKey(usedTable, &iterator, &foundKey);
    if (-1 == retVal)
    {
        printf("HtGetFirstKey failed!\n");
        goto cleanup;
    }
    if (0 != strcmp("pere", foundKey))
    {
        printf("Invalid key!\n");
        goto cleanup;
    }

    retVal = HtGetNextKey(iterator, &foundKey);
    if (-1 == retVal)
    {
        printf("HtGetFirstKey failed!\n");
        goto cleanup;
    }
    if (0 != strcmp("mere", foundKey))
    {
        printf("Invalid key!\n");
        goto cleanup;
    }

    retVal = HtReleaseIterator(&iterator);
    if (-1 == retVal)
    {
        printf("HtReleaseIterator failed!\n");
        goto cleanup;
    }


    retVal = HtRemoveKey(usedTable, "pere");
    if (0 != retVal)
    {
        printf("HtRemoveKey failed!\n");
        goto cleanup;
    }

    retVal = HtGetKeyCount(usedTable);
    if (1 != retVal)
    {
        printf("HtGetKeyCount failed!\n");
        goto cleanup;
    }

    retVal = HtClear(usedTable);
    if (0 != retVal)
    {
        printf("HtClear failed!\n");
        goto cleanup;
    }

    retVal = HtGetKeyCount(usedTable);
    if (0 != retVal)
    {
        printf("HtGetKeyCount failed!\n");
        goto cleanup;
    }

cleanup:
    if (NULL != usedTable)
    {
        if (0 != HtDestroy(&usedTable))
        {
            printf("HtDestroy failed!\n");
            retVal = -1;
        }
    }
    return retVal;
}

int TestStack()
{
    int retVal = -1;
    int foundVal = -1;
    CC_STACK* usedStack = NULL;
    CC_STACK* usedStack2 = NULL;
    CC_STACK* usedStack3 = NULL;

    retVal = StCreate(&usedStack);
    if (0 != retVal)
    {
        printf("StCreate failed!\n");
        goto cleanup;
    }

    retVal = StPush(usedStack, 10);
    if (0 != retVal)
    {
        printf("StPush failed!\n");
        goto cleanup;
    }

    retVal = StPush(usedStack, 20);
    if (0 != retVal)
    {
        printf("StPush failed!\n");
        goto cleanup;
    }

    if (0 != StIsEmpty(usedStack))
    {
        printf("Invalid answer to StIsEmpty!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = StPeek(usedStack, &foundVal);
    if (0 != retVal)
    {
        printf("StPeek failed!\n");
        goto cleanup;
    }

    if (foundVal != 20)
    {
        printf("Invalid value after peek!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = StPop(usedStack, &foundVal);
    if (0 != retVal)
    {
        printf("StPop failed!\n");
        goto cleanup;
    }

    if (foundVal != 20)
    {
        printf("Invalid value after pop!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = StClear(usedStack);
    if (0 != retVal)
    {
        printf("StClear failed!\n");
        goto cleanup;
    }

    if (0 != StGetCount(usedStack))
    {
        printf("Invalid count after clear\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = StCreate(&usedStack2);
    if (0 != retVal)
    {
        printf("StCreate failed!\n");
        goto cleanup;
    }

    retVal = StPush(usedStack2, 5);
    if (0 != retVal)
    {
        printf("StPush failed!\n");
        goto cleanup;
    }

    retVal = StPush(usedStack2, 15);
    if (0 != retVal)
    {
        printf("StPush failed!\n");
        goto cleanup;
    }

    retVal = StPush(usedStack, 1);
    if (0 != retVal)
    {
        printf("StPush failed!\n");
        goto cleanup;
    }

    retVal = StPush(usedStack, 2);
    if (0 != retVal)
    {
        printf("StPush failed!\n");
        goto cleanup;
    }

    retVal = StPushStack(usedStack, usedStack2);
    if (0 != retVal)
    {
        printf("StPushStack failed!\n");
        goto cleanup;
    }

    if (4 != StGetCount(usedStack) || 0 != StGetCount(usedStack2))
    {
        printf("Invalid count after pushstack\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = StPeek(usedStack, &foundVal);
    if (0 != retVal)
    {
        printf("StPeek failed!\n");
        goto cleanup;
    }

    if (foundVal != 15)
    {
        printf("Invalid value after peek!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = StCreate(&usedStack3);
    if (0 != retVal)
    {
        printf("StCreate failed!\n");
        goto cleanup;
    }

    retVal = StCreate(&usedStack3);
    if (0 != retVal)
    {
        printf("StCreate failed!\n");
        goto cleanup;
    }

    retVal = StPush(usedStack3, 10);
    if (0 != retVal)
    {
        printf("StPush failed!\n");
        goto cleanup;
    }

    retVal = StPush(usedStack3, 20);
    if (0 != retVal)
    {
        printf("StPush failed!\n");
        goto cleanup;
    }

    retVal = StClear(usedStack3);
    if (0 != retVal)
    {
        printf("StClear failed!\n");
        goto cleanup;
    }

    retVal = StPush(usedStack3, 29);
    if (0 != retVal)
    {
        printf("StPush failed!\n");
        goto cleanup;
    }

    retVal = StPush(usedStack3, 10);
    if (0 != retVal)
    {
        printf("StPush failed!\n");
        goto cleanup;
    }

    //StPrintAll(usedStack3);

cleanup:
    if (NULL != usedStack)
    {
        if (0 != StDestroy(&usedStack))
        {
            printf("StDestroy failed!\n");
            retVal = -1;
        }
    }
    if (NULL != usedStack2)
    {
        if (0 != StDestroy(&usedStack2))
        {
            printf("StDestroy failed!\n");
            retVal = -1;
        }
    }
    if (NULL != usedStack3)
    {
        if (0 != StDestroy(&usedStack3))
        {
            printf("StDestroy failed!\n");
            retVal = -1;
        }
    }
    return retVal;
}

int TestVector()
{
    int retVal = -1;
    int foundVal = 0;
    CC_VECTOR* usedVector = NULL;
    CC_VECTOR* usedVector2 = NULL;
    CC_VECTOR* usedVector3 = NULL;

    retVal = VecCreate(&usedVector);
    if (0 != retVal)
    {
        printf("VecCreate failed!\n");
        goto cleanup;
    }

    retVal = VecInsertTail(usedVector, 10);
    if (0 != retVal)
    {
        printf("VecInsertTail failed!\n");
        goto cleanup;
    }

    retVal = VecInsertHead(usedVector, 16);
    if (0 != retVal)
    {
        printf("VecInsertHead failed!\n");
        goto cleanup;
    }

    if (VecGetCount(usedVector) != 2)
    {
        printf("Invalid count returned!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = VecInsertAfterIndex(usedVector, 0, 20);
    if (0 != retVal)
    {
        printf("VecInsertAfterIndex failed!\n");
        goto cleanup;
    }

    retVal = VecCreate(&usedVector2);
    if (0 != retVal)
    {
        printf("VecCreate failed!\n");
        goto cleanup;
    }

    retVal = VecInsertTail(usedVector2, 10);
    if (0 != retVal)
    {
        printf("VecInsertTail failed!\n");
        goto cleanup;
    }

    retVal = VecInsertHead(usedVector2, 20);
    if (0 != retVal)
    {
        printf("VecInsertHead failed!\n");
        goto cleanup;
    }

    retVal = VecInsertAfterIndex(usedVector2, 1, 5);
    if (0 != retVal)
    {
        printf("VecInsertAfterIndex failed!\n");
        goto cleanup;
    }

    retVal = VecAppend(usedVector, usedVector2);
    if (0 != retVal)
    {
        printf("VecAppend failed!\n");
        goto cleanup;
    }

    if (6 != VecGetCount(usedVector2))
    {
        printf("Invalid count after append\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = VecSort(usedVector2);
    if (0 != retVal)
    {
        printf("VecSort failed!\n");
        goto cleanup;
    }

    retVal = VecGetValueByIndex(usedVector2, 3, &foundVal);
    if (0 != retVal)
    {
        printf("VecGetValueByIndex failed!\n");
        goto cleanup;
    }

    if (10 != foundVal)
    {
        printf("Invalid value found at position 3\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = VecRemoveByIndex(usedVector, 0);
    if (0 != retVal)
    {
        printf("VecRemoveByIndex failed!\n");
        goto cleanup;
    }

    retVal = VecGetValueByIndex(usedVector, 0, &foundVal);
    if (0 != retVal)
    {
        printf("VecGetValueByIndex failed!\n");
        goto cleanup;
    }

    if (foundVal != 20)
    {
        printf("Invalid value found at position 0\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = VecClear(usedVector);
    if (0 != retVal)
    {
        printf("VecClear failed!\n");
        goto cleanup;
    }

    if (0 != VecGetCount(usedVector))
    {
        printf("Invalid count after clear\n");
        retVal = -1;
        goto cleanup;
    }

    
    retVal = VecCreate(&usedVector3);
    if (0 != retVal)
    {
        printf("VecCreate failed!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = VecInsertHead(usedVector3, 16);
    if (0 != retVal)
    {
        printf("VecInsertHead failed!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = VecInsertHead(usedVector3, 28);
    if (0 != retVal)
    {
        printf("VecInsertHead failed!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = VecInsertTail(usedVector3, 25);
    if (0 != retVal)
    {
        printf("VecInsertHead failed!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = VecInsertAfterIndex(usedVector3, 10, 63);
    if (-1 != retVal)
    {
        printf("VecInsertAfterIndex failed!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = VecInsertAfterIndex(usedVector3, -5, 63);
    if (-1 != retVal)
    {
        printf("VecInsertAfterIndex failed!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = VecInsertAfterIndex(usedVector3, 2, 63);
    if (0 != retVal)
    {
        printf("VecInsertAfterIndex failed!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = VecInsertAfterIndex(usedVector3, -1, 26);
    if (-1 != retVal)
    {
        printf("VecInsertAfterIndex failed!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = VecInsertAfterIndex(usedVector3, 10, 26);
    if (-1 != retVal)
    {
        printf("VecInsertAfterIndex failed!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = VecInsertTail(usedVector3, 26);
    if (0 != retVal)
    {
        printf("VecInsertTail failed!\n");
        retVal = -1;
        goto cleanup;
    }

    VecSort(usedVector3);

    retVal = VecGetValueByIndex(usedVector3, -1, &foundVal);
    if (-1 != retVal)
    {
        printf("VecGetValueByIndex failed!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = VecGetValueByIndex(usedVector3, 4, &foundVal);
    if (0 != retVal)
    {
        printf("VecGetValueByIndex failed!\n");
        retVal = -1;
        goto cleanup;
    }

    if (16 != foundVal)
    {
        printf("Invalid value found at position 5!\n");
        retVal = -1;
        goto cleanup;
    }

    VecClear(usedVector3);

    retVal = VecCreate(&usedVector3);
    if (0 != retVal)
    {
        printf("VecCreate failed!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = VecInsertAfterIndex(usedVector3, -1, 26);
    if (-1 != retVal)
    {
        printf("VecInsertAfterIndex failed!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = VecInsertAfterIndex(usedVector3, -1, 67);
    if (-1 != retVal)
    {
        printf("VecInsertAfterIndex failed!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = VecAppend(usedVector3, usedVector2);
    if (0 != retVal)
    {
        printf("VecAppend failed!\n");
        retVal = -1;
        goto cleanup;
    }

    //VecPrintAll(usedVector3);

    retVal = VecGetValueByIndex(usedVector3, 1, &foundVal);
    if (-1 != retVal)
    {
        printf("VecGetValueByIndex failed!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = VecGetValueByIndex(usedVector2, 4, &foundVal);
    if (0 != retVal)
    {
        printf("VecGetValueByIndex failed!\n");
        retVal = -1;
        goto cleanup;
    }
    if (10 != foundVal)
    {
        printf("Invalid value found at position 4!\n");
        retVal = -1;
        goto cleanup;
    }

cleanup:
    if (NULL != usedVector)
    {
        if (0 != VecDestroy(&usedVector))
        {
            printf("VecDestroy failed!\n");
            retVal = -1;
        }
    }
    if (NULL != usedVector2)
    {
        if (0 != VecDestroy(&usedVector2))
        {
            printf("VecDestroy failed!\n");
            retVal = -1;
        }
    }
    if (NULL != usedVector3)
    {
        if (0 != VecDestroy(&usedVector3))
        {
            printf("VecDestroy failed!\n");
            retVal = -1;
        }
    }
    return retVal;
}