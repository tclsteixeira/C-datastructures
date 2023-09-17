/*
 * circdbllinkedlist.c
 *
 *  Created on: 20/03/2023
 *      Author: Tiago C. Teixeira
 * Description: Implements a generic circular double linked list in C.
 *
 * Time Complexity: O(N)
 * Auxiliary Space: O(1), As constant extra space is used.
 *
 * Advantages of circular doubly linked list:
 *
 *     The list can be traversed from both directions i.e. from head to tail or from
 *     tail to head.
 *     Jumping from head to tail or from tail to head is done in constant time O(1).
 *     Circular Doubly Linked Lists are used for the implementation of advanced data
 *     structures like the Fibonacci Heap.
 *
 * Disadvantages of circular doubly linked list:
 *
 *     It takes slightly extra memory in each node to accommodate the previous pointer.
 *     Lots of pointers are involved while implementing or doing operations on a list.
 *     So, pointers should be handled carefully otherwise data of the list may get lost.
 *
 * Applications of Circular doubly linked list:
 *
 *     Managing song playlists in media player applications.
 *     Managing shopping carts in online shopping.
 *
 *
 *****************************************************************************/


#include "circdbllinkedlist.h"

#include <stdlib.h>
#include <assert.h>

/*
 * Creates a new empty circular double linked list.
 * */
struct circdbllinkedlist* circdbllinkedlist_create( circdbllinkedlist_isequal isequalfunc,
													circdbllinkedlist_printdata printdatafunc,
													circdbllinkedlist_freedata freedatafunc )
{
	struct circdbllinkedlist* result = NULL;
	result = malloc(sizeof(*result));

	if (result != NULL) {
		struct circdbllinkedlistnode** hp = malloc(sizeof *hp);
		if (hp != NULL) {
			*hp = NULL;
			result->headp = hp;
		}
		else {
			free(result);
			result = NULL;
		}

		result->isequal = isequalfunc;
		result->printdata = printdatafunc;
		result->freedata = freedatafunc;
		result->size = 0;
	}

	return result;
}

/*
 * Checks if list is empty.
 * Returns 1 if is empty, 0 otherwise.
 * */
int circdbllinkedlist_isempty(const struct circdbllinkedlist* list) {
	return (list->size) == 0;
}

/*
 * Inserts at beginning of list.
 * Returns 1 if succeeded, 0 otherwise.
 * */
int circdbllinkedlist_insert_empty(struct circdbllinkedlist* list, void* data) {
	int result = 0;
	assert(list != NULL);

	if (list->size == 0) {
		struct circdbllinkedlistnode* new_node = malloc(sizeof(*new_node));
		if (new_node == NULL) {
			return result;
		}
		else {
			new_node->data = data;
			new_node->next = new_node;
			new_node->prev = new_node;
			(*(list->headp)) = new_node;
			list->size = 1;
			result = 1;
		}
	}

	return result;
}

/*
 * Inserts at beginning of list.
 * Returns 1 if succeeded, 0 otherwise.
 * */
