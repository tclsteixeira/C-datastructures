/*****************************************************************************
 * hashtable2.c
 *
 *   Created on: 30/08/2023
 *       Author: Tiago C. Teixeira
 *  Description: Implements an hash table data structure in C using list
 *  			 chaining to avoid collisions.
 *
 *-------------------------------------------------------------
 *
 *	Hash table definition
 *
 *  Hash Table is a data structure which stores data in an associative manner.
 *  In a hash table, data is stored in an array format, where each data value has its
 *  own unique index value. Access of data becomes very fast if we know the index of
 *  the desired data.
 *
 *  Thus, it becomes a data structure in which insertion and search operations are very
 *  fast irrespective of the size of the data. Hash Table uses an array as a storage
 *  medium and uses hash technique to generate an index where an element is to be
 *  inserted or is to be located from.
 *
 *-------------------------------------------
 *	Implementation notes
 *
 *  Collision resolution by chaining
 *  In chaining, if a hash function produces the same index for multiple elements, these
 *  elements are stored in the same index by using a linked list.
 *  If j is the slot for multiple elements, it contains a pointer to the head of the list
 *  of elements. If no element is present, j contains NIL.
 *-------------------------------------------
 *
 *  Hashing
 *
 *  Hashing is a technique to convert a range of key values into a range of indexes of an
 *  array. We're going to use modulo operator to get a range of key values.
 *
 *  Source: https://www.tutorialspoint.com/data_structures_algorithms/hash_data_structure.htm
 *
 *******************************************************************************/

#include "hashtable.h"

#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"
#include <assert.h>

/*
 * Checls if a given number is prime-
 */
int hashtable_check_prime(int n)
{
  int i;
  if (n == 1 || n == 0) {
	  return 0;
  }
  for (i = 2; i < n / 2; i++) {
	  if (n % i == 0) {
		return 0;
	  }
  }
  return 1;
}

/*
 * Gets the next prime of a given number.
 */
int hashtable_get_prime(int n)
{
	if (n % 2 == 0) {
		n++;
	}
	while (!hashtable_check_prime(n)) {
	  n += 2;
	}

	return n;
}

/*
 * Computes the threshold value.
 * threshold = capacity * loadfactor
 */
int hashtable_compute_threshold(size_t capacity, float loadfactor)
{
	return (int)((float)capacity * loadfactor);
}

/*
 * Creates a new hash table with given initial size and load factor.
 * Note: freedatafunc function should release key pair key/data.
 * */
struct hashtable* hashtable_create( size_t capacity, float loadfactor, float resizefactor,
									  hashtable_hashfunc hashfunc,
									  hashtable_isequal isequalfunc,
									  hashtable_printitem printitemfunc,
									  hashtable_freedata freedatafunc )
{
	assert(capacity > HASHTABLE_MIN_SIZE);
	assert( (loadfactor > 0.1) && (loadfactor < 1.0) );
	assert( (resizefactor > 1.0) && (resizefactor < 10.0) );

	capacity = hashtable_get_prime(capacity);

	uint arr_size = capacity * sizeof(struct linkedlist);
	struct hashtable* result = malloc(sizeof(*result));

	if (result == NULL)
		return result;
	else {
		result->harray = (struct linkedlist**)malloc(arr_size);
		if (!(result->harray)) {
			printf("Error: failed to allocate memory for hashtable array!");
			abort();
		}

		result->capacity = capacity;
		result->loadfactor = loadfactor;
		result->threshold = hashtable_compute_threshold(capacity, loadfactor);

		result->hashfunc = hashfunc;
		result->isequal = isequalfunc;
		result->printitem = printitemfunc;
		result->freedata = freedatafunc;

		// initialize hash array elements with NULL (empty slots)
		for (int i = 0; i < capacity; ++i) {
			result->harray[i] = NULL;
		}

		result->count = 0;
		result->resizefactor = HASHTABLE_RESIZE_FACTOR;
	}

	return result;
}

/*
 * Creates a new hash table with default settings (size = 16, LF = 0.75).
 * */
