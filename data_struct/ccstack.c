#include "ccstack.h"
#include "common.h"
#include "string.h"
#include "stdio.h"

#define INITIAL_SIZE 20

int StCreate(CC_STACK **Stack)
{
    CC_UNREFERENCED_PARAMETER(Stack);
    CC_STACK* stack = NULL;

    if (NULL == Stack)
    {
        return -1;
    }

    if (0 != StDestroy(Stack))
    {
        return -1;
    }

    stack = (CC_STACK*)malloc(sizeof(CC_STACK));

    if (NULL == stack)
    {
        return -1;
    }

    memset(stack, 0, sizeof(*stack));

    stack->Top = 0;
    stack->Size = INITIAL_SIZE;
    stack->Array = (int*)malloc(sizeof(int) * INITIAL_SIZE);
    if (NULL == stack->Array)
    {
        free(stack);
        return -1;
    }

    *Stack = stack;

    return 0;
}

int StDestroy(CC_STACK **Stack)
{
    CC_UNREFERENCED_PARAMETER(Stack);

    CC_STACK* st = *Stack;

    if (NULL == Stack)
    {
        return -1;
    }
    if (NULL != st)
    {
        free(st->Array);
    }

    free(st);

    *Stack = NULL;

    return 0;
}

int StRealloc(CC_STACK* Stack, int NewSize)
{
    CC_UNREFERENCED_PARAMETER(Stack);

    if (NULL == Stack)
    {
        return -1;
    }

    Stack->Size = NewSize;
    int* stArray = (int*)realloc(Stack->Array, NewSize * sizeof(int));
    
    if (NULL == stArray)
    {
        return -1;
    }

    Stack->Array = stArray;

    return 0;
}

int StPush(CC_STACK *Stack, int Value)
{
    CC_UNREFERENCED_PARAMETER(Stack);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Stack)
    {
        return -1;
    }

    if (Stack->Top >= Stack->Size) {
        //REALLOC
        if (0 != StRealloc(Stack, Stack->Size * 2))
        {
            return -1;
        }
    }

    Stack->Array[Stack->Top] = Value;
    Stack->Top++;

    return 0;
}

int StPop(CC_STACK *Stack, int *Value)
{
    CC_UNREFERENCED_PARAMETER(Stack);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Stack)
    {
        return -1;
    }

    if (NULL == Value)
    {
        return -1;
    }

    if (StIsEmpty(Stack))
    {
        return -1;
    }

    Stack->Top --;
    *Value = Stack->Array[Stack->Top];

    return 0;
}

int StPrintAll(CC_STACK* Stack) 
{
    if (NULL == Stack)
    {
        return -1;
    }

    if (0 == Stack->Top)
    {
        printf("empty");
    }

    for (int i = 0; i < Stack->Top; i++)
    {
        printf("%d ", Stack->Array[i]);
    }
    printf("\n");

    return 0;
}

int StPeek(CC_STACK *Stack, int *Value)
{
    CC_UNREFERENCED_PARAMETER(Stack);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Stack)
    {
        return -1;
    }
    if (NULL == Value)
    {
        return -1;
    }

    if ( StIsEmpty(Stack) )
    {
        return -1;
    }

    *Value = Stack->Array[Stack->Top - 1];

    return 0;
}

int StIsEmpty(CC_STACK *Stack)
{
    CC_UNREFERENCED_PARAMETER(Stack);

    if (NULL == Stack)
    {
        return -1;
    }

    if (0 == Stack->Top)
    {
        return 1;
    }

    return 0;
}

int StGetCount(CC_STACK *Stack)
{
    CC_UNREFERENCED_PARAMETER(Stack);

    if (NULL == Stack)
    {
        return -1;
    }

    return Stack->Top;
}

int StClear(CC_STACK *Stack)
{
    CC_UNREFERENCED_PARAMETER(Stack);

    if (NULL == Stack)
    {
        return -1;
    }

    Stack->Top = 0;
    
    if (0 != StRealloc(Stack, INITIAL_SIZE))
    {
        return -1;
    }

    return 0;
}

int StPushStack(CC_STACK *Stack, CC_STACK *StackToPush)
{
    CC_UNREFERENCED_PARAMETER(Stack);
    CC_UNREFERENCED_PARAMETER(StackToPush);

    if (NULL == Stack)
    {
        return -1;
    }

    if (NULL == StackToPush)
    {
        return -1;
    }

    CC_STACK* stackAux = NULL;
    StCreate(&stackAux);

    while (!StIsEmpty(StackToPush))
    {
        int value = 0;
        if (0 != StPop(StackToPush, &value))
        {
            return -1;
        }
        if (0 != StPush(stackAux, value))
        {
            return -1;
        }
    }

    while (!StIsEmpty(stackAux))
    {
        int value = 0;
        if (0 != StPop(stackAux, &value))
        {
            return -1;
        }
        if (0 != StPush(Stack, value))
        {
            return -1;
        }
    }

    StDestroy(&stackAux);

    return 0;
}
