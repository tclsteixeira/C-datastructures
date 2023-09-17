/*
 * treeset.h
 *
 *  Created on: 10/09/2023
 *      Author: Tiago C. Teixeira
 * Description: Headers for an ordered set implemented with a self-balancing binary
 * 				search tree (red-black tree).
 *
 * Definition
 *
 * 	In computer science, a set data structure is defined as a data structure that stores a
 * 	collection of distinct elements.
 * 	It is a fundamental Data Structure that is used to store and manipulate a group of
 * 	objects, where each object is unique. The Signature property of the set is that it
 * 	doesn’t allow duplicate elements.
 *
 * 	Properties of sets:
 * 		- each element is unique;
 * 		- each element is immutable.
 *
 * 1. Speed and internal implementation
 *
 * For operations like search, insert, and delete HashSet takes constant time for these
 * operations on average. HashSet is faster than TreeSet. HashSet is Implemented using a
 * hash table. TreeSet takes O(Log n) for search, insert and delete which is higher than
 * HashSet. But TreeSet keeps sorted data. Also, it supports operations like higher()
 * (Returns least higher element), floor(), ceiling(), etc. These operations are also
 * O(Log n) in TreeSet and not supported in HashSet. TreeSet is implemented using a
 * self-balancing binary search tree (Red-Black Tree). TreeSet is backed by TreeMap in
 * Java.
 *
 */

#ifndef TREESET_H_
	#define TREESET_H_

	#include "redblacktree.h"

	// the two next functions are used internally by the red-black tree
	typedef rbtree_calcdatasize treeset_calcelementsize; // function to calc size in bytes of an element
	typedef rbtree_copydata treeset_copyelement; 		 // function to copy element instance to other instance of same type

	typedef rbtree_cmp treeset_compare;					 // function to compare two elements in the set.
	typedef rbtree_printdata treeset_printelement;		 // function to print an element
//	typedef void (*treeset_printelement)(const void* element); // function to print an element.
	typedef rbtree_freedata treeset_freedata;			 // function to release an element from memory

	// visit function for treeset traversal functions
	typedef void (*treeset_visit)(void* element, void** result, int index);

	struct treeset {
		struct rbtree* tree;
		size_t size;
	};

	/*
	 * Function to create a new treeset.
	 * Returns pointer to created treeset instance is succeeded, NULL otherwise.
	 */
	struct treeset* treeset_create( treeset_calcelementsize calcelementsizefunc,
									treeset_copyelement copyelementfunc,
									treeset_compare comparefunc,
									treeset_printelement printelementfunc,
									treeset_freedata freedatafunc );

	/*
	 * Returns the number of elements in the treeset.
	 */
	size_t treeset_getsize( struct treeset* set );

	/*
	 * Checks if the treeset already contains a given element.
	 */
	int treeset_contains( struct treeset* set, void* value );

	/*
	 * Adds a new element in the set.
	 * Note: Must be unique (its a property of sets).
	 */
	void treeset_add(struct treeset* set, void* value);

	/*
	 * Removes a given element from the set.
	 * Returns the removed element.
	 */
	void* treeset_remove(struct treeset* set, void* value);

	/*
	 * Gets minimum element in the set.
	 * Returns NULL if set is empty.
	 */
	void* treeset_min(struct treeset* set);

	/*
	 * Gets maximum element in the set.
	 * Returns NULL if set is empty.
	 */
	void* treeset_max(struct treeset* set);

	/*
	 * This function is used to find floor element of a key in O(H) time.
	 * Floor Value: greatest data lesser than or equal to the key value.
	 *
	 * Time Complexity: O(H), where H is the height of the tree
	 * Auxiliary Space: O(1)
	 *
	 * Returns NULL if set is empty.
	 * */
	void* treeset_floor(struct treeset* set, struct rbtreenode* root, void* key);

	/*
	 * This function is used to find ceiling element of a key in O(H) time.
	 * Ceil Value: Smallest data larger than or equal to the key value.
	 *
	 * Time Complexity: O(H), where H is the height of the tree
	 * Auxiliary Space: O(1)
	 *
	 * Returns NULL if set is empty.
	 * */
	void* treeset_ceiling(struct treeset* set, struct rbtreenode* root, void* key);

	/*
	 * Returns set elements in ascendind order.
	 * Note: Returned array must be released later.
	 * */
	void** treeset_toarray(struct treeset* set);

	/*
	 * Returns set elements in descendind order.
	 * Note: Returned array must be released later.
	 * */
	void** treeset_toarray_desc(struct treeset* set);

	/*
	 * Returns elements between a given range in ascendind order.
	 * Note: Returning list must be released later from memory.
	 * */
	struct arraylist* treeset_toarraylist_range(struct treeset* set, void* from, void* to,
			int hardcopy );

	/*
	 * Removes elements between a given range.
	 * Returns number of removed elements.
	 * */
	int treeset_remove_range(struct treeset* set, void* from, void* to);

	/*
	 * Prints treeset elements.
	 */
	void treeset_print(struct treeset* set, int reverse);

	/*
	 * Releases all nodes and data instance from treeset.
	 * */
	void treeset_clear(struct treeset* set);

	/*
	 * Releases all nodes, his data, and the treeset structure instance from memory.
	 * */
	void treeset_destroy(struct treeset* set);

// other operation like first(), last(), floor(), ceiling(), higher(), etc

#endif /* TREESET_H_ */