struct hashtable* hashtable_create_default( hashtable_hashfunc hashfunc,
		  	  	  	  	  	  	  	  	     hashtable_isequal isequalfunc,
											 hashtable_printitem printitemfunc,
											 hashtable_freedata freedatafunc )
{
	struct hashtable* result = hashtable_create( HASHTABLE_DEFAULT_CAPACITY, HASHTABLE_DEFAULT_LOAD_FACTOR,
 												   HASHTABLE_RESIZE_FACTOR,
	 											   hashfunc, isequalfunc,
												   printitemfunc, freedatafunc
	);

	return result;
}

/*
 * Checks if a given hash array slot is empty.
 * Returns 1 if slot is empty, 0 otherwise.
 * */
int hashtable_isemptybucket(const struct hashtable* htable, int bucket) {
	return ((htable->harray[bucket] == NULL) || (htable->harray[bucket]->size == 0));
}

/*
 * Inserts a new key/value pair in the given hashtable array.
 * Returns: '1' (true) if succeeded, '0' (false) otherwise.
 * Note: does not verify if key already exists in the linked list.
 */
int hashtable_insert_on_array( int bucket,
							   hashtable_isequal isequal,
							   hashtable_freedata freedata,
							   size_t capacity,
						       struct linkedlist** arr, void* key, void* value )
{
	int result = 0;

	struct linkedlist* list = NULL;
	struct hashtable_keyvalue_pair* kvp = NULL;
	kvp = (struct hashtable_keyvalue_pair*)malloc(sizeof(*kvp));
	kvp->key = key;
	kvp->value = value;

	if (arr[bucket] == NULL)
		list = linkedlist_create(isequal, freedata);
	else
		list = arr[bucket];

	if (linkedlist_append(list, kvp)) {
		arr[bucket] = list;
		result = 1;	// succeess
	}
	else {
		printf("Error: failed to append node in linked list of hashtable bucket!");
		abort();
	}

	return result;
}

/*
 * Reallocates all items in the hash table array.
 * Must be invoked every time hash table array if resized.
 * Returns 1 if succeeded, 0 otherwise.
 * */
void hashtable_reallocate( struct hashtable* htable,
										size_t new_size ) {
	int hashvalue = -1;
	int bucket = -1;
	struct linkedlist** new_array = (struct linkedlist**)malloc(sizeof(struct linkedlist) * new_size);

	// important: don't forget to initialize
	for (int i = 0; i < new_size; ++i) {
		new_array[i] = NULL;
	}

	int capacity = htable->capacity;
	int count = 0;
	int numItems = htable->count;
	struct linkedlist* list = NULL;
	struct linkedlistnode* listnode = NULL;
	struct hashtable_keyvalue_pair* kvp = NULL;

	for (int i = 0; i < capacity; ++i) {
		// skip empty buckets
		if (hashtable_isemptybucket(htable, i))
		{
			if (htable->harray[i] != NULL)
				free(htable->harray[i]);
			continue;
		}

		list = htable->harray[i];
		listnode = linkedlist_getfirst(list);

		while (listnode != NULL) {
			kvp = (struct hashtable_keyvalue_pair*)listnode->data;
			hashvalue = htable->hashfunc(kvp->key);
			bucket = hashvalue % new_size;

			if (hashtable_insert_on_array( bucket, htable->isequal,
										   htable->freedata, new_size,
										   new_array, kvp->key, kvp->value)
										 )
			{
				if (++count == numItems) {
					free(kvp);
					break;
				}
			}
			else {
				printf("Function hashtable_reallocate(): Error inserting new item in hashtable array!");
				abort();
			}

			free(kvp);
			listnode = listnode->next;
		}

		linkedlist_destroy(list);
	}

	free(htable->harray);	// release old array
	htable->harray = new_array;
	//htable->count = count; // no need. is the same.
	htable->capacity = new_size;
	htable->threshold = hashtable_compute_threshold(new_size, htable->loadfactor);
//	return result;
}

/*
 * Adds the key/value to the hash table.
 * Returns 1 if succeeded, 0 otherwise.
 * Note: Duplicate keys are not allowed.
 * */
