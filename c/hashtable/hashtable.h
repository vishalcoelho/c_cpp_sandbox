#ifndef hashtable_h__
#define hashtable_h__

#ifdef __cplusplus
// extern "C"
// {
#endif

#define SIZE_OF_HASH_TABLE (20)

typedef struct Entry_t
{
    int key;
    int value;
} Entry;

typedef Entry *HashTable[SIZE_OF_HASH_TABLE];

/** Insert a key-value pair into the hash table. */
void insert(HashTable table, int key, int value);

/** Search for a key-value pair in the hashtable. */
Entry *search(HashTable table, int key);

/** Remove a key-value pair from the hashtable. */
Entry *del(HashTable table, int key);

/** Print the contents of the hash table. */
void printTable(HashTable table);

/** Print the contents of a single entry. */
void printEntry(Entry *entry);

#ifdef __cplusplus
// }
#endif

#endif /* hashtable_h__ */