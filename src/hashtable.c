/********************************************************************************
 * hashtable.c
 *
 *  Created on: 11/03/2023
 *      Author: Tiago C. Teixeira
 * Description: Implements an hash table data structure in C.
 *
 *  Note: This implementation only uses an array (resizable) with
 *  	  linear prob to store key/values pairs.
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
#include "hashtable.h"

/*
 * Creates a new hash table with default settings (size = 25, LF = 0.75).
 * */
struct hashtable* hashtable_createdefault( int (*hashfunc)(const void* key),
										   int (*isequalfunc)(const void* key1, const void* key2)) {
	struct hashtable* result = hashtable_create( HASHTABLE_DEFAULT_SIZE, HASHTABLE_DEFAULT_LOAD_FACTOR,
												 HASHTABLE_RESIZE_FACTOR,
												 hashfunc, isequalfunc
	);
	return result;
}

/*
 * Creates a new hash table with given initial size and load factor.
 * */
struct hashtable* hashtable_create(int capacity, float loadfactor, float resizefactor,
			int (*hashfunc)(const void* key), int (*isequalfunc)(const void* key1, const void* key2)) {

	assert(capacity > HASHTABLE_MIN_SIZE);
	assert( (loadfactor > 0.1) && (loadfactor < 1.0) );
	assert( (resizefactor > 1.0) && (resizefactor < 10.0) );

	uint arr_size = capacity * sizeof(struct hashtablekeyvaluepair);
	struct hashtable* result = malloc(sizeof(*result) + arr_size);

	if (result == NULL)
		return result;
	else {
		result->capacity = capacity;
		result->loadfactor = loadfactor;
		result->threshold = (int)((float)capacity * loadfactor);

		result->hashfunc = hashfunc;
		result->isequal = isequalfunc;
		result->empty_kvp = malloc(sizeof(struct hashtablekeyvaluepair));
		result->empty_kvp->key = NULL;
		result->empty_kvp->value = NULL;

		int* delk = malloc(sizeof(int)); int* delv = malloc(sizeof(int));
		*delk = -1; *delv = -1;

		//struct hashtablekeyvaluepair* delete_item = malloc(sizeof(*delete_item));
		//delete_item->key = delk;
		//delete_item->key = delv;
		result->deleted_kvp = malloc(sizeof(struct hashtablekeyvaluepair));
		result->deleted_kvp->key = delk;
		result->deleted_kvp->value = delv;
		//result->deleted_kvp = delete_item;

		// initialize hash array with dummy value (empty slots)
		for (int i = 0; i < capacity; ++i) {
			result->harray[i] = malloc(sizeof(*(result->harray[i])));
			result->harray[i]->key = result->empty_kvp->key;
			result->harray[i]->value = result->empty_kvp->value;
		}

		result->count = 0;
		result->resizefactor = HASHTABLE_RESIZE_FACTOR;
	}

	return result;
}

/*
 * Checks if a given hash array slot is empty.
 * Returns 1 if slot is empty, 0 otherwise.
 * */
int hashtable_isempty(const struct hashtable* htable, int slot) {
	struct hashtablekeyvaluepair* item = htable->harray[slot];
	int result = (item->key == NULL);
	return result;
}

/*
 * Checks if a given hash array slot stored a deleted item.
 * Returns 1 if slot stored a deleted item, 0 otherwise.
 * */
int hashtable_isdeleted(struct hashtable* htable, int slot) {
	struct hashtablekeyvaluepair* item = htable->harray[slot];
	int result = htable->isequal(item->key, htable->deleted_kvp->key);
	return result;
}

/*
 * Reallocates all items in the hash table array.
 * Must be invoked every time hash table array if resized.
 * Returns 1 if succeeded, 0 otherwise.
 * */
