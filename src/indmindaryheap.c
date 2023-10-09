/*
 * indexedmindaryheap.c
 *
 *  Created on: 22/09/2023
 *      Author: Tiago C. Teixeira
 * Description: An implementation in C of an indexed min D-ary heap priority queue.
 *
 * Definition
 *
 * 		An Indexed Priority Queue is a data structure that combines the properties of
 * 		both an indexable data structure (like an array or a list) and a priority queue.
 * 		It is used in computer science and algorithms to efficiently manage a collection
 * 		of elements with associated priorities, allowing for quick updates to both
 * 		priorities and values. Indexed Priority Queues are particularly useful in graph
 * 		algorithms, shortest path algorithms (e.g., Dijkstra's algorithm), and other
 * 		scenarios where efficient priority-based operations are required.
 *
 *
 * This implementation supports arbitrary keys with comparable values. To use arbitrary keys
 * (such as strings or objects) first map all your keys to the integer domain [0, N) where N is the
 * number of keys you have and then use the mapping with this indexed priority queue.
 *
 * As convention, I denote 'ki' as the index value in the domain [0, N) associated with a key k,
 * therefore: ki = map[k]
 *
 * Often the keys themselves are integers in rhe range [0..N) so there's no need for
 * mapping. but it's handy to be able to support any type of key (like names).
 *
 * In a normal priority queue search, delete and update operations can take O(n) time
 * where in a indexed priority queue (indexed binary PQ) this operations are done in
 * O(logn).
 *
 * 		  Time complexity by operation
 *	-----------------------------------------
 * 	|	valueof(ki)   			| O(1)		|
 * 	|	contains(ki) 			| O(1)		|
 * 	|	peekminkeyindex 		| O(1)		|
 * 	|	poolminkeyindex 		| O(logn)	|
 * 	|	peekminvalue 			| O(1)		|
 * 	|	poolminvalue 			| O(logn)	|
 * 	|	insert(ki, value) 		| O(logn)	|
 *	|	update(ki, value) 		| O(logn)	|
 * 	|	decreasekey(ki, value) 	| O(logn)	|
 * 	|	increasekey(ki, value) 	| O(logn)	|
 *	-----------------------------------------
 * 	where ki = key index
 *
 * Structure:
 *
 * 		An Indexed Priority Queue is typically implemented using a binary heap or a
 *    	Fibonacci heap as the underlying data structure.
 *    	It consists of a collection of elements, each associated with a unique index and
 *    	a priority value.
 *    	Elements are organized in a way that allows for efficient extraction of the
 *    	element with the highest (or lowest, depending on the implementation) priority.
 *
 * Pros:
 *
 *    	Efficient Priority-Based Operations:
 *    		Indexed Priority Queues allow for efficient insertion, deletion, and
 *    		priority change operations, typically with logarithmic time complexity.
 *
 *    	Indexed Access:
 *    		You can quickly access elements by their unique index, making it suitable
 *    		for graph algorithms and other scenarios where you need to associate data
 *    		with specific vertices or nodes.
 *
 *   	Used in Various Algorithms:
 *   		It is a fundamental data structure in algorithms like Dijkstra's algorithm,
 *   		Prim's algorithm, and A* search, which are used in graph traversal and
 *   		shortest path problems.
 *
 * Cons:
 *
 *    	Complexity:
*    		Implementing an efficient indexed priority queue can be complex,
*    		especially when using data structures like Fibonacci heaps. Simpler
*    		implementations using binary heaps may have slightly worse time complexity
*    		for some operations.
*
 *    	Space Overhead:
 *    		Indexed Priority Queues may have a higher space overhead compared to
 *    		simpler data structures like arrays or lists, especially if additional
 *    		data (e.g., values) is associated with each element.
 *
 *
 * Sources: This source code is ported and adapted from William Fiset Java implementation.
 * 		    https://github.com/williamfiset/Algorithms/blob/master/src/main/java/com/williamfiset/algorithms/datastructures/priorityqueue/MinIndexedDHeap.java
 *
 * 			Texts and a more simpler c++ implementation can be found at:
 * 			https://www.geeksforgeeks.org/indexed-priority-queue-with-implementation/
 *
 */