int circdbllinkedlist_insert_at_begin(struct circdbllinkedlist* list, void* data) {
	int result = 0;
	assert(list != NULL);

	if (list->size == 0)
		result = circdbllinkedlist_insert_empty(list, data);
	else {
		struct circdbllinkedlistnode* first = *(list->headp);
		struct circdbllinkedlistnode* new_node = malloc(sizeof(*new_node));
		if (new_node == NULL)
			return result;
		else {
			new_node->data = data;
			new_node->next = first;			// new node next points to first node
			new_node->prev = first->prev;	// new node prev points to first prev node
			first->prev = new_node;			// first prev points to new node
			*(list->headp) = new_node;		// new node becomes first
			new_node->prev->next = new_node;// last node next points to new node
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
int circdbllinkedlist_insert_at_end(struct circdbllinkedlist* list, void* data) {
	int result = 0;
	assert(list != NULL);

	if (list->size == 0)
		result = circdbllinkedlist_insert_empty(list, data);
	else {
		struct circdbllinkedlistnode* last = (*(list->headp))->prev;
		struct circdbllinkedlistnode* new_node = malloc(sizeof(*new_node));
		if (new_node == NULL)
			return result;
		else {
			new_node->data = data;
			new_node->next = last->next;	// new node next points to first node
			new_node->prev = last;			// new node prev points to last node
			last->next = new_node;			// last node next points to new node
			new_node->next->prev = new_node;// first prev points to new node
			list->size += 1;
			result = 1;
		}
	}

	return result;
}

/*
 * Inserts after node.
 * Returns 1 if succeeded, 0 otherwise.
 * */
int circdbllinkedlist_insert_after(struct circdbllinkedlist* list, struct circdbllinkedlistnode* node, void* data) {
	int result = 0;
	assert(list != NULL);
	assert(node != NULL);

	if (node == (*(list->headp))->prev)				// is last node?
		result = circdbllinkedlist_insert_at_end(list, data);
	else {
		struct circdbllinkedlistnode* new_node = malloc(sizeof(*new_node));
		if (new_node == NULL)
			return result;
		else {
			new_node->data = data;
			new_node->next = node->next;	// new node next points to node next
			new_node->prev = node;			// new node prev points to node
			node->next = new_node;			// node next points to new node

			if (node->prev == node)			// if node prev points to itself,
				node->prev = new_node;		// then node prev points to new node

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
struct circdbllinkedlistnode* circdbllinkedlist_getnode(struct circdbllinkedlist* list, const void* data) {
	struct circdbllinkedlistnode* node = *(list->headp);
	int i = 0;
	if (node == NULL)
		return NULL;

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
 * Note: Do not free memory from returned node reference. That is a job to be done
 * 		 by the linked list when destroyed.
 * */
struct circdbllinkedlistnode* circdbllinkedlist_getstart(struct circdbllinkedlist* list) {
	return *(list->headp);
}

/*
 * Gets data from a node that matches given data.
 * Returns reference to founded data if succeeded, NULL otherwise.
 * Note: Do not free memory from returned node reference. That is a job to be done
 * 		 by the linked list when destroyed.
 * */
void* circdbllinkedlist_getdata(struct circdbllinkedlist* list, const void* data) {
	void* result = NULL;
	if (circdbllinkedlist_isempty(list))
		return result;
	else {
		struct circdbllinkedlistnode* node = circdbllinkedlist_getnode(list, data);
		if (node != NULL)
			result = node->data;
	}

	return result;
}

/*
 * Removes first item from list.
 * Returns reference to removed node if succeeded, NULL otherwise.
 * */
struct circdbllinkedlistnode* circdbllinkedlist_remove_first(struct circdbllinkedlist* list) {
	struct circdbllinkedlistnode* result = NULL;
	if (circdbllinkedlist_isempty(list))
		return result;
	else {
		struct circdbllinkedlistnode* first = *(list->headp);

		if (list->size == 1) {
			first->next = NULL;
			first->prev = NULL;
			*(list->headp) = NULL;
		}
		else {
			*(list->headp) = first->next;				// first becomes next node
			(*(list->headp))->prev = first->prev; 		// new first prev points to old first prev
			(*(list->headp))->prev->next = first->next; // last next points to first next
			first->next = NULL;							// disconnect old first
			first->prev = NULL;
		}

		list->size -= 1;
		result = first;
	}

	return result;
}


/*
 * Removes item from list.
 * Returns reference to removed node if succeeded, NULL otherwise.
 * */
struct circdbllinkedlistnode* circdbllinkedlist_remove(struct circdbllinkedlist* list, const void* data) {
	struct circdbllinkedlistnode* result = NULL;
	if (circdbllinkedlist_isempty(list))
		return result;
	else {
		struct circdbllinkedlistnode* node = circdbllinkedlist_getnode(list, data);

		if (node != NULL) {
			if ((*(list->headp)) == node) {
				node = circdbllinkedlist_remove_first(list);
			}
			else {
				node->next->prev = node->prev;	// next node prev points to node prev
				node->prev->next = node->next;	// prev node next points to node next

				node->prev = NULL;				// disconnect node
				node->next = NULL;
			}

			list->size -= 1;
			result = node;
		}
	}

	return result;
}

/**
 * Releases all resources from list.
 */
void circdbllinkedlist_destroy(struct circdbllinkedlist* list) {
	struct circdbllinkedlistnode* node = NULL;
	while ((node = circdbllinkedlist_remove_first(list)) != NULL) {
		if (list->freedata)
			if (node->data)
				list->freedata(node->data);

		free(node);
	}

	free(list->headp);
	free(list);
}