int hashtable_put(struct hashtable* htable, void* key, void* value)
{
	int result = 0;
	int hashvalue = htable->hashfunc(key);
	int bucket = hashvalue % htable->capacity;
	struct linkedlist* list = NULL;
//	struct hashtablekeyvaluepair* kvp = NULL;

//	kvp = (struct hashtablekeyvaluepair*)malloc(sizeof(*kvp));
//	kvp->key = key;
//	kvp->value = value;

	if (hashtable_isemptybucket(htable, bucket)) {

		if (hashtable_insert_on_array( bucket, htable->isequal, htable->freedata,
									   htable->capacity, htable->harray, key, value))
		{
			htable->count++;
			result = 1;	// succeess
		}
		else
		{
			printf("Error: failed to insert key/value pair on hashtable array bucket!");
			abort();
		}
	}
	else {
		// already exists?
		if (hashtable_get(htable, key) != NULL)
		{
			// duplicated keys are not allowed
			printf("Error: failed to insert key in hashtable. Duplicate keys are not allowed.\n");
			return 0;
		}
		else
		{
			if (hashtable_insert_on_array( bucket, htable->isequal, htable->freedata,
										   htable->capacity, htable->harray, key, value))
			{
				htable->harray[bucket] = list;
				htable->count++;
				result = 1;	// succeess
			}
			else
			{
				printf("Error: failed to insert key/value pair on hashtable array bucket!");
				abort();
			}
		}
	}

	// if threshold reached, reallocate and re-hash
	if (htable->count == htable->threshold) {
//		printf("Reallocation after inserting %zu elements...\n", htable->count);
		hashtable_reallocate(htable, hashtable_get_prime( htable->resizefactor * (float)(htable->capacity) ) );
//		printf("After reallocating, capacity = %zu ...\n", htable->capacity);
	}

	return result;
}

/*
 * Checks if the hashtable already contains a given key.
 */
int hashtable_contains(struct hashtable* htable, void* key)
{
	void* el = hashtable_get( htable, key );
	return (el != NULL);
}

/*
 * Gets the value associated with given key.
 * Returns pointer to value if succeeded, NULL otherwise.
 * */
void* hashtable_get(const struct hashtable* htable, const void* key) {
	void* result = NULL;
	int hashvalue = htable->hashfunc(key);
	int bucket = hashvalue % htable->capacity;

	if (hashtable_isemptybucket(htable, bucket)) {
		// not found
		return result;
	}
	else
	{
		struct linkedlist* list = htable->harray[bucket];

		if (list)
		{
			// Note: must scan node by node because list entries are
			// keyvalue pairs, not keys only
			struct linkedlistnode* node = linkedlist_getfirst(list);
			struct hashtable_keyvalue_pair* kvp = NULL;
			while (node) {
				kvp = (struct hashtable_keyvalue_pair*)(node->data);
				if (htable->isequal(kvp->key, key)) {
					result = kvp;
					break;
				}
				else
					node = node->next;
			}
		}
	}

	return result;
}

/*
 * Deletes the key/value pair from the hash table for a given key.
 * Returns removed key/value pair reference if succeeded, NULL otherwise.
 * */
struct hashtable_keyvalue_pair* hashtable_remove(struct hashtable* htable, const void* key)
{
	struct hashtable_keyvalue_pair* result = NULL;
	int hashvalue = htable->hashfunc(key);
	int bucket = hashvalue % htable->capacity;

	if (hashtable_isemptybucket(htable, bucket)) {
		// not found
		return result;
	}
	else {
		struct linkedlist* list = htable->harray[bucket];
		struct linkedlistnode* node = linkedlist_getfirst(list);
		struct linkedlistnode* first = node;
		struct linkedlistnode* prev = NULL;
		struct linkedlistnode* del = NULL;
		struct hashtable_keyvalue_pair* kvp = NULL;
		while (node != NULL) {
			kvp = (struct hashtable_keyvalue_pair*)(node->data);
			if (htable->isequal(key, kvp->key)) {
				if (node == first) {
					del = linkedlist_remove_first(list);
					free(del);
				} else {
					del = node;
					prev->next = node->next;	// remove from list
					node->next = NULL;
					free(del);
				}

				result = kvp;
				htable->count--;
				break;
			} else {
				prev = node;
				node = node->next;
			}
		}
	}

