/********************************************************************************
 * linkedlistqueue.c
 *
 *  Created on: 13/04/2023
 *      Author: Tiago C. Teixeira
 * Description: Implements a generic queue in C with a linkedlist.
 *
 *
 * Definition:
 *
 * 		A Queue is defined as a linear data structure that is open at both ends
 * 		and the operations are performed in First In First Out (FIFO) order.
 *
 * 		We define a queue to be a list in which all additions to the list are made
 * 		at one end, and all deletions from the list are made at the other end.
 * 		The element which is first pushed into the order, the operation is first
 * 		performed on that.
 *
 *
 * Time Complexity:
 *
 * 		O(1), The time complexity of both operations enqueue() and dequeue() is O(1)
 * 		as it only changes a few pointers in both operations.
 *
 *	Auxiliary Space:
 *
 *		O(1), The auxiliary Space of both operations enqueue() and dequeue() is O(1)
 *		as constant extra space is required.
 *
 *
 * Applications of Queue:
 *
 * 		Queue is used when things don’t have to be processed immediately, but have
 * 		to be processed in First In First Out order like Breadth First Search. This
 * 		property of Queue makes it also useful in following kind of scenarios.
 *
 *     	- When a resource is shared among multiple consumers. Examples include CPU
 *     	  scheduling, Disk Scheduling.
 *     	- When data is transferred asynchronously (data not necessarily received at
 *     	  same rate as sent) between two processes. Examples include IO Buffers,
 *     	  pipes, file IO, etc.
 *     	- Queue can be used as an essential component in various other data structures.
 *
 * Basic Operations on Queue:
 *
 *    enqueue(): Inserts an element at the end of the queue i.e. at the rear end.
 *    dequeue(): This operation removes and returns an element that is at the front end of the queue.
 *    front(): This operation returns the element at the front end without removing it.
 *    rear(): This operation returns the element at the rear end without removing it.
 *    isEmpty(): This operation indicates whether the queue is empty or not.
 *    isFull(): This operation indicates whether the queue is full or not.
 *    size(): This operation returns the size of the queue i.e. the total number of elements it contains.
 *
 ********************************************************************************/

#include <stdlib.h>
#include <limits.h>

#ifndef LINKEDLIST_H_
	#include "linkedlist.h"
#endif /* LINKEDLIST_H_ */

#ifndef LINKEDLISTQUEUE_H_
	#include "linkedlistqueue.h"
#endif /* LINKLIST_H_ */

/*
 * Creates a new instance of a linkedlistqueue.
 * Returns a new empty queue instance if succeeded, NULL otherwise.
 * Max number of nodes will be set to maximum value a uint can store.
 * */
struct linkedlistqueue* linkedlistqueue_create( ) {
	return linkedlistqueue_createWithSizeLimit(UINT_MAX, NULL);
}

/*
 * Creates a new instance of a linkedlistqueue with function to free data.
 * */
struct linkedlistqueue* linkedlistqueue_create_freedata( linkedlist_freedata freedata )
{
	return linkedlistqueue_createWithSizeLimit(UINT_MAX, freedata );
}

/*
 * Creates a new instance of a linkedlistqueue.
 * Returns a new empty queue instance if succeeded, NULL otherwise.
 * */
struct linkedlistqueue* linkedlistqueue_createWithSizeLimit( uint maxsize,
															 linkedlist_freedata freedata )
{
	struct linkedlistqueue* result = NULL;
	struct linkedlist* queue = linkedlist_create( NULL, freedata );

	if (queue == NULL)
		return NULL;
	else {
		result = malloc(sizeof(*result));
		result->maxsize = maxsize;
		result->queue = queue;
		result->front = *(queue->headp);
		result->rear = *(queue->tailp);
	}

	return result;
}

/*
 * Gets the size of queue.
 * Returns the size of queue.
 * */
uint linkedlistqueue_getsize(struct linkedlistqueue* q) {
	return q->queue->size;
}

/*
 * Checks if queue is empty (has no elements).
 * Returns 1 if is empty, 0 otherwise.
 * */
int linkedlistqueue_isempty(struct linkedlistqueue* q) {
	int result = 0;
	if (linkedlist_isempty(q->queue))
		result = 1;

	return result;
}

/*
 * Checks if queue is full (there is no room for more elements).
 * Returns 1 if is full, 0 otherwise.
 * */
int linkedlistqueue_isfull(struct linkedlistqueue* q) {
	return (linkedlistqueue_getsize(q) == q->maxsize);
}

/*
 * Push a new element at rear of queue.
 * Returns 1 if succeded, 0 otherwise.
 * */
int linkedlistqueue_enqueue(struct linkedlistqueue* q, void* data) {
	int result = 0;

	// is full?
	if (linkedlistqueue_isfull(q)) {
		return result;
	}
	else {
		// still empty?
		if (q->rear == NULL) {
			if (linkedlist_append(q->queue, data)) {
				q->rear = linkedlist_getfirst(q->queue);
				q->front = q->rear;
				result = 1;
			}
			else {
				// fail to insert element
			}
		}
		else {
			// queue not empty
			// append at end
			if (linkedlist_append(q->queue, data)) {
				q->rear = linkedlist_getlast(q->queue);
				result = 1;
			}
			else {
				// fail to insert element
			}
		}
	}

	return result;
}

/*
 * Pops the element in front of queue.
 * Returns popped element if succeded, NULL otherwise.
 * */
void* linkedlistqueue_dequeue(struct linkedlistqueue* q) {
	void* result = NULL;
	struct linkedlistnode* node = linkedlist_remove_first(q->queue);

	if (node != NULL) {
		// uodate front and rear
		q->front = linkedlist_getfirst(q->queue);
		q->rear = linkedlist_getlast(q->queue);
		result = node->data;
		free(node);
	}

	return result;
}

/*
 * Gets the element at front of queue without removing it.
 * Returns the element at front if succeeded, NULL otherwise.
 * */
void* linkedlistqueue_peekfront(struct linkedlistqueue* q) {
	if (q->front != NULL)
		return q->front->data;

	return NULL;
}

/*
 * Gets the element at rear of queue without removing it.
 * Returns the element at rear if succeeded, NULL otherwise.
 * */
void* linkedlistqueue_peekrear(struct linkedlistqueue* q) {
	if (q->rear != NULL)
			return q->rear->data;

	return NULL;
}

/*
 * Releases queue instance from memory.
 * */
void linkedlistqueue_destroy(struct linkedlistqueue* q) {
	q->front = NULL;
	q->rear = NULL;
	q->maxsize = 0;
	linkedlist_destroy(q->queue);
	free(q);
}


