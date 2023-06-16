/***************************************************************************
 * linklist.h
 *
 *  Created on: 24/02/2023
 *      Author: Tiago C. Teixeira
 *
 *  Description: C program for generic linked list.
 *
 *-----------------------------------------------------------------------
 *
 *  Advantages of Linked Lists over arrays:
 *
 *    Dynamic Array.
 *    Ease of Insertion/Deletion.
 *    Insertion at the beginning is a constant time operation and takes O(1) time, as
 *    compared to arrays where inserting an element at the beginning takes O(n) time,
 *    where n is the number of elements in the array.
 *
 *  Drawbacks of Linked Lists:
 *
 *    Random access is not allowed. We have to access elements sequentially starting
 *    from the first node(head node). So we cannot do a binary search with linked
 *    lists efficiently with its default implementation.
 *    Extra memory space for a pointer is required with each element of the list.
 *    Not cache-friendly. Since array elements are contiguous locations, there is the
 *    locality of reference which is not there in the case of linked lists.
 *    It takes a lot of time in traversing and changing the pointers.
 *    Reverse traversing is not possible in singly linked lists.
 *    It will be confusing when we work with pointers.
 *    Direct access to an element is not possible in a linked list as in an array by
 *    index.
 *    Searching for an element is costly and requires O(n) time complexity.
 *    Sorting of linked lists is very complex and costly.
 *    Appending an element to a linked list is a costly operation, and takes O(n) time,
 *    where n is the number of elements in the linked list, as compared to arrays that
 *    take O(1) time.
 *
 ***********************************************************************/


#include <stdlib.h>
#include <assert.h>
#include "linkedlist.h"

/*
 * Creates a new linked list.
 * */
struct linkedlist* linkedlist_create(int (*isequalfunc)(const void* a, const void* b)) {
	struct linkedlist* result = NULL;
	result = malloc(sizeof(*result));
	if (result != NULL) {
		struct linkedlistnode** hp = malloc(sizeof *hp);
		if (hp != NULL)
		{
			*hp = NULL;
			result->headp = hp;

			struct linkedlistnode** tp = malloc(sizeof *tp);
			if (tp != NULL)	{
				*tp = NULL;
				result->tailp = tp;
			}
			else {
				free(hp);
				free(result);
				result = NULL;
			}
		}
		else {
			free(result);
			result = NULL;
		}
	}

	result->size = 0;
	result->isequalfunc = isequalfunc;
	return result;
}

/*
 * Checks if list is empty.
 * Returns 1 if is empty, 0 otherwise.
 * */
int linkedlist_isempty(const struct linkedlist* list) {
	return (list->size == 0);
}

/*
 * Adds a new element at begin of linked list.
 * Returns 1 if succeeded, 0 otherwise.
 * */
int linkedlist_push(struct linkedlist* list, void* new_data) {
	int result = 0;
	assert(list != NULL);

	struct linkedlistnode* new_node = malloc(sizeof(*new_node));

	if (new_node != NULL) {
		if (linkedlist_isempty(list)) {
			new_node->next = NULL;
			*(list->tailp) = new_node;	// tail points to new node
		}
		else {
			// next points to node pointed by list head pointer
			new_node->next = *(list->headp);
		}

		new_node->data = new_data;

		// head now points to new node
		*(list->headp) = new_node;
		list->size += 1;	// increment size
		result = 1;
	}

	return result;
}

/*
 * Adds a new element at end of linked list.
 * Returns 1 if succeeded, 0 otherwise.
 * */
int linkedlist_append(struct linkedlist* list, void* new_data) {
	int result = 0;
	assert(list != NULL);

	struct linkedlistnode* new_node = malloc(sizeof(*new_node));

	if (new_node != NULL) {
		new_node->next = NULL;

		if (linkedlist_isempty(list)) {
			*(list->headp) = new_node;			// head points to new node
		}
		else {
			(*(list->tailp))->next = new_node;	// tail next points to new node
		}

		new_node->data = new_data;

		// tail now points to new node
		*(list->tailp) = new_node;
		list->size += 1;	// increment size
		result = 1;
	}

	return result;
}

/*
 * Reverses a linked list.
 *
 * Follow the steps below to solve the problem:
 *
 * Initialize three pointers prev as NULL, curr as head, and next as NULL.
 * Iterate through the linked list. In a loop, do the following:
 *   Before changing the next of curr, store the next node
 *       next = curr -> next
 *   Now update the next pointer of curr to the prev
 *       curr -> next = prev
 *   Update prev as curr and curr as next
 *       prev = curr
 *       curr = next
 *
 * Time Complexity: O(N), Traversing over the linked list of size N.
 * Auxiliary Space: O(1)
 *
 * */