#include "indmindaryheap.h"

#include <stdio.h>
#include <stdlib.h>

/*
 * Return max of two non-negative values.
 */
size_t imindarypq_max(size_t a, size_t b) {
	return (a > b) ? a : b;
}

/*
 * Return min of two non-negative values.
 */
 size_t imindarypq_min(size_t a, size_t b) {
 	return (a < b) ? a : b;
 }

/*
 * Error handler function.
 */
void imindarypq_error(char msg[]) {
	printf("%s\n", msg);
	abort();
}

/*
 * Initializes a D-ary heap with a maximum capacity of maxSize.
 */
struct idarypq* imindarypq_create( size_t degree, size_t maxSize,
								   idarypq_comparefunc comparefunc,
								   idarypq_printdata printdatafunc,
								   idarypq_freedata freedatafunc )
{
	if (maxSize <= 0) {
		imindarypq_error("Illegal argument: max priority queue size must be greater than zero!");
	}

	struct idarypq* result = (struct idarypq*)malloc(sizeof(*result));
	if (result == NULL) {
		printf("Error: failed to allocate memory for indexed d-ary priority queue!");
		abort();
	}

	result->D = imindarypq_max(2, degree);
	result->N = imindarypq_max(result->D + 1, maxSize);
	result->sz = 0;	// empty at start
	result->compare = comparefunc;
	result->printdata = printdatafunc;
	result->freedata = freedatafunc;

	result->im = (int*)malloc(result->N * sizeof(int));
	if (result->im == NULL) imindarypq_error("Error: failed to allocate memory for inverse map in priority queue!");

	result->pm = (int*)malloc(result->N * sizeof(int));
	if (result->pm == NULL) imindarypq_error("Error: failed to allocate memory for positional map in priority queue!");

	result->child = (int*)malloc(result->N * sizeof(int));
	if (result->child == NULL) imindarypq_error("Error: failed to allocate memory for child index array in priority queue!");

	result->parent = (int*)malloc(result->N * sizeof(int));
	if (result->parent == NULL) imindarypq_error("Error: failed to allocate memory for parent index array in priority queue!");

	result->values = (void**)malloc(result->N * sizeof(void*));
	if (result->values == NULL) imindarypq_error("Error: failed to allocate memory for values array in priority queue!");

	// initialize arrays
	for (int i = 0; i < result->N; i++) {
		result->parent[i] = (i - 1) / result->D;
		result->child[i] = i * result->D + 1;
		result->pm[i] = result->im[i] = -1;
	}

	return result;
}

/*
 * Checks if the priority heap is empty.
 */
int imindarypq_isempty(struct idarypq* ipq) {
    return (ipq->sz == 0);
}

/* Helper functions to make the code more readable. */

void imindarypq_key_in_bounds_or_throw(struct idarypq* ipq, int ki) {
    if (ki < 0 || ki >= ipq->N)
    	imindarypq_error("Key index out of bounds");
}

/*
 * Checks if an element with a given key index exists in the heap or not.
 */
int imindarypq_contains( struct idarypq* ipq , int ki ) {
	imindarypq_key_in_bounds_or_throw(ipq, ki);
    return ipq->pm[ki] != -1;
}

void imindarypq_key_exists_or_throw(struct idarypq* ipq, int ki) {
	if (!imindarypq_contains( ipq, ki ) )
		imindarypq_error("Index does not exist");
}

void imindarypq_value_not_null_or_throw(struct idarypq* ipq, void* value) {
    if (value == NULL)
    	imindarypq_error("value cannot be null");
}

void imindarypq_is_not_empty_or_throw(struct idarypq* ipq) {
    if (imindarypq_isempty(ipq))
    	imindarypq_error("Priority queue underflow");
}

void imindarypq_key_exists_and_value_not_null_or_throw(struct idarypq* ipq, int ki, void* value) {
	imindarypq_key_exists_or_throw(ipq, ki);
	imindarypq_value_not_null_or_throw(ipq, value);
}

/*
 * Returns the next key index to be pooled from the heap.
 */
