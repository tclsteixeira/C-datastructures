/*****************************************************************************
 * circlinklist.c
 *
 *   Created on: 25/02/2023
 *       Author: Tiago C. Teixeira
 *
 *  Description: C program for generic circular linked list.
 *
 -----------------------------------------------------------
 *
 * Advantages of Circular Linked Lists:
 *
 *    Any node can be a starting point. We can traverse the whole list by starting from
 *    any point. We just need to stop when the first visited node is visited again.
 *    Useful for implementation of a queue. Unlike this implementation, we don’t need
 *    to maintain two pointers for front and rear if we use a circular linked list.
 *    We can maintain a pointer to the last inserted node and the front can always be
 *    obtained as next of last.
 *
 *    Circular lists are useful in applications to repeatedly go around the list. For
 *    example, when multiple applications are running on a PC, it is common for the
 *    operating system to put the running applications on a list and then cycle through
 *    them, giving each of them a slice of time to execute, and then making them wait
 *    while the CPU is given to another application. It is convenient for the operating
 *    system to use a circular list so that when it reaches the end of the list it can
 *    cycle around to the front of the list.
 *    Circular Doubly Linked Lists are used for the implementation of advanced data
 *    structures like the Fibonacci Heap.
 *    Implementing a circular linked list can be relatively easy compared to other more
 *    complex data structures like trees or graphs.
 *
 * Disadvantages of circular linked list:
 *
 *    Compared to singly linked lists, circular lists are more complex.
 *    Reversing a circular list is more complicated than singly or doubly reversing a
 *    circular list.
 *    It is possible for the code to go into an infinite loop if it is not handled carefully.
 *    It is harder to find the end of the list and control the loop.
 *    Although circular linked lists can be efficient in certain applications, their
 *    performance can be slower than other data structures in certain cases, such as
 *    when the list needs to be sorted or searched.
 *    Circular linked lists don’t provide direct access to individual nodes
 *
 * Applications of circular linked lists:
 *
 *    Multiplayer games use this to give each player a chance to play.
 *    A circular linked list can be used to organize multiple running applications
 *    on an operating system. These applications are iterated over by the OS.
 *    Circular linked lists can be used in resource allocation problems.
 *    Circular linked lists are commonly used to implement circular buffers,
 *    Circular linked lists can be used in simulation and gaming.
 *
 * Why circular linked list?
 *
 *    A node always points to another node, so NULL assignment is not necessary.
 *    Any node can be set as the starting point.
 *    Nodes are traversed quickly from the first to the last.
 *
 *	Source: https://www.geeksforgeeks.org/circular-singly-linked-list-insertion/?ref=lbp
 *
 ***************************************************************************/


#include "circlinkedlist.h"

#include <stdlib.h>
#include <assert.h>

/*
 * Creates a new empty circular linked list.
 * */
struct circlinkedlist* circlinkedlist_create( circlinkedlist_isequal isequalfunc,
		  	  	  	  	  	  	  	  	  	  circlinkedlist_printdata printdatafunc,
											  circlinkedlist_freedata freedatafunc) {
	struct circlinkedlist* result = NULL;
	result = malloc(sizeof(*result));
	if (result != NULL) {
		result->isequal = isequalfunc;
		result->printdata = printdatafunc;
		result->freedata = freedatafunc;
		struct circlinkedlistnode** tp = malloc(sizeof *tp);
		if (tp != NULL) {
			*tp = NULL;
			result->tailp = tp;
		}
		else {
			free(result);
			result = NULL;
		}

		result->size = 0;
	}

	return result;
}

/*
 * Checks if list is empty.
 * Returns 1 is is empty, 0 otherwise.
 * */
int circlinkedlist_isempty(struct circlinkedlist* list) {
	return (list->size == 0);
}

/*
 * Inserts a new node in a empty list.
 * Note: Private for internal use only.
 * */
int circlinkedlist_insert_empty(struct circlinkedlist* list, void* data) {
	int result = 0;

	assert(circlinkedlist_isempty(list));

	struct circlinkedlistnode* new_node = malloc(sizeof(*new_node));
	if (new_node == NULL) {
		return result;
	}
	else {
		new_node->data = data;
		new_node->next = new_node;
		*(list->tailp) = new_node;	// and last node
		list->size = 1;
		result = 1;
	}

	return result;
}

/*
 * Inserts at beginning of list.
 * Returns 1 if succeeded, 0 otherwise.
 * */
int circlinkedlist_insert_at_begin(struct circlinkedlist* list, void* data) {
	int result = 0;
	if (circlinkedlist_isempty(list))
		result = circlinkedlist_insert_empty(list, data);
	else {
		struct circlinkedlistnode* new_node = malloc(sizeof(*new_node));
		if (new_node == NULL) {
			return result;
		}
		else {
			new_node->data = data;
			new_node->next = (*(list->tailp))->next;	// new node points to node pointed by last node
			(*(list->tailp))->next = new_node;			// last node points to new node
			list->size += 1;
			result = 1;
		}
	}

	return result;
}

/*
 * Inserts at end of list.
 * Returns 1 if succeeded, 0 otherwise.
 * */
