/*****************************************************************************
 * hashtable.h
 *
 *   Created on: 11/03/2023
 *       Author: Tiago C. Teixeira
 *  Description: Implements an hash table data structure in C.
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
 *******************************************************************************/

#ifndef HASHTABLE_H_
	#define HASHTABLE_H_

	#include <stdlib.h>

	#define HASHTABLE_DEFAULT_SIZE 25
	#define HASHTABLE_DEFAULT_LOAD_FACTOR 0.75
	#define HASHTABLE_MIN_SIZE 10
	#define HASHTABLE_RESIZE_FACTOR 2.0

	// key/value pair type
	struct hashtablekeyvaluepair {
		void* key;
		void* value;
	};


	// hash table type
	struct hashtable {
		struct hashtablekeyvaluepair* empty_kvp;		// fill empty data slots
		struct hashtablekeyvaluepair* deleted_kvp;		// fill deleted data slots
		int count;
		int capacity;									// size of hash array
		int (*hashfunc)(const void* key);					// hash function
		int (*isequal)(const void* key1, const void* key2);	// key compare for equality function
		int threshold;									// limit size to rise a reallocation (loadfactor * capacity)
		float loadfactor;								// fraction of hash array filled to generate a reallocation
		float resizefactor;								// to compute new hash array size for reallocation (new_size = resizefactor * capacity)
		struct hashtablekeyvaluepair* harray[];			// hash array
	};

	/*
	 * Creates a new hash table with default settings (size = 25, LF = 0.75).
	 * */
	struct hashtable* hashtable_createdefault( int (*hashfunc)(const void* key),
											   int (*isequalfunc)(const void* key1, const void* key2) );

	/*
	 * Creates a new hash table with given initial size and load factor.
	 * */
	struct hashtable* hashtable_create( int size, float loadfactor, float resizefactor,
										int (*hashfunc)(const void* key),
										int (*isequalfunc)(const void* key1, const void* key2) );

	/*
	 * Gets the value associated with given key.
	 * Returns pointer to value if succeeded, NULL otherwise.
	 * */
	void* hashtable_get(const struct hashtable* htable, const void* key);

	/*
	 * Adds the key/value to the hash table.
	 * Returns 1 if succeeded, 0 otherwise.
	 * */
	int hashtable_put(struct hashtable* htable, void* key, void* value);

	/*
	 * Deletes the key/value pair from the hash table for a given key.
	 * Returns removed key/value pair reference if succeeded, NULL otherwise.
	 * */
	struct hashtablekeyvaluepair* hashtable_delete(struct hashtable* htable, const void* key);

	/*
	 * Releases the hash table from memory.
	 * */
	void hashtable_destroy(struct hashtable* htable);

#endif /* HASHTABLE_H_ */