struct hashtable* hashtable_reallocate(struct hashtable* htable, int new_size) {
	struct hashtable* result = NULL;
	result = hashtable_create(new_size, htable->loadfactor, htable->resizefactor, htable->hashfunc, htable->isequal);
	result->resizefactor = htable->resizefactor;

	int capacity = htable->capacity;
	int count = 0;
	int numItems = htable->count;
	struct hashtablekeyvaluepair* item = NULL;

	// reallocate to new array
	for (int i = 0; i < capacity; ++i) {
		// skip empty and deleted slots
		if ((hashtable_isempty(htable, i)) || (hashtable_isdeleted(htable, i)))
			continue;

		item = htable->harray[i];
		// insert in result array
		if (hashtable_put(result, item->key, item->value)) {

			if (++count == numItems)
				break;
		}
		else {
			// report error
			fprintf(stderr, "Error reallocating item number '%d' in new hash table!", count);
			return NULL;
		}
	}

	// release old instance
	hashtable_destroy(htable);
	return result;
}

/*
 * Adds the key/value to the hash table.
 * Returns 1 if succeeded, 0 otherwise.
 * */
int hashtable_put(struct hashtable* htable, void* key, void* value) {
	int result = 0;
	//struct hashtablekeyvaluepair* kvpp = malloc(sizeof(*kvpp));
	//if (kvpp == NULL) {
	//	return result;
	//}
	//else {
		int hashvalue = htable->hashfunc(key);
		int slot = hashvalue % htable->capacity;

		// move until an empty or deleted slot is found
		while (!hashtable_isempty(htable, slot) && (!hashtable_isdeleted(htable, slot)))
		{
			++slot;
			slot = slot % htable->capacity;	// increment index and wrap around the table
		}

		//kvpp->key = key;
		//kvpp->value = value;

		//htable->harray[slot] = kvpp;	// insert on hash array
		htable->harray[slot]->key = key;
		htable->harray[slot]->value = value;

		htable->count++;

		// if threshold reached, reallocate and re-ash
		if (htable->count == htable->threshold) {
			hashtable_reallocate(htable, htable->resizefactor * (float)(htable->capacity));
		}

		result = 1;
	//}

	return result;
}

/*
 * Gets the value associated with given key.
 * Returns pointer to value if succeeded, NULL otherwise.
 * */
void* hashtable_get(const struct hashtable* htable, const void* key) {
	void* result = NULL;
	int hashvalue = htable->hashfunc(key);
	int slot = hashvalue % htable->capacity;

	if (hashtable_isempty(htable, slot)) {
		// not found
		return result;
	}
	else {
		// note: deleted slots have a dummy value
		// move until an empty slot is found or item found
		while (!hashtable_isempty(htable, slot))  {
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
struct hashtablekeyvaluepair* hashtable_delete(struct hashtable* htable, const void* key) {
	struct hashtablekeyvaluepair* result = NULL;
	int hashvalue = htable->hashfunc(key);
	int slot = hashvalue % htable->capacity;

	if (hashtable_isempty(htable, slot)) {
		// not found
		return result;
	}
	else {
		// note: deleted slots have a dummy value
		// move until an empty slot is found or item found
		while (!hashtable_isempty(htable, slot))  {
			// found item?
			if (htable->isequal(key, htable->harray[slot]->key)) {
				result = htable->harray[slot];
				// set deleted key/value pair in slot
				htable->harray[slot]->key = htable->deleted_kvp->key;
				htable->harray[slot]->value = htable->deleted_kvp->value;
				break;
			}

			++slot;
			slot = slot % htable->capacity;	// increment index and wrap around the table
		}
	}

	return result;
}

/*
 * Release hash table from memory.
 * */
void hashtable_destroy(struct hashtable* htable) {
	free(htable->empty_kvp);
	free(htable->deleted_kvp->key);
	free(htable->deleted_kvp->value);
	free(htable->deleted_kvp);
	for (int i = 0; i < htable->capacity; ++i) {
		free(htable->harray[i]);
	}

	free(htable);
}

