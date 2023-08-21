/*
 * dbllinkedlistdeque.c
 *
 *  Created on: 18/08/2023
 *      Author: Tiago C. Teixeira
 * Description: C implementation of a deque using a double linked list.
 *
 * Complexity Analysis:
 *
 *    Time Complexity : Time complexity of operations like push_front(), push_back(),
 *    pop_front(), pop_back() is O(1). The Time Complexity of erase() is O(n).
 *
 *    ---------------------------------------
 *    |	Operation 	  | 	Time complexity	|
 *    ---------------------------------------
 *    |	push_front()  | 	O(1)			|
 *    |	push_back()	  | 	O(1)			|
 *    |	pop_front()	  |		O(1)			|
 *    |	pop_back 	  |		O(1)			|
 *    |	erase()		  | 	O(n)			|
 *	  ---------------------------------------
 *
 *    Auxiliary space: O(1)
 *
 *    Source: https://www.geeksforgeeks.org/implementation-deque-using-doubly-linked-list/?ref=ml_lbp
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dbllinkedlistdeque.h"
#include "dbllinkedlist.h"

/*
 * Create deque instance.
 */
struct dbllinkedlistdeque* dbllinkedlistdeque_create(
									  dbllinkedlist_printdata printdatafunc,
									  dbllinkedlist_freedata freedatafunc )
{
	struct dbllinkedlistdeque* result = (struct dbllinkedlistdeque*)malloc(sizeof(*result));

	if (result == NULL)
		printf("Memory error when allocating double linked list deque struct!\n");
	else
	{
		struct dbllinkedlist* list = dbllinkedlist_create(NULL, printdatafunc, freedatafunc);

		if (list == NULL)
		{
			printf("Memory error when allocating double linked list struct for deque!\n");
			free(result);
			abort();
		}
		else
		{
			result->list = list;
			return result;
		}
	}

	return NULL;
}

/*
 * Function to check if deque is empty or not
 */
int dbllinkedlistdeque_empty(struct dbllinkedlistdeque* q)
{
	assert(q != NULL);
	return (q->list->size == 0);
}

/*
 * Function to get number of elements of deque
 */
size_t dbllinkedlistdeque_size(struct dbllinkedlistdeque* q)
{
	assert(q != NULL);
	return (q->list->size);
}

/*
 * Function to find the front element of the deque
 */
void* dbllinkedlistdeque_front(struct dbllinkedlistdeque* q)
{
	assert(q != NULL);
	if (dbllinkedlistdeque_empty(q))
	{
		printf("Deque underflow\n");
		abort();
	}
	else
		return (dbllinkedlist_getlast(q->list)->data);
}

/*
 * Function to find the last element of the deque
 */
void* dbllinkedlistdeque_back(struct dbllinkedlistdeque* q)
{
	assert(q != NULL);
	if (dbllinkedlistdeque_empty(q))
	{
		printf("Deque underflow\n");
		abort();
	}
	else
		return (dbllinkedlist_getfirst(q->list)->data);
}

/*
 * Function to insert the element to the back of the deque
 *
 * 1. Allocate space for a newNode of doubly linked list.
 * 2. IF newNode == NULL, then
 * 3.     print "Overflow"
 * 4.  ELSE
 * 5.      IF rear == NULL, then
 * 6.         front = rear = newNode
 * 7.     ELSE
 * 8.         newNode->prev = rear
 * 9.         rear->next = newNode
 * 10.        rear = newNode
 */
void dbllinkedlistdeque_push_back(struct dbllinkedlistdeque* q, void* x)
{
	assert(q != NULL);
	if (!(dbllinkedlist_insert_at_begin(q->list, x)))
	{
		printf("Failed to insert at back.\n");
		abort();
	}
}

/*
 * Function to insert the element
 * to the front of the deque
 *
 * 1. Allocate space for a newNode of doubly linked list.
 * 2. IF newNode == NULL, then
 * 3.     print "Overflow"
 * 4. ELSE
 * 5.     IF front == NULL, then
 * 6.         rear = front = newNode
 * 7.     ELSE
 * 8.         newNode->next = front
 * 9.         front->prev = newNode
 * 10.        front = newNode
 */
void dbllinkedlistdeque_push_front(struct dbllinkedlistdeque* q, void* x)
{
	assert(q != NULL);
	if (!(dbllinkedlist_insert_at_end(q->list, x)))
	{
		printf("Failed to insert at front.\n");
		abort();
	}
}

/*
 * Function to delete the element from the front of the deque.
 * Returns removed node if succeeded.
 *
 * 1. IF front == NULL
 * 2.     print "Underflow"
 * 3. ELSE
 * 4.     Initialize temp = front
 * 5.     front = front->next
 * 6.     IF front == NULL
 * 7.         rear = NULL
 * 8.     ELSE
 * 9.         front->prev = NULL
 *
 * 10     Deallocate space for temp
 */
void* dbllinkedlistdeque_pop_front(struct dbllinkedlistdeque* q)
{
	assert(q != NULL);
	void* result = NULL;
	if (dbllinkedlistdeque_empty(q))
	{
		printf("Deque underflow\n");
		abort();
	}
	else
	{
		struct dbllinkedlistnode* node = dbllinkedlist_remove_last(q->list);
		if (node)
		{
			result = node->data;
			free(node);
		}
	}

	return result;
}

/*
 * Function to remove the element from the back of the deque.
 * Returns removed element if succeeded.
 *
 * 1. IF front == NULL
 * 2.     print "Underflow"
 * 3. ELSE
 * 4.     Initialize temp = rear
 * 5.     rear = rear->prev
 * 6.     IF rear == NULL
 * 7.         front = NULL
 * 8.     ELSE
 * 9.         rear->next = NULL
 * 10     Deallocate space for temp
 *
 */
void* dbllinkedlistdeque_pop_back(struct dbllinkedlistdeque* q)
{
	assert(q != NULL);
	void* result = NULL;
	if (dbllinkedlistdeque_empty(q))
	{
		printf("Deque underflow\n");
		abort();
	}
	else
	{
		struct dbllinkedlistnode* node = dbllinkedlist_remove_first(q->list);
		if (node)
		{
			result = node->data;
			free(node);
		}
	}

	return result;
}

/*
 * Function to remove all elements from list.
 */
void dbllinkedlistdeque_erase(struct dbllinkedlistdeque* q)
{
	assert(q != NULL);
	dbllinkedlist_erase(q->list);
}

/*
 * Release array deque instance from memory.
 * */
void dbllinkedlistdeque_destroy(struct dbllinkedlistdeque* q)
{
	dbllinkedlist_destroy(q->list);
	free(q);
}


