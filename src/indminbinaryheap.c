/*
 * indexedminbinaryheap.c
 *
 *  Created on: 26/09/2023
 *      Author: Tiago C. Teixeira
 * Description: C implementation of an indexed min binary heap (indexed priority queue).
 */

#include <stdio.h>
#include "indminbinaryheap.h"
#include "indmindaryheap.h"

/*
 * Initializes an indexed min binary heap with a maximum capacity of maxSize.
 */
struct iminbinarypq* iminbinpq_create( size_t maxSize,
									   iminbinpq_comparefunc comparefunc,
									   iminbinpq_printdata printdatafunc,
									   iminbinpq_freedata freedatafunc )
{
	struct iminbinarypq* result = (struct iminbinarypq*)malloc(sizeof(*result));
	if (!result) {
		printf("Memory error: Unable to allocate memory for indexed min priority queue struct!");
		abort();
	}

	// degree = 2 (binary heap has 2 childs per node)
	struct idarypq* ipq = imindarypq_create( 2, maxSize,
										     comparefunc, printdatafunc,
										     freedatafunc );
	if (!ipq) {
		printf("Memory error: Unable to allocate memory for indexed min priority queue struct!");
		abort();
	}
	else {
		result->ipq = ipq;
	}

	return result;
}

/*
 * Returns the heap element value stored at a given key index.
 */
void* iminbinpq_valueof(struct iminbinarypq* ipq, int ki)
{
	return imindarypq_valueof( ipq->ipq, ki );
}

/*
 * Checks if the priority heap is empty.
 */
int iminbinpq_isempty(struct iminbinarypq* ipq) {
	return imindarypq_isempty( ipq->ipq );
}

/*
 * Gets the number of elements on the indexed priority queue.
 */
size_t iminbinpq_getsize(struct iminbinarypq* ipq) {
	return imindarypq_getsize( ipq->ipq );
}

/*
 * Checks if an element with a given key index exists in the heap or not.
 */
int iminbinpq_contains( struct iminbinarypq* ipq , int ki ) {
	return imindarypq_contains( ipq->ipq, ki );
}

/*
 * Inserts a new element in the heap at a given key index.
 * Note: If key index already contains an element in the heap, an error will be throw.
 */
void iminbinpq_insert( struct iminbinarypq* ipq, int ki, void* value ) {
	imindarypq_insert( ipq->ipq, ki, value );
}

/*
 * Deletes an element (value) in the heap for a given key index.
 * Returns the deleted element if succeeded, NULL otherwise.
 */
void* iminbinpq_delete(struct iminbinarypq* ipq, int ki) {
	return imindarypq_delete( ipq->ipq, ki );
}

/*
 * Returns the priority value (at root) from heap but does not remove it.
 * The time Complexity of this operation is O(1).
 */
void* iminbinpq_peek( struct iminbinarypq* ipq ) {
	return imindarypq_peek( ipq->ipq );
}

/*
 * Extracts element (with high priority) at top of the heap.
 */
void* iminbinpq_extractkey( struct iminbinarypq* ipq ) {
	return imindarypq_extractkey( ipq->ipq );
}

/*
 * Returns the next key index to be pooled from the heap.
 */
int iminbinpq_peekkeyindex( struct iminbinarypq* ipq ) {
	return imindarypq_peekkeyindex( ipq->ipq );
}

/*
 * Removes the high priority element from the heap at a given key index (ki).
 * Returns the key index of the removed element.
 */
int iminbinpq_extractkeyindex( struct iminbinarypq* ipq ) {
	return imindarypq_extractkeyindex( ipq->ipq );
}

/*
 * Updates a given value and returns old value.
 */
void* iminbinpq_update(struct iminbinarypq* ipq, int ki, void* value) {
	return imindarypq_update( ipq->ipq, ki, value );
}

/*
 * Strictly decreases the value associated with 'ki' to 'value'
 * Note: If freedata() is defined it will be executed to release old value resources!
 */
void iminbinpq_decrease(struct iminbinarypq* ipq, int ki, void* value) {
	imindarypq_decrease( ipq->ipq, ki, value );
}

/*
 * Strictly increases the value associated with 'ki' to 'value'
 * Note: If freedata() is defined it will be executed to release old value resources!
 */
void iminbinpq_increase(struct iminbinarypq* ipq, int ki, void* value) {
	imindarypq_increase( ipq->ipq, ki, value );
}

/*
 * Prints the heap indexed priority queue elements.
 */
void iminbinpq_print( struct iminbinarypq* ipq ) {
	imindarypq_print( ipq->ipq );
}

/*
 * Releases priority queue instance from memory.
 */
void iminbinpq_destroy(struct iminbinarypq* ipq) {
	imindarypq_destroy( ipq->ipq );
	free(ipq);
}

