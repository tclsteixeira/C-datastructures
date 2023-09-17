
/*****************************************************************************
 * hashtable2.h
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
 *--------------------------------------------
 *	Implementation notes
 *
 *  Collision resolution by chaining
 *  In chaining, if a hash function produces the same index for multiple elements, these
 *  elements are stored in the same index by using a linked list.
 *  If j is the slot for multiple elements, it contains a pointer to the head of the list
 *  of elements. If no element is present, j contains NIL.
 *--------------------------------------------
 *
 *  Hashing
 *
 *  Hashing is a technique to convert a range of key values into a range of indexes of an
 *  array. We're going to use modulo operator to get a range of key values.
 *
 *  Source: https://www.tutorialspoint.com/data_structures_algorithms/hash_data_structure.htm
 *
 *******************************************************************************/

#ifndef HASHTABLE_H_
	#define HASHTABLE_H_

	#include <stdlib.h>
	#include "linkedlist.h"

	#define HASHTABLE_DEFAULT_CAPACITY 16
	#define HASHTABLE_DEFAULT_LOAD_FACTOR 0.75
	#define HASHTABLE_MIN_SIZE 10
	#define HASHTABLE_RESIZE_FACTOR 2.0

	// key/value pair type
	struct hashtable_keyvalue_pair {
		void* key;
		void* value;
	};

	typedef void (*hashtable_freedata)(void* data);
	typedef int (*hashtable_isequal)(const void* key1, const void* key2);
	typedef int (*hashtable_hashfunc)(const void* key);
	typedef void (*hashtable_printitem)(const struct hashtable_keyvalue_pair* kvp);

	// hash table type
	struct hashtable {
		size_t count;									// number of elements in the hashtable
		size_t capacity;								// size of hash array
		hashtable_hashfunc hashfunc;					// hash function
		hashtable_isequal isequal;						// key compare for equality function
		hashtable_freedata freedata;					// release key/value pair from memory
		hashtable_printitem printitem;					// prints key/value pair
		int threshold;									// limit array size to rise a reallocation (loadfactor * capacity)
		float loadfactor;								// fraction of hash array filled to generate a reallocation
		float resizefactor;								// to compute new hash array size for reallocation (new_size = resizefactor * capacity)
		struct linkedlist** harray;						// hash array
	};

	/*
	 * Creates a new hash table with default settings (size = 25, LF = 0.75).
	 * */
	struct hashtable* hashtable_create_default( hashtable_hashfunc hashfunc,
											    hashtable_isequal isequalfunc,
											    hashtable_printitem printitemfunc,
											    hashtable_freedata freedatafunc );

	/*
	 * Creates a new hash table with given initial size and load factor.
	 * */
	struct hashtable* hashtable_create( size_t size, float loadfactor, float resizefactor,
									    hashtable_hashfunc hashfunc,
										hashtable_isequal isequalfunc,
										hashtable_printitem printitemfunc,
										hashtable_freedata freedatafunc );

	/*
	 * Gets the value associated with given key.
	 * Returns pointer to value if succeeded, NULL otherwise.
	 * */
	void* hashtable_get(const struct hashtable* htable, const void* key);

	/*
	 * Checks if the hashtable already contains a given key.
	 */
	int hashtable_contains(struct hashtable* htable, void* key);

	/*
	 * Adds the key/value to the hash table.
	 * Returns 1 if succeeded, 0 otherwise.
	 * */
	int hashtable_put( struct hashtable* htable, void* key, void* value );

	/*
	 * Deletes the key/value pair from the hash table for a given key.
	 * Returns removed key/value pair reference if succeeded, NULL otherwise.
	 * */
	struct hashtable_keyvalue_pair* hashtable_remove( struct hashtable* htable,
													const void* key );

	/*
	 * Shallow copies all keys from the hashtable to an array.
	 * You have to free result array from memory later in your code.
	 */
	void** hashtable_keys(struct hashtable* htable);

	/*
	 * Shallow copies all key/value pairs from the hashtable to an array.
	 * You have to free result array from memory later in your code.
	 */
	struct hashtable_keyvalue_pair** hashtable_toarray(struct hashtable* htable);

	/*
	 * Prints the hashtable items.
	 */
	void hashtable_print(struct hashtable* htable);

	/*
	 * Removes all elements from the hashtable.
	 * */
	void hashtable_clear(struct hashtable* htable);

	/*
	 * Releases the hash table from memory.
	 * */
	void hashtable_destroy(struct hashtable* htable);

#endif /* HASHTABLE_H_ */
