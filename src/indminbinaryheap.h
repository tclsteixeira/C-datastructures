/*
 * indexedminbinaryheap.h
 *
 *  Created on: 26/09/2023
 *      Author: Tiago C. Teixeira
 * Description: Headers for an indexed min binary heap (indexed priority queue).
 */

#ifndef INDMINBINARYHEAP_H_
	#define INDMINBINARYHEAP_H_
	#include "indmindaryheap.h"

	typedef idarypq_comparefunc iminbinpq_comparefunc;
	typedef idarypq_printdata iminbinpq_printdata;
	typedef idarypq_freedata iminbinpq_freedata;

	struct iminbinarypq {
		struct idarypq* ipq;
	};

	/*
	 * Initializes an indexed min binary heap with a maximum capacity of maxSize.
	 */
	struct iminbinarypq* iminbinpq_create( size_t maxSize,
										   iminbinpq_comparefunc comparefunc,
										   iminbinpq_printdata printdatafunc,
										   iminbinpq_freedata freedatafunc );

	/*
	 * Returns the heap element value stored at a given key index.
	 */
	void* iminbinpq_valueof(struct iminbinarypq* ipq, int ki);

	/*
	 * Checks if the priority heap is empty.
	 */
	int iminbinpq_isempty(struct iminbinarypq* ipq);

	/*
	 * Gets the number of elements on the indexed priority queue.
	 */
	size_t iminbinpq_getsize(struct iminbinarypq* ipq);

	/*
	 * Checks if an element with a given key index exists in the heap or not.
	 */
	int iminbinpq_contains( struct iminbinarypq* ipq , int ki );

	/*
	 * Inserts a new element in the heap at a given key index.
	 * Note: If key index already contains an element in the heap, an error will be throw.
	 */
	void iminbinpq_insert( struct iminbinarypq* ipq, int ki, void* value );

	/*
	 * Deletes an element (value) in the heap for a given key index.
	 * Returns the deleted element if succeeded, NULL otherwise.
	 */
	void* iminbinpq_delete(struct iminbinarypq* ipq, int ki);

	/*
	 * Returns the priority value (at root) from heap but does not remove it.
	 * The time Complexity of this operation is O(1).
	 */
	void* iminbinpq_peek( struct iminbinarypq* ipq );

	/*
	 * Extracts element (with high priority) at top of the heap.
	 */
	void* iminbinpq_extractkey( struct iminbinarypq* ipq );

	/*
	 * Returns the next key index to be pooled from the heap.
	 */
	int iminbinpq_peekkeyindex( struct iminbinarypq* ipq );

	/*
	 * Removes the high priority element from the heap at a given key index (ki).
	 * Returns the key index of the removed element.
	 */
	int iminbinpq_extractkeyindex( struct iminbinarypq* ipq );

	/*
	 * Updates a given value and returns old value.
	 */
	void* iminbinpq_update(struct iminbinarypq* ipq, int ki, void* value);

	/*
	 * Strictly decreases the value associated with 'ki' to 'value'
	 * Note: If freedata() is defined it will be executed to release old value resources!
	 */
	void iminbinpq_decrease(struct iminbinarypq* ipq, int ki, void* value);

	/*
	 * Strictly increases the value associated with 'ki' to 'value'
	 * Note: If freedata() is defined it will be executed to release old value resources!
	 */
	void iminbinpq_increase(struct iminbinarypq* ipq, int ki, void* value);

	/*
	 * Prints the heap indexed priority queue elements.
	 */
	void iminbinpq_print( struct iminbinarypq* ipq );

	/*
	 * Releases priority queue instance from memory.
	 */
	void iminbinpq_destroy(struct iminbinarypq* ipq);

#endif /* INDMINBINARYHEAP_H_ */
