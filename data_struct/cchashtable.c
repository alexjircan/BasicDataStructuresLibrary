#include <string.h>
#include "cchashtable.h"
#include "common.h"
#include "stdio.h"

#define INITIAL_SIZE    1013

enum {
    FREE,
    OCCUPIED,
    DELETED
};

int HtCreate(CC_HASH_TABLE **HashTable)
{
    CC_UNREFERENCED_PARAMETER(HashTable);

    if (NULL == HashTable)
    {
        return -1;
    }
    if (0 != HtDestroy(HashTable))
    {
        return -1;
    }

    CC_HASH_TABLE* ht = NULL;
    ht = (CC_HASH_TABLE*)malloc(sizeof(CC_HASH_TABLE));

    if(NULL == ht)
    {
        return -1;
    }

    memset(ht, 0, sizeof(*ht));

    ht->Count = 0;
    ht->Array = (CC_HASH_ITEM*)malloc(sizeof(CC_HASH_ITEM) * INITIAL_SIZE);

    if (NULL == ht->Array)
    {
        free(ht);
        return -1;
    }

    memset(ht->Array, 0, sizeof(CC_HASH_ITEM) * INITIAL_SIZE);

    *HashTable = ht;

    return 0;
}

int HtDestroy(CC_HASH_TABLE **HashTable)
{
    CC_UNREFERENCED_PARAMETER(HashTable);

    if (NULL == HashTable)
    {
        return -1;
    }

    CC_HASH_TABLE* ht = *HashTable;

    if (NULL != *HashTable)
    {
        for (int i = 0; i < INITIAL_SIZE; i++)
        {
            if (NULL != ht->Array[i].Key)
            {
                free(ht->Array[i].Key);
            }
        }
        free(ht->Array);
    }

    free(ht);

    *HashTable = NULL;

    return 0;
}

unsigned long HtDjb2(char* Key)
{
    unsigned long hash = 5381;
    int c;

    while (c = *Key++)
    {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

unsigned long HtHashFunction(char* Key, int Index)
{
    return (HtDjb2(Key) % INITIAL_SIZE + Index % INITIAL_SIZE + Index * Index % INITIAL_SIZE) % INITIAL_SIZE;
}

int HtStrLen(char* Str)
{
    int len = 0;
    while (*Str++ != '\0')
    {
        len++;
    }
    return len;
}

void HtStrCpy(char* Dest, char* Src)
{
    while (*Src != '\0')
    {
        *Dest = *Src;
        Dest++;
        Src++;
    }
    *Dest = '\0';
}

int HtStrCmp(char* Str1, char* Str2)
{
    while (*Str1)
    {
        if (*Str1 != *Str2) {
            break;
        }

        Str1++;
        Str2++;
    }

    return *Str1 - *Str2;
}

int HtSetKeyValue(CC_HASH_TABLE *HashTable, char *Key, int Value)
{
    CC_UNREFERENCED_PARAMETER(HashTable);
    CC_UNREFERENCED_PARAMETER(Key);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == HashTable || NULL == Key)
    {
        return -1;
    }

    int index = 0;
    int i = 0;
    for (i = 0; i < INITIAL_SIZE; i++)
    {
        index = HtHashFunction(Key, i);
        if (FREE == HashTable->Array[index].Status || DELETED == HashTable->Array[index].Status)
        {
            HashTable->Array[index].Status = OCCUPIED;
            HashTable->Array[index].Key = (char*)malloc(sizeof(char) * (HtStrLen(Key) + 1));
            HtStrCpy(HashTable->Array[index].Key, Key);
            HashTable->Array[index].Value = Value;
            HashTable->Count++;
            break;
        }
        else if (OCCUPIED == HashTable->Array[index].Status && HtStrCmp(Key, HashTable->Array[index].Key) == 0)
        {
            return -1;
        }
    }

    if (i == INITIAL_SIZE)
    {
        return -1;
    }

    return 0;
}

int HtGetKeyValue(CC_HASH_TABLE *HashTable, char *Key, int *Value)
{
    CC_UNREFERENCED_PARAMETER(HashTable);
    CC_UNREFERENCED_PARAMETER(Key);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == HashTable || NULL == Key || NULL == Value)
    {
        return -1;
    }

    int index = 0;
    for (int i = 0; i < INITIAL_SIZE; i++)
    {
        index = HtHashFunction(Key, i);
        if (FREE == HashTable->Array[index].Status)
        {
            return -1;
        }
        if (OCCUPIED == HashTable->Array[index].Status && 0 == HtStrCmp(HashTable->Array[index].Key, Key))
        {
            *Value = HashTable->Array[index].Value;
            return 0;
        }
    }

    return -1;
}