int imindarypq_peekminkeyindex( struct idarypq* ipq ) {
	imindarypq_is_not_empty_or_throw(ipq);
    return ipq->im[0];
}

/*
 * Returns the next key index to be pooled from the heap.
 */
int imindarypq_peekkeyindex( struct idarypq* ipq ) {
	return imindarypq_peekminkeyindex(ipq);
}

//// delete function prototype
//void* imindarypq_delete(struct idarypq* ipq, int ki);

/*
 * Removes the minimum element from the heap at a given key index (ki).
 * Returns the key index of the removed element.
 */
 int imindarypq_pollminkeyindex( struct idarypq* ipq ) {
	 int minki = imindarypq_peekminkeyindex(ipq);
	 void* value = imindarypq_delete( ipq, minki);
	 if ((ipq->freedata) && (value))
		 ipq->freedata(value);
	 return minki;
}

/*
 * Removes the minimum element from the heap at a given key index (ki).
 * Returns the key index of the removed element.
 */
int imindarypq_extractkeyindex( struct idarypq* ipq ) {
	return imindarypq_pollminkeyindex( ipq );
}

/*
 *	Retrieves to minimum value (element at top of the heap).
 *	Note: doesn't remove the element.
 */
void* imindarypq_peekminvalue( struct idarypq* ipq )
{
	imindarypq_is_not_empty_or_throw(ipq);
    return ipq->values[ipq->im[0]];
}

void* imindarypq_peek( struct idarypq* ipq ) {
	return imindarypq_peekminvalue( ipq );
}

/*
 * Extracts element (with high priority) at top of the heap.
 */
void* imindarypq_extractkey( struct idarypq* ipq ) {
    void* minValue = imindarypq_peekminvalue( ipq );
    imindarypq_delete( ipq, imindarypq_peekkeyindex( ipq ) );
    return minValue;
}

/*
 * Gets the number of elements on the indexed priority queue.
 */
size_t imindarypq_getsize(struct idarypq* ipq) {
    return ipq->sz;
}

/*
 * Swap position map indexes and inverse map indexes.
 * Note: No need two touch priority values array.
 */
void imindarypq_swap( struct idarypq* ipq, int i, int j ) {
    ipq->pm[ipq->im[j]] = i;
    ipq->pm[ipq->im[i]] = j;
    int tmp = ipq->im[i];
    ipq->im[i] = ipq->im[j];
    ipq->im[j] = tmp;
}

/*
 * Checks if data1 < data2.
 */
int imindarypq_less(struct idarypq* ipq, void* data1, void* data2) {
	return (ipq->compare(data1, data2) < 0);
}

/*
 * Checks if the value of node i < node j (by index)
 */
int imindarypq_less_by_inv_index(struct idarypq* ipq, int i, int j) {
	return imindarypq_less(ipq, ipq->values[ipq->im[i]], ipq->values[ipq->im[j]]);
}

/*
 * From the parent node at index i find the minimum child below it.
 * Note: Nodes have D-ary childs.
 */
int imindarypq_minchild(struct idarypq* ipq, int i) {
    int index = -1;
    int from = ipq->child[i];
    int to = imindarypq_min(ipq->sz, from + ipq->D);
    for (int j = from; j < to; j++)
    	if (imindarypq_less_by_inv_index(ipq, j, i)) index = i = j;
    return index;
}

/*
 * Moves node at index i down the heap.
 */
void imindarypq_sink(struct idarypq* ipq, int i) {
    for (int j = imindarypq_minchild(ipq, i); j != -1; ) {
    	imindarypq_swap(ipq, i, j);
    	i = j;
    	j = imindarypq_minchild(ipq, i);
    }
}

/*
 * Moves node at index i up the heap.
 */
void imindarypq_swim(struct idarypq* ipq, int i) {
	int parent = ipq->parent[i];
	if (parent > -1)
		while (imindarypq_less_by_inv_index(ipq, i, parent)) {
			imindarypq_swap(ipq, i, parent);
			i = parent;
			parent = ipq->parent[i];
			if (parent < 0) break;
		}
}

/*
 * Inserts a new element in the heap at a given key index.
 * Note: If key index already contains an element in the heap, an error will be throw.
 */
