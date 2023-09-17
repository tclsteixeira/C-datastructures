/*
 * treeset.c
 *
 *  Created on: 10/09/2023
 *      Author: Tiago C. Teixeira
 * Description: Implements an ordered set using a self-balancing binary
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

#include <stdlib.h>
#include <stdio.h>
#include "treeset.h"
#include "redblacktree.h"
#include "arraylist.h"

/*
 * Function to create a new treeset.
 * Returns pointer to created treeset instance is succeeded, NULL otherwise.
 */
struct treeset* treeset_create( treeset_calcelementsize calcelementsizefunc,
								treeset_copyelement copyelementfunc,
								treeset_compare comparefunc,
								treeset_printelement printelementfunc,
								treeset_freedata freedatafunc )
{

	struct treeset* result = (struct treeset*)malloc(sizeof(struct treeset));

	if (!result) {
		printf("Memory error: failed to allocate memory for treeset!");
		abort();
	}
	else {
		result->tree = rbtree_create( NULL, calcelementsizefunc, comparefunc,
									  freedatafunc, printelementfunc, copyelementfunc);
		if (!(result->tree)) {
			printf("Memory error: faile to allocate memory for treeset tree!");
			abort();
		}

		result->size = 0;
	}

	return result;
}

/*
 * Checks if the treeset already contains a given element.
 */
int treeset_contains( struct treeset* set, void* value )
{
	if (rbtree_search(set->tree, set->tree->root, value))
		return 1;
	else
		return 0;
}

/*
 * Adds a new element in the set.
 * Note: Must be unique (its a property of sets).
 */
void treeset_add(struct treeset* set, void* value)
{
	// duplicated values will not be inserted by default in the red-black tree.
	if (rbtree_insert(set->tree, value))
		set->size++;
}

/*
 * Removes a given element from the set.
 * Returns the removed element.
 */
void* treeset_remove(struct treeset* set, void* value)
{
	void* result = rbtree_delete(set->tree, value);
	if (result)
		set->size--;

	return result;
}

/*
 * Gets maximum element in the set.
 * Returns NULL if set is empty.
 */
void* treeset_max(struct treeset* set)
{
	struct rbtreenode* node = set->tree->root;
	if (node) {
		while (node->right) {
			node = node->right;
		}

		return node->data;
	} else {
		return NULL;
	}
}

/*
 * Gets minimum element in the set.
 * Returns NULL if set is empty.
 */
void* treeset_min(struct treeset* set)
{
	struct rbtreenode* node = set->tree->root;
	if (node) {
		while (node->left) {
			node = node->left;
		}

		return node->data;
	}
	else
		return NULL;
}

/*
 * This function is used to find floor element of a key in O(H) time.
 * Floor Value: greatest data lesser than or equal to the key value.
 *
 * Time Complexity: O(H), where H is the height of the tree
 * Auxiliary Space: O(1)
 *
 * Returns NULL if set is empty.
 * */
void* treeset_floor(struct treeset* set, struct rbtreenode* root, void* key)
{
    if (!root)
        return NULL;

    /* If root->data is equal to key */
    if (set->tree->compare(root->data, key) == 0) // (root->data == key)
        return root->data;

    /* If root->data is greater than the key - go left*/
    if (set->tree->compare(root->data, key) > 0)	//(root->data > key)
        return treeset_floor(set, root->left, key);

    /* Else, the floor may lie in right subtree
      or may be equal to the root - go right*/
    void* floorValue = treeset_floor(set, root->right, key);
    return ((!(set->tree->compare(floorValue, key) > 0)) && (floorValue != NULL)) ? floorValue : root->data;
}

/*
 * This function is used to find ceiling element of a key in O(H) time.
 * Ceil Value: Smallest data larger than or equal to the key value.
 *
 * Time Complexity: O(H), where H is the height of the tree
 * Auxiliary Space: O(1)
 *
 * Returns NULL if set is empty.
 * */
void* treeset_ceiling(struct treeset* set, struct rbtreenode* root, void* key)
{
    if (!root)
        return NULL;

    /* If root->data is equal to key */
    if (set->tree->compare(root->data, key) == 0) // (root->data == key)
        return root->data;

    /* If root->data is lesser than the key - go right*/
    if (set->tree->compare(root->data, key) < 0)	//(root->data < key)
        return treeset_ceiling( set, root->right, key );

    /* Else, the celing may lie in left subtree
      or may be equal to the root - go left*/
    void* ceilingValue = treeset_ceiling( set, root->left, key );
    return (!(set->tree->compare(ceilingValue, key) < 0)) ? ceilingValue : root->data;
}

/*
 * Inorder traversal to visit nodes element in ascending order.
 */
void treeset_inorder_traversal( struct rbtreenode* node,
								void* result, int* indexp,
								treeset_visit visit)
{
	if (node) {
		treeset_inorder_traversal(node->left, result, indexp, visit);
		visit( node->data, result, (*indexp)++ );
		treeset_inorder_traversal(node->right, result, indexp, visit);
	}
}

/*
 * Inorder traversal to visit nodes element between given range in ascending order.
 */