int HtRemoveKey(CC_HASH_TABLE *HashTable, char *Key)
{
    CC_UNREFERENCED_PARAMETER(HashTable);
    CC_UNREFERENCED_PARAMETER(Key);

    if (NULL == HashTable || NULL == Key)
    {
        return -1;
    }

    int index = 0;
    for (int i = 0; i < INITIAL_SIZE; i++)
    {
        index = HtHashFunction(Key, i);
        if (FREE == HashTable->Array[index].Status)
        {
            return -1;
        }
        if (OCCUPIED == HashTable->Array[index].Status && 0 == HtStrCmp(HashTable->Array[index].Key, Key))
        {
            HashTable->Array[index].Status = DELETED;
            free(HashTable->Array[index].Key);
            HashTable->Array[index].Key = NULL;
            HashTable->Count--;
            return 0;
        }
    }

    return -1;
}

int HtHasKey(CC_HASH_TABLE *HashTable, char *Key)
{
    CC_UNREFERENCED_PARAMETER(HashTable);
    CC_UNREFERENCED_PARAMETER(Key);

    if (NULL == HashTable || NULL == Key)
    {
        return -1;
    }

    int index = 0;
    for (int i = 0; i < INITIAL_SIZE; i++)
    {
        index = HtHashFunction(Key, i);
        if (HashTable->Array[index].Status == FREE)
        {
            return 0;
        }
        if (OCCUPIED == HashTable->Array[index].Status && 0 == HtStrCmp(HashTable->Array[index].Key, Key))
        {
            return 1;
        }
    }

    return 0;
}

int HtGetFirstKey(CC_HASH_TABLE* HashTable, CC_HASH_TABLE_ITERATOR **Iterator, char **Key)
{
    CC_HASH_TABLE_ITERATOR *iterator = NULL;

    CC_UNREFERENCED_PARAMETER(Key);

    if (NULL == HashTable)
    {
        return -1;
    }
    if (NULL == Iterator)
    {
        return -1;
    }
    if (NULL == Key)
    {
        return -1;
    }

    iterator = (CC_HASH_TABLE_ITERATOR*)malloc(sizeof(CC_HASH_TABLE_ITERATOR));
    if (NULL == iterator)
    {
        return -1;
    }

    memset(iterator, 0, sizeof(*iterator));

    iterator->HashTable = HashTable;
    iterator->Index = -1;

    for (int i = 0; i < INITIAL_SIZE; i++) {
        if (OCCUPIED == HashTable->Array[i].Status)
        {
            iterator->Index = i;
            *Key = (char*)malloc(sizeof(char) * (HtStrLen(HashTable->Array[i].Key) + 1));
            HtStrCpy(*Key, HashTable->Array[i].Key);
            break;
        }
    }

    if (-1 == iterator->Index)
    {
        return -2;
    }

    *Iterator = iterator;



    return 0;
}

int HtGetNextKey(CC_HASH_TABLE_ITERATOR *Iterator, char **Key)
{
    CC_UNREFERENCED_PARAMETER(Key);
    CC_UNREFERENCED_PARAMETER(Iterator);

    if (NULL == Iterator || NULL == Key)
    {
        return -1;
    }

    for (int i = Iterator->Index + 1; i < INITIAL_SIZE; i++)
    {
        if (OCCUPIED == Iterator->HashTable->Array[i].Status)
        {
            Iterator->Index = i;
            *Key = (char*)malloc(sizeof(char) * (HtStrLen(Iterator->HashTable->Array[i].Key) + 1));
            HtStrCpy(*Key, Iterator->HashTable->Array[i].Key);
            return 0;
        }
    }

    return -2;
}

int HtReleaseIterator(CC_HASH_TABLE_ITERATOR **Iterator)
{
    CC_UNREFERENCED_PARAMETER(Iterator);

    if (NULL == Iterator)
    {
        return -1;
    }

    CC_HASH_TABLE_ITERATOR* iter = *Iterator;

    if (NULL == iter)
    {
        return -1;
    }

    free(iter);

    *Iterator = NULL;
    
    return 0;
}

int HtClear(CC_HASH_TABLE *HashTable)
{
    CC_UNREFERENCED_PARAMETER(HashTable);

    if (NULL == HashTable)
    {
        return -1;
    }

    for (int i = 0; i < INITIAL_SIZE; i++)
    {
        if (NULL != HashTable->Array[i].Key)
        {
            free(HashTable->Array[i].Key);
        }
    }

    memset(HashTable->Array, 0, sizeof(CC_HASH_ITEM) * INITIAL_SIZE);

    HashTable->Count = 0;

    return 0;
}

int HtGetKeyCount(CC_HASH_TABLE *HashTable)
{
    CC_UNREFERENCED_PARAMETER(HashTable);

    if (NULL == HashTable)
    {
        return -1;
    }

    return HashTable->Count;
}
