/*****************************************************************************
 * hashtable.h
 *
 *   Created on: 11/03/2023
 *       Author: Tiago C. Teixeira
 *  Description: Implements an hash table data structure in C using linear probing
 *  			 technique to avoid slot collisions.
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
 *******************************************************************************/

#ifndef HASHTABLE_LP_H_
	#define HASHTABLE_LP_H_

	#include <stdlib.h>

	#define HASHTABLE_LP_DEFAULT_SIZE 25
	#define HASHTABLE_LP_DEFAULT_LOAD_FACTOR 0.75
	#define HASHTABLE_LP_MIN_SIZE 10
	#define HASHTABLE_LP_RESIZE_FACTOR 2.0

	// key/value pair type
	struct hashtable_lp_keyvalue_pair {
		void* key;
		void* value;
	};

	typedef int (*hashtable_lp_hashfunc)(const void* key);
	typedef int (*hashtable_lp_isequal)(const void* key1, const void* key2);
	typedef void (*hashtable_lp_printitem)(const struct hashtable_lp_keyvalue_pair* kvp);
	typedef void (*hashtable_lp_freedata)(void* data);


	// hash table type
	struct hashtable_lp {
		struct hashtable_lp_keyvalue_pair* empty_kvp;		// fill empty data slots
		struct hashtable_lp_keyvalue_pair* deleted_kvp;	// fill deleted data slots
		size_t count;										// number of elements in the hashtable
		size_t capacity;									// size of hash array
		hashtable_lp_hashfunc hashfunc;					// hash function
		hashtable_lp_isequal isequal;					// key compare for equality function
		hashtable_lp_printitem printitem;				// function to print hastable item (key/value) pair
		hashtable_lp_freedata freedata;					// release key/value from memory function
		int threshold;									// limit size to rise a reallocation (loadfactor * capacity)
		float loadfactor;								// fraction of hash array filled to generate a reallocation
		float resizefactor;								// to compute new hash array size for reallocation (new_size = resizefactor * capacity)
		struct hashtable_lp_keyvalue_pair** harray;		// hash array
	};

	/*
	 * Creates a new hash table with default settings (size = 25, LF = 0.75).
	 * */
	struct hashtable_lp* hashtable_lp_create_default( hashtable_lp_hashfunc hashfunc,
													  hashtable_lp_isequal isequalfunc,
													  hashtable_lp_printitem printitemfunc,
													  hashtable_lp_freedata freedatafunc );

	/*
	 * Creates a new hash table with given initial size and load factor.
	 * */
	struct hashtable_lp* hashtable_lp_create( size_t size, float loadfactor, float resizefactor,
											  hashtable_lp_hashfunc hashfunc,
											  hashtable_lp_isequal isequalfunc,
											  hashtable_lp_printitem printitemfunc,
											  hashtable_lp_freedata freedatafunc );

	/*
	 * Checks if hastable contains element with the given key.
	 * Returns '1' (true) if succeeded, '0' (false) otherwise.
	 * */
	int hashtable_lp_contains(const struct hashtable_lp* htable, const void* key);

	/*
	 * Gets the value associated with given key.
	 * Returns pointer to value if succeeded, NULL otherwise.
	 * */
	void* hashtable_lp_get(const struct hashtable_lp* htable, const void* key);

	/*
	 * Adds the key/value to the hash table.
	 * Returns 1 if succeeded, 0 otherwise.
	 * */
	int hashtable_lp_put(struct hashtable_lp* htable, void* key, void* value);

	/*
	 * Deletes the key/value pair from the hash table for a given key.
	 * Returns removed key/value pair reference if succeeded, NULL otherwise.
	 * */
	struct hashtable_lp_keyvalue_pair* hashtable_lp_remove(struct hashtable_lp* htable, const void* key);

	/*
	 * Prints the hashtable items.
	 */
	void hashtable_lp_print(struct hashtable_lp* htable);

	/*
	 * Releases the hash table from memory.
	 * */
	void hashtable_lp_destroy(struct hashtable_lp* htable);

#endif /* HASHTABLE_LP_H_ */