void imindarypq_insert(struct idarypq* ipq, int ki, void* value)
{
    if (imindarypq_contains(ipq, ki))
    	imindarypq_error("Heap insertion error: index 'ki' already exists.");

    imindarypq_value_not_null_or_throw(ipq, value);
    ipq->pm[ki] = ipq->sz;
    ipq->im[ipq->sz] = ki;
    ipq->values[ki] = value;
    imindarypq_swim(ipq, ipq->sz++);
}

/*
 * Returns the heap element value stored at a given key index.
 */
void* imindarypq_valueof(struct idarypq* ipq, int ki) {
	imindarypq_key_exists_or_throw(ipq, ki);
    return ipq->values[ki];
}

/*
 * Deletes an element (value) in the heap for a given key index.
 * Returns the deleted element if succeeded, NULL otherwise.
 */
void* imindarypq_delete(struct idarypq* ipq, int ki)
{
	imindarypq_key_exists_or_throw(ipq, ki);
    int i = ipq->pm[ki];
    imindarypq_swap(ipq, i, --(ipq->sz));	// swap with last element
    imindarypq_sink(ipq, i);	// can go down or up in the tree
    imindarypq_swim(ipq, i);
    void* value = ipq->values[ki];
    ipq->values[ki] = NULL;		// key index position has to be marked as free
    ipq->pm[ki] = -1;			// and relation position maps
    ipq->im[ipq->sz] = -1;
    return value;
}

/*
 * Updates a given value and returns old value.
 */
void* imindarypq_update(struct idarypq* ipq, int ki, void* value)
{
	imindarypq_key_exists_and_value_not_null_or_throw(ipq, ki, value);
    int i = ipq->pm[ki];
    void* oldValue = ipq->values[ki];
    ipq->values[ki] = value;
    imindarypq_sink(ipq, i);
    imindarypq_swim(ipq, i);
    return oldValue;
}

/*
 * Strictly decreases the value associated with 'ki' to 'value'
 * Note: If freedata() is defined it will be executed to release old value resources!
 */
void imindarypq_decrease(struct idarypq* ipq, int ki, void* value)
{
	imindarypq_key_exists_and_value_not_null_or_throw(ipq, ki, value);
    if (imindarypq_less(ipq, value, ipq->values[ki])) {
    	if (ipq->freedata)
    		ipq->freedata(ipq->values[ki]);		// release old value if needed
    	ipq->values[ki] = value;
    	imindarypq_swim(ipq, ipq->pm[ki]);
    }
}

/*
 * Strictly increases the value associated with 'ki' to 'value'
 * Note: If freedata() is defined it will be executed to release old value resources!
 */
void imindarypq_increase(struct idarypq* ipq, int ki, void* value)
{
	imindarypq_key_exists_and_value_not_null_or_throw(ipq, ki, value);
    if (imindarypq_less(ipq, ipq->values[ki], value)) {
    	if (ipq->freedata)
    	    ipq->freedata(ipq->values[ki]);		// release old value if needed
    	ipq->values[ki] = value;
    	imindarypq_sink(ipq, ipq->pm[ki]);
    }
}

/*
 * Prints the heap indexed priority queue elements.
 */
void imindarypq_print( struct idarypq* ipq )
{
	if (!(ipq->printdata))
		imindarypq_error("Error printing priority queue: 'printdata()' function is undefined!");
	else {
		for (int i = 0; i < ipq->sz; ++i) {
			printf("Print ki/value pairs by priority order:\n");
			printf("(%d : ", ipq->im[i]); ipq->printdata(ipq->values[ipq->im[i]]); printf(") ");
		}

		printf("\n");
	}
}

/*
 * Releases priority queue instance from memory.
 */
void imindarypq_destroy(struct idarypq* ipq)
{
	free(ipq->parent);
	free(ipq->child);
	free(ipq->pm);
	free(ipq->im);

	if (ipq->freedata)
		for (int i = 0; i < ipq->sz; ++i) {
			if (ipq->values[i] != NULL)
				ipq->freedata( ipq->values[i] );
		}

	free(ipq->values);
	free(ipq);
}