	return result;
}

/*
 * Prints the hashtable items.
 */
void hashtable_print(struct hashtable* htable)
{
	if (!(htable->printitem)) {
		printf("Error: 'printitem' function is undefined.");
		abort();
	}

	char* spaces = "  ";
	printf("{\n");
	struct linkedlist* list = NULL;
	struct linkedlistnode* node = NULL;
	size_t cap = htable->capacity;

	for (int i = 0; i < cap; ++i) {
		list = htable->harray[i];

		if (list == NULL || list->size == 0) {
			printf("%s", spaces);
			printf("empty bucket,");
		}
		else {
			node = linkedlist_getfirst(list);
			while (node != NULL) {
				printf("%s(", spaces);
				htable->printitem( (struct hashtable_keyvalue_pair*)(node->data) );
				printf(")");

				if (i < (cap-1))
					printf(" --> end");

//				printf("\n");
				node = node->next;
			}
		}

		printf("\n");
	}

	printf("}\n");
}

/*
 * Shallow copies all keys from the hashtable to an array.
 * You have to free result array from memory later in your code.
 */
void** hashtable_keys(struct hashtable* htable)
{
	void** result = NULL;

	if (htable->count > 0)
	{
		result = (void**)malloc(sizeof(void*) * htable->count);

		struct linkedlist* list = NULL;
		struct linkedlistnode* node = NULL;
		int index = 0;

		for (int i = 0; i < htable->capacity; ++i) {
			list = htable->harray[i];

			if (!(list == NULL || list->size == 0))
			{
				node = linkedlist_getfirst(list);
				while (node != NULL) {
					result[index++] = ((struct hashtable_keyvalue_pair*)(node->data))->key;
					node = node->next;
				}
			}

			if (index == htable->count)
				break;
		}
	}

	return result;
}

/*
 * Shallow copies all key/value pairs from the hashtable to an array.
 * You have to free result array from memory later in your code.
 */
struct hashtable_keyvalue_pair** hashtable_toarray(struct hashtable* htable)
{
	struct hashtable_keyvalue_pair** result = NULL;

	if (htable->count > 0)
	{
		result = (struct hashtable_keyvalue_pair**)malloc(sizeof(struct hashtable_keyvalue_pair*) * htable->count);

		struct linkedlist* list = NULL;
		struct linkedlistnode* node = NULL;
		int index = 0;

		for (int i = 0; i < htable->capacity; ++i) {
			list = htable->harray[i];

			if (!(list == NULL || list->size == 0))
			{
				node = linkedlist_getfirst(list);
				while (node != NULL) {
					result[index++] = (struct hashtable_keyvalue_pair*)(node->data);
					node = node->next;
				}
			}

			if (index == htable->count)
				break;
		}
	}

	return result;
}

/*
 * Removes all elements from the hashtable.
 * */
void hashtable_clear(struct hashtable* htable)
{
	int size = htable->capacity;
	struct linkedlist* list = NULL;

	for (int i = 0; i < size; ++i) {
		list = htable->harray[i];
		if (list != NULL) {
			linkedlist_destroy(list);
			htable->harray[i] = NULL;
		}
	}

	htable->count = 0;
}

/*
 * Releases the hash table from memory.
 * */
void hashtable_destroy(struct hashtable* htable)
{
	struct linkedlist* list = NULL;
	struct linkedlistnode* node = NULL;

	for (int i = 0; i < htable->capacity; ++i) {
		list = htable->harray[i];
		if (list != NULL) {
			// must release data (key/value pair) from node by node
			node = linkedlist_getfirst(list);
			while (node) {
				if (htable->freedata)
					htable->freedata(node->data);
				else
					free(node->data);

				node = node->next;
			}

			linkedlist_destroy(list);
		}
	}

	free(htable->harray);
	free(htable);
}



