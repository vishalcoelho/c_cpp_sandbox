#include "hashtable.h"

#include <stdio.h>
#include <stdlib.h>

/* Prototypes */
static int hashKey(int key);
static void createEntryAtIndex(HashTable table, int index, int key, int value);
static int searchAndGetIndex(HashTable table, int key);

void insert(HashTable table, int key, int value)
{
    int index = hashKey(key);
    if (NULL == table[index])
    {
        createEntryAtIndex(table, index, key, value);
    }
    else
    {
        // location is occupied. find next empty spot to place it.
        int conflictIndex = index;
        index = (index + 1) % SIZE_OF_HASH_TABLE;

        while ((index != conflictIndex) && (NULL != table[index]))
        {
            // Keep checking the next index till you find an empty postion or
            // have come full circle.
            index = (index + 1) % SIZE_OF_HASH_TABLE;
        }

        if (index != conflictIndex)
            createEntryAtIndex(table, index, key, value);
    }
}

static int hashKey(int key)
{
    return key % SIZE_OF_HASH_TABLE;
}

static void createEntryAtIndex(HashTable table, int index, int key, int value)
{
    // No entry at this location yet. Add it.
    Entry *entry = (Entry *)malloc(sizeof(Entry));
    if (entry)
    {
        entry->key = key;
        entry->value = value;
        table[index] = entry;
    }
}

Entry *search(HashTable table, int key)
{
    int index = hashKey(key);
    Entry *entry = table[index];

    if ((NULL != entry) && (entry->key == key))
    {
        // found it, return.
        return entry;
    }
    else
    {
        // there must have been a collision, search the table linearly till i
        // find a match
        int origIndex = index;
        index = ++index % SIZE_OF_HASH_TABLE;

        while (index != origIndex)
        {
            if (NULL != table[index])
            {
                if (table[index]->key == key)
                    return table[index];
            }
            index = ++index % SIZE_OF_HASH_TABLE;
        }
    }

    return NULL;
}

Entry *del(HashTable table, int key)
{
    int index = searchAndGetIndex(table, key);
    if (-1 != index)
    {
        // found a match
        Entry *entry = table[index];
        table[index] = NULL;
        return entry;
    }
    else
    {
        return NULL;
    }
}

static int searchAndGetIndex(HashTable table, int key)
{
    int index = hashKey(key);
    Entry *entry = table[index];

    if ((NULL != entry) && (entry->key == key))
    {
        // found it, return.
        return index;
    }
    else // null entry || mimatched key(collision)
    {
        // there must have been a collision, search the table linearly till i
        // find a match
        int origIndex = index;
        index = ++index % SIZE_OF_HASH_TABLE;

        while (index != origIndex)
        {
            if (NULL != table[index])
            {
                if (table[index]->key == key)
                    return index;
            }
            index = ++index % SIZE_OF_HASH_TABLE;
        }
    }

    return -1;
}

void printTable(HashTable table)
{
    printf("+--Table--+\n");
    for (int i = 0; i < SIZE_OF_HASH_TABLE; i++)
    {
        Entry *entry = table[i];
        if (entry)
        {
            printf("|%2d|%2d->%2d|\n", i, entry->key, entry->value);
        }
        else
        {
            printf("|%2d| empty|\n", i);
        }
    }
    printf("+---Done--+\n");
}

void printEntry(Entry *entry)
{
    if (entry)
    {
        printf("found:%d->%d\n", entry->key, entry->value);
    }
    else
    {
        printf("not found.\n");
    }
}

/* array of 'Entry' pointers. */
Entry *hashTable[SIZE_OF_HASH_TABLE];

int main(void)
{

    // Test 1: Insertion
    printf("=====Test1:Insertion=====\n");
    insert(hashTable, 44, 45);
    insert(hashTable, 46, 47);
    insert(hashTable, 48, 49);
    insert(hashTable, 50, 51);
    printTable(hashTable);
    insert(hashTable, 0, 33);
    insert(hashTable, 1, 34);
    insert(hashTable, 2, 35);
    insert(hashTable, 3, 36);
    insert(hashTable, 4, 37); // conflicts with (44,45), should be palced at index 5
    printTable(hashTable);

    // Test 2: Searching
    printf("=====Test2:Search=====\n");
    printEntry(search(hashTable, 4));
    printEntry(search(hashTable, 5));
    printEntry(search(hashTable, 6));
    printEntry(search(hashTable, 0));
    printEntry(search(hashTable, 7));

    // Test 3: Deleting
    printf("=====Test3:Deletion=====\n");
    printEntry(del(hashTable, 0)); // exists, should null out entry
    printTable(hashTable);
    printEntry(del(hashTable, 7)); // doesnt exist
    printTable(hashTable);
    printEntry(del(hashTable, 4)); // exists at a collision index, should null out entry
    printTable(hashTable);
    printEntry(del(hashTable, 0)); // delete already deleted entry
    printTable(hashTable);

    // Test 4: Re-insertion
    printf("=====Test4:Re-insertion=====\n");
    insert(hashTable, 0, 33);
    printTable(hashTable);

    return 0;
}