/*
 * hashset.c
 *
 *  Created on: 04/09/2023
 *      Author: Tiago C. Teixeira
 * Description: Implements an unordered set in C using an hashtable.
 *
 * Definition
 *
 * 	In computer science, a set data structure is defined as a data structure that stores a
 * 	collection of distinct elements.
 * 	It is a fundamental Data Structure that is used to store and manipulate a group of
 * 	objects, where each object is unique. The Signature property of the set is that it
 * 	doesn’t allow duplicate elements.
 *
 * A set can be implemented in various ways but the most common ways are:
 *
 *    - Hash-Based Set: the set is represented as a hash table where each element in the
 *    	set is stored in a bucket based on its hash code.
 *
 *    - Tree-based set: In this implementation, the set is represented as a binary search
 *    	tree where each node in the tree represents an element in the set.
 *
 *
 * Need for Set Data Structure
 *
 * 	Set data structures are commonly used in a variety of computer science applications,
 * 	including algorithms, data analysis, and databases. The main advantage of using a set
 * 	data structure is that it allows you to perform operations on a collection of elements
 * 	in an efficient and organized way.
 *
 * Types of Set Data Structure:
 *
 * 	The set data structure can be classified into the following two categories:
 * 		1. Unordered Set
 *
 * 			An unordered set is an unordered associative container implemented using a
 * 			hash table where keys are hashed into indices of a hash table so that the
 * 			insertion is always randomized. All operations on the unordered set take
 * 			constant time O(1) on an average which can go up to linear time O(n) in the
 * 			worst case which depends on the internally used hash function, but practically
 * 			they perform very well and generally provide a constant time lookup operation.
 *
 * 		2. Ordered Set
 *
 * 			An Ordered set is the common set data structure we are familiar with. It is
 * 			generally implemented using balanced BSTs and it supports O(log n) lookups,
 * 			insertions and deletion operations.
 *
 *
 * A set is a data structure that stores a collection of unique elements, with no
 * duplicates allowed. Sets can be implemented using a variety of data structures,
 * including arrays, linked lists, binary search trees, and hash tables.
 *
 * Basically, a Set is language dependent Data Structure. Every language uses a different
 * data structure to implement a set data structure internally like C++ uses Self-Balancing
 * BST. Java, Python, C#, and JavaScript use Hash tables.
 *
 * Sets in C++ use Self-Balancing Binary Tree(BST). In this approach, the elements are
 * stored in nodes of a binary tree, with the property that the left subtree of any node
 * contains only elements smaller than the node’s value, and the right subtree contains
 * only elements larger than the node’s value. This property ensures that the elements
 * in the tree are always sorted in ascending order.
 *
 *
 * Text source: https://www.geeksforgeeks.org/introduction-to-set-data-structure-and-algorithm-tutorials/
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "hashset.h"
#include "hashtable.h"


int hashsetlist_isequal(const void* kvp1, const void* kvp2)
{
	int key1 = *((int*)(((struct hashtable_keyvalue_pair*)kvp1)->key));
	int key2 = *((int*)(((struct hashtable_keyvalue_pair*)kvp2)->key));
	return (key1 == key2);
}

/*
 * Creates a new hashset instance with a given size capacity.
 */
struct hashset* hashset_create_capacity( size_t capacity, hashset_hashfunc hashfunc,
										 hashset_isequal isequalfunc,
										 hashset_printelement printelementfunc,
										 hashset_freedata freedatafunc )
{
	struct hashset* result = (struct hashset*)malloc(sizeof(*result));
	if (result) {
		result->htable = hashtable_create( capacity,  HASHSET_DEFAULT_LOAD_FACTOR,
									       HASHSET_DEFAULT_RESIZE_FACTOR,
										   hashfunc, isequalfunc,
										   NULL, freedatafunc );
		result->printelement = printelementfunc;
	}
	else
	{
		printf("Error: Failed to allocate memory when creating hashset instance!");
		abort();
	}

	return result;
}

/*
 * Creates a new hashset instance with default size capacity.
 */
struct hashset* hashset_create( hashset_hashfunc hashfunc,
								hashset_isequal isequalfunc,
								hashset_printelement printelementfunc,
								hashset_freedata freedatafunc )
{
	struct hashset* result = hashset_create_capacity( HASHSET_DEFAULT_CAPACITY,
											 	 	  hashfunc, isequalfunc,
													  printelementfunc, freedatafunc );
	return result;
}

/*
 * Returns the number of elements in the set.
 */
size_t hashset_getsize(struct hashset* set)
{
	return set->htable->count;
}

/*
 * Checks if the hashset already contains a given key.
 */
int hashset_contains(struct hashset* set, void* value)
{
	void* el = hashtable_get(set->htable, value);
	return (el != NULL);
}

/*
 * Adds a new element in the set.
 * Note: Must be unique (its a property of sets).
 */
void hashset_add(struct hashset* set, void* value)
{
	// duplicated values are not allowed in sets
	if (!hashset_contains(set, value))
		hashtable_put(set->htable, value, HASHSET_ELEMENT_CONTENT);
}

/*
 * Removes a given element from the set.
 * Returns the removed element.
 */
void* hashset_remove(struct hashset* set, void* value)
{
	void* result = NULL;
	struct hashtable_keyvalue_pair* kvp = hashtable_remove(set->htable, value);
	if (kvp != NULL)
	{
		result = kvp->key;
		free(kvp);
	}

	return result;
}

/*
 * Shallow copies all elements from the hashtable to an array.
 * You have to free result array from memory later in your code.
 */
void** hashset_toarray(struct hashset* set)
{
	void** result = hashtable_keys(set->htable);
	return result;
}

/*
 * Prints all elements in set.
 */
void hashset_print(struct hashset* set)
{
	if (set->printelement == NULL) {
		printf("Error: 'printelement' function is undefined.");
		abort();
	}
	else {
		void** keys = hashset_toarray(set);
		size_t size = hashset_getsize(set);
		printf("{ ");

		if (size > 0) {
			set->printelement(keys[0]);

			for (int i = 1; i < size; ++i) {
				printf(", ");
				set->printelement(keys[i]);
			}
		}

		free(keys);
		printf(" }\n");
	}
}

/*
 * Removes all elements from the set.
 */
void hashset_clear(struct hashset* set)
{
	hashtable_clear(set->htable);
}

/*
 * Releases the hash set from memory.
 * */
void hashset_destroy(struct hashset* set)
{
	hashtable_destroy(set->htable);
	free(set);
}

