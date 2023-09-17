/********************************************************************************
 * hashtable.c
 *
 *  Created on: 11/03/2023
 *      Author: Tiago C. Teixeira
 * Description: Implements an hash table data structure in C using linear probing
 *  			technique to avoid slot collisions.
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
 *-------------------------------------------------------
 *  Implementation notes
 *
 *  Unlike chaining, open addressing doesn't store multiple elements into the same slot.
 *  Here, each slot is either filled with a single key or left NIL.
 *  To avoid collisions its implemented the linear probing technique.
 *
 *  Linear Probing
 *
 *  In linear probing, collision is resolved by checking the next slot.
 * ------------------------------------------------------
 *
 *  Hashing
 *
 *  Hashing is a technique to convert a range of key values into a range of indexes of an
 *  array. We're going to use modulo operator to get a range of key values.
 *
 *  Source: https://www.tutorialspoint.com/data_structures_algorithms/hash_data_structure.htm
 *
 ***************************************************************************/

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "hashtable_lp.h"

/*
 * Checls if a given number is prime-
 */
int hashtable_lp_check_prime(int n)
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
int hashtable_lp_get_prime(int n)
{
	if (n % 2 == 0) {
		n++;
	}
	while (!hashtable_lp_check_prime(n)) {
	  n += 2;
	}

	return n;
}

/*
 * Computes the threshold value.
 * threshold = capacity * loadfactor
 */
int hashtable_lp_compute_threshold(size_t capacity, float loadfactor)
{
	return (int)((float)capacity * loadfactor);
}

/*
 * Creates a new hash table with default settings (size = 25, LF = 0.75).
 * */
struct hashtable_lp* hashtable_lp_create_default( hashtable_lp_hashfunc hashfunc,
		 	 	 	 	 	 	 	 	 	  	  hashtable_lp_isequal isequalfunc,
												  hashtable_lp_printitem printitemfunc,
												  hashtable_lp_freedata freedatafunc )
{
	struct hashtable_lp* result = hashtable_lp_create( HASHTABLE_LP_DEFAULT_SIZE, HASHTABLE_LP_DEFAULT_LOAD_FACTOR,
												       HASHTABLE_LP_RESIZE_FACTOR,
												       hashfunc, isequalfunc,
													   printitemfunc, freedatafunc );
	return result;
}

/*
 * Initializes hash array
 */
void hashtable_lp_initialize_array(struct hashtable_lp_keyvalue_pair* emptykvp, struct hashtable_lp_keyvalue_pair** array, size_t size)
{
	if (array)
		for (int i = 0; i < size; ++i) {
			array[i] = (struct hashtable_lp_keyvalue_pair*)malloc(sizeof(struct hashtable_lp_keyvalue_pair));
			array[i]->key = emptykvp->key;
			array[i]->value = emptykvp->value;
		}
}

/*
 * Creates a new hash table with given initial size and load factor.
 * */
struct hashtable_lp* hashtable_lp_create( size_t capacity, float loadfactor, float resizefactor,
										  hashtable_lp_hashfunc hashfunc,
										  hashtable_lp_isequal isequalfunc,
										  hashtable_lp_printitem printitemfunc,
										  hashtable_lp_freedata freedatafunc )
{

	assert(capacity > HASHTABLE_LP_MIN_SIZE);
	assert( (loadfactor > 0.1) && (loadfactor < 1.0) );
	assert( (resizefactor > 1.0) && (resizefactor < 10.0) );

	capacity = hashtable_lp_get_prime(capacity);

	struct hashtable_lp* result = malloc(sizeof(*result));

	if (result == NULL)
		return result;
	else {
		uint arr_size = capacity * sizeof(struct hashtable_lp_keyvalue_pair);
		result->harray = (struct hashtable_lp_keyvalue_pair**)malloc(arr_size);
		result->capacity = capacity;
		result->loadfactor = loadfactor;
		result->threshold = hashtable_lp_compute_threshold(capacity, loadfactor);

		result->hashfunc = hashfunc;
		result->isequal = isequalfunc;
		result->printitem = printitemfunc;
		result->freedata = freedatafunc;
		result->empty_kvp = (struct hashtable_lp_keyvalue_pair*)malloc(sizeof(struct hashtable_lp_keyvalue_pair));
		result->empty_kvp->key = NULL;
		result->empty_kvp->value = NULL;

		int* delk = (int*)malloc(sizeof(int)); int* delv = (int*)malloc(sizeof(int));
		*delk = -1; *delv = -1;

		result->deleted_kvp = (struct hashtable_lp_keyvalue_pair*)malloc(sizeof(struct hashtable_lp_keyvalue_pair));
		result->deleted_kvp->key = delk;
		result->deleted_kvp->value = delv;

		// initialize hash array with dummy value (empty slots)
		hashtable_lp_initialize_array(result->empty_kvp, result->harray, capacity);

//		for (int i = 0; i < capacity; ++i) {
//			result->harray[i] = (struct hashtablelpkeyvaluepair)malloc(sizeof(*(result->harray[i])));
//			result->harray[i]->key = result->empty_kvp->key;
//			result->harray[i]->value = result->empty_kvp->value;
//		}

		result->count = 0;
		result->resizefactor = resizefactor;
	}

	return result;
}