void linkedlist_reverse(struct linkedlist* l)
{
	if (linkedlist_isempty(l))
		return;

    struct linkedlistnode* prev = NULL;
    struct linkedlistnode* current = *(l->headp);// *head_ref;
    struct linkedlistnode* next = NULL;
    *(l->tailp) = current;	// tail points to current head

    while (current != NULL) {
        // Store next
        next = current->next;

        // Reverse current node's pointer
        current->next = prev;

        // Move pointers one position ahead.
        prev = current;
        current = next;
    }

    *(l->headp) = prev;
}

/*
 * Gets the first node.
 * */
struct linkedlistnode* linkedlist_getfirst(const struct linkedlist* list) {
	if (list->size == 0)
		return NULL;
	else
		return *(list->headp);
}

/*
 * Gets the last node.
 * */
struct linkedlistnode* linkedlist_getlast(const struct linkedlist* list) {
	if (list->size == 0)
		return NULL;
	else
		return *(list->tailp);
}

/*
 * Removes the first node from list.
 * Returns the remove node if succeeded, NULL otherwise.
 * */
struct linkedlistnode* linkedlist_remove_first(struct linkedlist* list) {
	struct linkedlistnode* result = NULL;
	assert(list != NULL);

	struct linkedlistnode* first = *(list->headp);

	if (first != NULL) {
		(*(list->headp)) = first->next;	// head points to first next first
		first->next = NULL;				// disconnect first to remove from list
		list->size -= 1;

		if (list->size == 0)	// is empty?
			(*(list->tailp)) = NULL;

		result = first;
	}

	return result;
}

/*
 * Removes the node from list that matches given data.
 * Returns the remove node if succeeded, NULL otherwise.
 * */
struct linkedlistnode* linkedlist_remove(struct linkedlist* list, const void* data) {
	struct linkedlistnode* result = NULL;
	assert(list != NULL);

	struct linkedlistnode* node = *(list->headp);
	struct linkedlistnode* prev_node = node;

	if (node != NULL) {
		while ((node != NULL) && (!list->isequalfunc(node->data, data))) {
			prev_node = node;
			node = node->next;
		}

		if (node != NULL) {
			// first node?
			if (prev_node == node) {
				// yes, make head point to next node
				*(list->headp) = node->next;
			}
			else {
				// put founded node out of list
				prev_node->next = node->next;
			}

			list->size -= 1;	// decrement size

			if (list->size == 0)
				*(list->tailp) = NULL;
			else if ((*(list->tailp)) == node)	// remove last node?
				*(list->tailp) = prev_node;		// tail points to previous node

			node->next = NULL;	// disconnect from list
			result = node;
		}
	}

	return result;
}

/*
 * Gets list node that matches given data..
 * Returns reference to founded node if succeeded, NULL otherwise.
 * Note: Do not free memory from returned node reference. That is a job to be done
 * 		 by the linked list when destroyed.
 * */
void* linkedlist_getnode(const struct linkedlist* list, const void* data) {
	assert(list != NULL);
	struct linkedlistnode* node = *(list->headp);
	while ((node != NULL) && (!list->isequalfunc(node->data, data))) {
		node = node->next;
	}

	return node;
}

/*
 * Gets data from a node at given position (zero based) in list.
 * Returns reference to founded data if succeeded, NULL otherwise.
 * */
void* linkedlist_getdata_at(const struct linkedlist* list, uint position) {
	assert(list != NULL);
	if (list->size > position) {
		struct linkedlistnode* node = linkedlist_getfirst(list);
		for (int pos = 0; pos < position; ++pos) {
			node = node->next;
		}

		return node->data;
	}

	return NULL;
}

/*
 * Gets data from a node that matches given data.
 * Returns reference to founded data if succeeded, NULL otherwise.
 * Note: Do not free memory from returned node reference. That is a job to be done
 * 		 by the linked list when destroyed.
 * */
void* linkedlist_getdata(const struct linkedlist* list, const void* data) {
	void* result = NULL;
	assert(list != NULL);
	struct linkedlistnode* node = linkedlist_getnode(list, data);

	// found?
	if (node != NULL) {
		result = node->data;
	}

	return result;
}

/*
 * Releases the entire list and their nodes.
 * */
void linkedlist_destroy(struct linkedlist* list) {
	assert(list != NULL);
	struct linkedlistnode* node = NULL;

	while ((node = linkedlist_remove_first(list)) != NULL)  {
		free(node);
	}

	free(list->headp);
	free(list->tailp);
	free(list);
}