void treeset_inorder_traversal_between( struct treeset* set, struct rbtreenode* node,
										void* result, int* indexp,
										void (*visit_range)(struct treeset* set, void* element, void** result, int hardcopy),
										const void* from, const void* to )
{
	if (node) {
		if ( (!(set->tree->compare(node->data, from) < 0))) {
			treeset_inorder_traversal_between( set, node->left, result, indexp,
											   visit_range, from, to );
		}

		// (data >= from) and (data <= to) ?
		if ( (!(set->tree->compare(node->data, from) < 0))
			&& (!(set->tree->compare(node->data, to) > 0)) )
				visit_range(set, node->data, result, *indexp);

		if ((!(set->tree->compare(node->data, to) > 0))) {
			treeset_inorder_traversal_between( set, node->right, result, indexp,
											   visit_range, from, to );
		}
	}
}

/*
 * Inorder traversal to visit nodes element in descending order.
 */
void treeset_reverseorder_traversal( struct rbtreenode* node, void* result,
									 int* indexp,
									 treeset_visit visit )
{
	if (node) {
		treeset_reverseorder_traversal(node->right, result, indexp, visit);
		visit(node->data, result, (*indexp)++);
		treeset_reverseorder_traversal(node->left, result, indexp, visit);
	}
}

// declare callbacks for tree traversal visitor function
// visit function
void __tree_set_visitor_default( void* element, void** result, int i ) {
	result[i] = element;
}

// visit function for range traversals
void __treeset_range_visitor_default( struct treeset* set, void* element,
									  void** result, int hardcopy ) {
	if (hardcopy) {
		void* copy_el = (void*)malloc(set->tree->calcdatasize(element));
		set->tree->copydata(copy_el, element);
		arraylist_add( (struct arraylist*)result, copy_el );
	}
	else
		arraylist_add( (struct arraylist*)result, element );
}

/*
 * Returns set elements in ascendind order.
 * Note: Returned array must be released later.
 * */
void** treeset_toarray(struct treeset* set)
{
	void** arr = (void**)malloc(sizeof(void*) * set->size);
	int idx = 0;

//	// visit function
//	void visit( void* element, void** result, int i ) {
//		result[i] = element;
//	}

	treeset_inorder_traversal( set->tree->root, arr, &idx, __tree_set_visitor_default );
	return arr;
}

/*
 * Returns set elements in descendind order.
 * Note: Returned array must be released later.
 * */
void** treeset_toarray_desc(struct treeset* set)
{
	void** result = (void**)malloc(sizeof(void*) * set->size);
	int idx = 0;

//	// visit function
//	void visit(void* element, void** result, int i) {
//		result[i] = element;
//	}

	treeset_reverseorder_traversal( set->tree->root, (void*)result, &idx, __tree_set_visitor_default );
	return result;
}



/*
 * Returns elements between a given range in ascendind order.
 * Note: Returning list must be released later from memory.
 * */
struct arraylist* treeset_toarraylist_range( struct treeset* set, void* from, void* to,
											 int hardcopy )
{
	struct arraylist* result = arraylist_create();
    int idx = hardcopy;

	treeset_inorder_traversal_between( set, set->tree->root, (void*)result,
									   &idx,
								       __treeset_range_visitor_default, from, to);

	return result;
}

/*
 * Removes elements between a given range.
 * Returns number of removed elements.
 * */
int treeset_remove_range(struct treeset* set, void* from, void* to)
{
	int count = 0;	// number of deleted node from tree.
	// get hard copy because when deleting tree element, address of data can change
	// and change also arraylist data references that points to same tree node data.
	struct arraylist* result = treeset_toarraylist_range(set, from, to, 1);

	if (result) {
		void* deleted_value = NULL;
		void* cur_element = NULL;

		for (int i = 0; i < result->length; ++i) {
			cur_element = arraylist_get_item_at(result, i);

			// remove current element
			deleted_value = treeset_remove( set, cur_element );

			if (deleted_value) {
				count++;
				if (set->tree->freedata)
					set->tree->freedata(deleted_value);
			}
			else {
				printf("Error: failed to remove element width address '%p' from red-black tree!", cur_element);
				abort();
			}
		}
	}

	// release array list (remember its a hardcopy)
	for (int i = 0; i < result->length; ++i) {
		free(result->buffer[i]);
	}

	arraylist_destroy(result);
	return count;
}

/*
 * Prints treeset elements.
 */
void treeset_print(struct treeset* set, int reverse)
{
	if (!set->tree->printdata) {
		printf("Error: 'printdata' function is undefined. Can't print set.");
		abort();
	}

	void** asc = (reverse) ? treeset_toarray_desc(set) : treeset_toarray(set);
	printf("{ ");
	for (int i = 0; i < set->size; ++i) {
		set->tree->printdata(asc[i]);

		if (i < (set->size-1))
			printf("; ");
	}

	printf(" }\n");
	free(asc);
}

/*
 * Releases all elements from treeset.
 * */
void treeset_clear(struct treeset* set)
{
	rbtree_clear( set->tree );
	set->size = 0;
}

/*
 * Releases all resources from memory.
 * */
void treeset_destroy(struct treeset* set)
{
	rbtree_destroy( set->tree );
	free(set);
}