/*
 * Checks if a given hash array slot is empty.
 * Returns 1 if slot is empty, 0 otherwise.
 * */
int hashtable_lp_isempty( const struct hashtable_lp* htable, int slot )
{
	struct hashtable_lp_keyvalue_pair* item = htable->harray[slot];
	int result = (item->key == NULL);
	return result;
}

/*
 * Checks if a given hash array slot store a deleted item.
 * Returns 1 if slot store a deleted item, 0 otherwise.
 * */
int hashtable_lp_isdeleted(struct hashtable_lp* htable, int slot) {
	struct hashtable_lp_keyvalue_pair* item = htable->harray[slot];
	int result = htable->isequal(item->key, htable->deleted_kvp->key);
	return result;
}

/*
 * Reallocates all items in the hash table array.
 * Must be invoked every time hashtable array needs to be resized.
 * */
void hashtable_lp_reallocate(struct hashtable_lp* htable, int new_size)
{
	int capacity = htable->capacity;
	struct hashtable_lp_keyvalue_pair* kvp = NULL;
	int hashvalue = -1;
	int slot = -1;

	// create new array
	struct hashtable_lp_keyvalue_pair** new_array =
			(struct hashtable_lp_keyvalue_pair**)malloc(new_size * sizeof(struct hashtable_lp_keyvalue_pair));

	if (new_array == NULL) {
		printf("Memory error: failed to allocate memory for reallocated hashtable array!");
		abort();
	}

	// initialize hash array with dummy value (empty slots)
	hashtable_lp_initialize_array(htable->empty_kvp, new_array, new_size);

	// reallocate to new array
	for (int i = 0; i < capacity; ++i) {
		kvp = htable->harray[i];

		// skip empty and deleted slots
		if ((hashtable_lp_isempty(htable, i)) || (hashtable_lp_isdeleted(htable, i)))
		{
			free(kvp);
			continue;
		}

		hashvalue = htable->hashfunc(kvp->key);
		slot = hashvalue % new_size;

		new_array[slot]->key = kvp->key;
		new_array[slot]->value = kvp->value;

		free(kvp);
	}

	free(htable->harray);
	htable->harray = new_array;
	htable->capacity = new_size;
	htable->threshold = hashtable_lp_compute_threshold(new_size, htable->loadfactor);
}

/*
 * Adds the key/value to the hash table.
 * Returns 1 if succeeded, 0 otherwise.
 * */
int hashtable_lp_put(struct hashtable_lp* htable, void* key, void* value) {
	int result = 0;
	int hashvalue = htable->hashfunc(key);
	int slot = hashvalue % htable->capacity;

	// move until an empty or deleted slot is found
	while (!hashtable_lp_isempty(htable, slot) && (!hashtable_lp_isdeleted(htable, slot)))
	{
		++slot;
		slot = slot % htable->capacity;	// increment index and wrap around the table
	}

	htable->harray[slot]->key = key;
	htable->harray[slot]->value = value;
	htable->count++;

	// if threshold reached, reallocate and re-ash
	if (htable->count == htable->threshold) {
//		printf("Reallocation after inserting %zu elements...\n", htable->count);
		hashtable_lp_reallocate(htable, hashtable_lp_get_prime( htable->resizefactor * (float)(htable->capacity) ) );
//		printf("After reallocating, capacity = %zu ...\n", htable->capacity);
	}

	result = 1;
	return result;
}

/*
 * Checks if hastable contains element with the given key.
 * Returns '1' (true) if succeeded, '0' (false) otherwise.
 * */