int circlinkedlist_insert_at_end(struct circlinkedlist* list, void* data) {
	int result = 0;
	if (circlinkedlist_isempty(list))
		result = circlinkedlist_insert_empty(list, data);
	else {
		struct circlinkedlistnode* new_node = malloc(sizeof(*new_node));
		if (new_node == NULL) {
			return result;
		}
		else {
			new_node->data = data;
			// update links
			new_node->next = (*(list->tailp))->next;	// new node points to first node
			(*(list->tailp))->next = new_node;			// last node points to new node
			(*(list->tailp)) = new_node;				// new node becomes last node
			list->size += 1;
			result = 1;
		}
	}

	return result;
}

/*
 * Inserts after given node.
 * Returns 1 if succeeded, 0 otherwise.
 * */
int circlinkedlist_insert_after(struct circlinkedlist* list, struct circlinkedlistnode* node, void* data) {
	int result = 0;
	if ((*(list->tailp)) == node) {
		result = circlinkedlist_insert_at_end(list, data);
	}
	else {
		struct circlinkedlistnode* new_node = malloc(sizeof(*new_node));
		if (new_node == NULL) {
			return result;
		}
		else {
			new_node->data = data;
			// update links
			new_node->next = node->next;	// new node points to node next node
			node->next = new_node;			// node points to new node
			list->size += 1;
			result = 1;
		}
	}

	return result;
}

/*
 * Gets the node that matches given data.
 * Returns reference to founded node if succeeded, NULL otherwise.
 * Note: Do not free memory from returned node reference. That is a job to be done
 * 		 by the list when destroyed.
 * */
struct circlinkedlistnode* circlinkedlist_getnode(struct circlinkedlist* list, const void* data) {
	if (circlinkedlist_isempty(list))
		return NULL;

	struct circlinkedlistnode* node = (*(list->tailp))->next;	// first node
	int i = 0;
	while ((i < list->size) && (!list->isequal(node->data, data))) {
		node = node->next;
		++i;
	}

	// beyond end of list?
	if (i == list->size)
		return NULL;
	else
		return node;
}

/*
 * Gets the start node.
 * Returns reference to start node if succeeded, NULL otherwise.
 * Note: Do not free memory from returned reference. That is a job to be done
 * 		 by the linked list when destroyed.
 * */
struct circlinkedlistnode* circlinkedlist_getstart(struct circlinkedlist* list) {
	if (circlinkedlist_isempty(list))
		return NULL;
	else {
		return (*(list->tailp))->next;
	}
}


/*
 * Gets data from a node that matches given data..
 * Returns reference to founded data if succeeded, NULL otherwise.
 * Note: Do not free memory from returned reference. That is a job to be done
 * 		 by the linked list when destroyed.
 * */
void* circlinkedlist_getdata(struct circlinkedlist* list, const void* data) {
	void* result = NULL;
	if (circlinkedlist_isempty(list))
		return result;
	else {
		struct circlinkedlistnode* node = circlinkedlist_getnode(list, data);

		if (node != NULL)
			result = node->data;
	}

	return result;
}

/*
 * Removes first node.
 * Returns removed node if succeeded, NULL otherwise.
 * */
struct circlinkedlistnode* circlinkedlist_remove_first(struct circlinkedlist* list) {
	struct circlinkedlistnode* result = NULL;

	if (!circlinkedlist_isempty(list)) {
		struct circlinkedlistnode* first = (*(list->tailp))->next;
		struct circlinkedlistnode* last = (*(list->tailp));

		if (first == last) {
			(*(list->tailp))->next = NULL;	// make empty list
			(*(list->tailp)) = NULL;
		}
		else {
			last->next = first->next;		// last next points to old first next
			first->next = NULL;				// disconnect first from list
		}

		result = first;
		list->size -= 1;
	}

	return result;
}

/*
 * Removes item from list.
 * Returns reference to removed item if succeeded, NULL otherwise.
 * Note: Node to remove will be disconnected from list but not released from memory.
 * 		 You must do it yourself later.
 * */
struct circlinkedlistnode* circlinkedlist_remove(struct circlinkedlist* list, const void* data) {
	struct circlinkedlistnode* result = NULL;
	if (circlinkedlist_isempty(list))
		return result;
	else {
		struct circlinkedlistnode* node = (*(list->tailp))->next;	// start from beginning
		struct circlinkedlistnode* first = node;
		struct circlinkedlistnode* last = *(list->tailp);;
		struct circlinkedlistnode* prev_node = NULL;
		do {
			if (node->data == data) {
				if (node == first)
					result = circlinkedlist_remove_first(list);
				else {
					prev_node->next = node->next;
					node->next = NULL;	// disconnect node to remove from list

					if (node == last) {
						(*(list->tailp)) = prev_node;
					}

					result = node;
				}
			}
			else {
				prev_node = node;
				node = node->next;		// move to next node
			}
		} while ((result == NULL) && (node != first));
	}

	return result;
}

/**
 * Releases all resources from list (items included).
 */
void circlinkedlist_destroy(struct circlinkedlist* list) {
	struct circlinkedlistnode* node = NULL;
	while ((node = circlinkedlist_remove_first(list)) != NULL) {
		if (list->freedata)
			if (node->data != NULL)
				list->freedata(node->data);

		free(node);
	}

	free(list->tailp);
	free(list);
}