int hashtable_lp_contains(const struct hashtable_lp* htable, const void* key)
{
	int result= 0;
	int hashvalue = htable->hashfunc(key);
	int slot = hashvalue % htable->capacity;

	if (hashtable_lp_isempty(htable, slot)) {
		// not found
		return result;
	}
	else {
		// note: deleted slots have a dummy value
		// move until an empty slot is found or item found
		while (!hashtable_lp_isempty(htable, slot))  {
			// found item?
			if (htable->isequal(key, htable->harray[slot]->key)) {
				result = 1;
				break;
			}

			++slot;
			slot = slot % htable->capacity;	// increment index and wrap around the table
		}
	}

	return result;
}

/*
 * Gets the value associated with given key.
 * Returns pointer to value if succeeded, NULL otherwise.
 * */
void* hashtable_lp_get(const struct hashtable_lp* htable, const void* key) {
	void* result = NULL;
	int hashvalue = htable->hashfunc(key);
	int slot = hashvalue % htable->capacity;

	if (hashtable_lp_isempty(htable, slot)) {
		// not found
		return result;
	}
	else {
		// note: deleted slots have a dummy value
		// move until an empty slot is found or item found
		while (!hashtable_lp_isempty(htable, slot))  {
			// found item?
			if (htable->isequal(key, htable->harray[slot]->key)) {
				result = htable->harray[slot]->value;
				break;
			}

			++slot;
			slot = slot % htable->capacity;	// increment index and wrap around the table
		}
	}

	return result;
}

/*
 * Deletes the value associated with given key.
 * Returns pointer to key/value pair if succeeded, NULL otherwise.
 * Note: Deleted bucket will be filled with dummy key/value pair values.
 * */
struct hashtable_lp_keyvalue_pair* hashtable_lp_remove(struct hashtable_lp* htable, const void* key) {
	struct hashtable_lp_keyvalue_pair* result = NULL;
	int hashvalue = htable->hashfunc(key);
	int slot = hashvalue % htable->capacity;

	if (hashtable_lp_isempty(htable, slot)) {
		// not found
		return result;
	}
	else {
		// note: deleted slots have a dummy value
		// move until an empty slot is found or item found
		while (!hashtable_lp_isempty(htable, slot))  {
			// found item?
			if (htable->isequal(key, htable->harray[slot]->key)) {
				result = htable->harray[slot];
				// mark as deleted key/value pair in slot
				struct hashtable_lp_keyvalue_pair* new_kvp =
						(struct hashtable_lp_keyvalue_pair*)malloc(sizeof(*new_kvp));
				htable->harray[slot] = new_kvp;
				htable->harray[slot]->key = htable->deleted_kvp->key;
				htable->harray[slot]->value = htable->deleted_kvp->value;
				htable->count--;
				break;
			}

			++slot;
			slot = slot % htable->capacity;	// increment index and wrap around the table
		}
	}

	return result;
}

/*
 * Prints the hashtable items.
 */
void hashtable_lp_print(struct hashtable_lp* htable)
{
	if (!(htable->printitem)) {
		printf("Error: 'printitem' function is undefined.");
		abort();
	}

	const char* EMPTY_STR = "----EMPTY";
	const char* DELETED_STR = "----DELETED";
	const char* COMMA_STR = ",";
	const char* spaces = " ";

	size_t cap = htable->capacity;
	printf("{\n");
	struct hashtable_lp_keyvalue_pair* kvp = NULL;

	for (int i = 0; i < cap; ++i) {
		kvp = (struct hashtable_lp_keyvalue_pair*)htable->harray[i];

		if (hashtable_lp_isempty(htable, i)) {
			printf("%s%s", spaces, EMPTY_STR);
		}
		else if (hashtable_lp_isdeleted(htable, i)) {
			printf("%s%s", spaces, DELETED_STR);
		}
		else {
			printf("%s", spaces);
			printf("(");
			htable->printitem(kvp);
			printf(")");
		}

		if (i < (cap-1))
			printf("%s", COMMA_STR);
//		printf("\n");
	}

	printf("\n}\n");
}

/*
 * Release hash table from memory.
 * */
void hashtable_lp_destroy(struct hashtable_lp* htable) {
	free(htable->empty_kvp);
	free(htable->deleted_kvp->key);
	free(htable->deleted_kvp->value);
	free(htable->deleted_kvp);
	for (int i = 0; i < htable->capacity; ++i)
	{
		if (htable->freedata)
			if (!hashtable_lp_isempty(htable, i))
				if (!hashtable_lp_isdeleted(htable, i))
					htable->freedata(htable->harray[i]);	// free key and value

		free(htable->harray[i]);					// free kvp structure
	}

	free(htable->harray);
	free(htable);
}

