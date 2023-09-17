/*
 * dbllinklist.c
 *
 *  Created on: 06/03/2023
 *      Author: Tiago C. Teixeira
 *
 *  Description: C program for generic double linked list.
 *
 *---------------------------------------------------------
 *
 *  Advantages of DLL over the singly linked list:
 *
 *    A DLL can be traversed in both forward and backward directions.
 *    The delete operation in DLL is more efficient if a pointer to the node to be
 *    deleted is given.
 *    We can quickly insert a new node before a given node.
 *    In a singly linked list, to delete a node, a pointer to the previous node is needed.
 *    To get this previous node, sometimes the list is traversed. In DLL, we can
 *    get the previous node using the previous pointer.
 *
 * Disadvantages of DLL over the singly linked list:
 *
 *    Every node of DLL Requires extra space for a previous pointer. It is possible to
 *    implement DLL with a single pointer though (See this and this).
 *    All operations require an extra pointer previous to be maintained. For example,
 *    in insertion, we need to modify previous
 *    pointers together with the next pointers. For example in the following functions
 *    for insertions at different positions,
 *    we need 1 or 2 extra steps to set the previous pointer.
 *
 * Applications of DLL:
 *
 *    It is used by web browsers for backward and forward navigation of web pages
 *    LRU ( Least Recently Used ) / MRU ( Most Recently Used ) Cache are constructed
 *    using Doubly Linked Lists.
 *    Used by various applications to maintain undo and redo functionalities.
 *    In Operating Systems, a doubly linked list is maintained by thread scheduler to
 *    keep track of processes that are being executed at that time.
 *
 *
 * Source: https://www.geeksforgeeks.org/introduction-and-insertion-in-a-doubly-linked-list/?ref=lbp
 *
 ******************************************************************************/


#include <stdlib.h>
#include <stdio.h>
#include "dbllinkedlist.h"
#include <assert.h>

/*
 * Creates a new empty double linked list.
 * */
struct dbllinkedlist* dbllinkedlist_create( dbllinkedlist_isequal isequalfunc,
											dbllinkedlist_printdata printdatafunc,
											dbllinkedlist_freedata freedatafunc )
{
	struct dbllinkedlist* result = NULL;
	result = malloc(sizeof(*result));

	if (result != NULL) {
		struct dbllinkedlistnode** hp = malloc(sizeof *hp);
		struct dbllinkedlistnode** tp = malloc(sizeof *tp);
		if (hp != NULL) {
			*hp = NULL;
			result->headp = hp;
		}
		else {
			free(result);
			result = NULL;
		}
		if (tp != NULL) {
			*tp = NULL;
			result->tailp = tp;
		}
		else {
			free(hp);
			free(result);
			result = NULL;
		}

		result->printdata = printdatafunc;
		result->freedata = freedatafunc;
		result->isequal = isequalfunc;
		result->size = 0;
	}

	return result;
}

/*
 * Checks if list is empty.
 * Returns 1 if is empty, 0 otherwise.
 * */
int dbllinkedlist_isempty(const struct dbllinkedlist* list) {
	return (list->size) == 0;
}

/*
 * Inserts at beginning of list.
 * Returns 1 if succeeded, 0 otherwise.
 * */
int dbllinkedlist_insert_empty(struct dbllinkedlist* list, void* data) {
	int result = 0;
	assert(list != NULL);

	if (list->size == 0) {
		struct dbllinkedlistnode* new_node = malloc(sizeof(*new_node));
		if (new_node == NULL) {
			return result;
		}
		else {
			new_node->data = data;
			new_node->next = NULL;
			new_node->prev = NULL;
			(*(list->headp)) = new_node;
			(*(list->tailp)) = new_node;
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
int dbllinkedlist_insert_at_begin(struct dbllinkedlist* list, void* data) {
	int result = 0;
	assert(list != NULL);

	if (dbllinkedlist_isempty(list)) {
		result = dbllinkedlist_insert_empty(list, data);
	}
	else {
		struct dbllinkedlistnode* new_node = malloc(sizeof(*new_node));
		if (new_node == NULL) {
			return result;
		}
		else {
			new_node->data = data;
			new_node->next = (*(list->headp));	// next points to current first node
			new_node->prev = NULL;				// previous node undefined
			(*(list->headp))->prev = new_node;	// current first node previous points to new node
			(*(list->headp)) = new_node;		// new node becomes first node
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
int dbllinkedlist_insert_at_end(struct dbllinkedlist* list, void* data) {
	int result = 0;
	assert(list != NULL);

	if (dbllinkedlist_isempty(list)) {
		result = dbllinkedlist_insert_empty(list, data);
	}
	else {
		struct dbllinkedlistnode* new_node = malloc(sizeof(*new_node));
		if (new_node == NULL) {
			return result;
		}
		else {
			new_node->data = data;
			new_node->next = NULL;				// new node next is undefined
			new_node->prev = *(list->tailp);	// new node previous points to last node
			(*(list->tailp))->next = new_node;	// last node next points to new node
			(*(list->tailp)) = new_node;		// new node becomes last node
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
int dbllinkedlist_insert_after(struct dbllinkedlist* list, struct dbllinkedlistnode* node, void* data) {
	int result = 0;
	assert(node != NULL);

	struct dbllinkedlistnode* last = (*(list->tailp));

	if (node == last)
		result = dbllinkedlist_insert_at_end(list, data);
	else {
		struct dbllinkedlistnode* new_node = malloc(sizeof(*new_node));
		if (new_node == NULL) {
			return result;
		}
		else {
			new_node->data = data;
			new_node->next = node->next;	// new node points to node next node
			new_node->prev = node;			// new node previous points to node
			node->next = new_node;			// node next points to new node
			list->size += 1;
			result = 1;
		}
	}

	return result;
}

/*
 * Get first node of list.
 * Returns first node if exists, NULL otherwise.
 * */
struct dbllinkedlistnode* dbllinkedlist_getfirst(struct dbllinkedlist* list) {
	struct dbllinkedlistnode* result = *(list->headp);
	return result;
}

/*
 * Get last node of list.
 * Returns last node if exists, NULL otherwise.
 * */
struct dbllinkedlistnode* dbllinkedlist_getlast(struct dbllinkedlist* list) {
	struct dbllinkedlistnode* result = *(list->tailp);
	return result;
}

/*
 * Gets the node that matches given data.
 * Returns reference to founded node if succeeded, NULL otherwise.
 * Note: Do not free memory from returned node reference. That is a job to be done
 * 		 by the list when destroyed.
 * */
struct dbllinkedlistnode* dbllinkedlist_getnode(struct dbllinkedlist* list, const void* data) {
	struct dbllinkedlistnode* node = *(list->headp);
	while ((node != NULL) && (!list->isequal(node->data, data))) {
		node = node->next;
	}

	return node;
}

/*
 * Gets data from node that matches given data.
 * Returns reference to founded data if succeeded, NULL otherwise.
 * Note: Do not free memory from returned node reference. That is a job to be done
 * 		 by the linked list when destroyed.
 * */
void* dbllinkedlist_getdata(struct dbllinkedlist* list, const void* data) {
	void* result = NULL;
	struct dbllinkedlistnode* node = dbllinkedlist_getnode(list, data);

	// found?
	if (node != NULL) {
		result = node->data;
	}

	return result;
}

/*
 * Gets data from a node at given position (zero based).
 * Returns reference to founded data if succeeded, NULL otherwise.
 * */
void* dbllinkedlist_getdata_at(struct dbllinkedlist* list, uint position) {
	struct dbllinkedlistnode* node = dbllinkedlist_getfirst(list);

	if (list->size > position) {
		for (int pos = 0; pos < position; ++pos)
			node = node->next;

		return node->data;
	}

	return NULL;
}

/*
 * Removes first node.
 * Returns removed node if succeeded, NULL otherwise.
 * */
struct dbllinkedlistnode* dbllinkedlist_remove_first(struct dbllinkedlist* list) {
	struct dbllinkedlistnode* result = NULL;

	if (!dbllinkedlist_isempty(list)) {
		struct dbllinkedlistnode* first = (*(list->headp));
		struct dbllinkedlistnode* last = (*(list->tailp));

		if (first == last) {
			(*(list->headp)) = NULL;	// make empty list
			(*(list->tailp)) = NULL;
		}
		else {
			(*(list->headp)) = first->next;	// head of list points to first next node
			(*(list->headp))->prev = NULL;	// head of list previous points to NULL
			first->next = NULL;				// old first next points to NULL
		}

		result = first;
		list->size -= 1;
	}

	return result;
}

/*
 * Removes last node.
 * Returns removed node if succeeded, NULL otherwise.
 * */
struct dbllinkedlistnode* dbllinkedlist_remove_last(struct dbllinkedlist* list) {
	struct dbllinkedlistnode* result = NULL;

	if (!dbllinkedlist_isempty(list)) {
		struct dbllinkedlistnode* first = (*(list->headp));
		struct dbllinkedlistnode* last = (*(list->tailp));

		if (first == last) {
			(*(list->headp)) = NULL;	// make empty list
			(*(list->tailp)) = NULL;
		}
		else {
			(*(list->tailp)) = last->prev;	// tail of list points to last previous node
			(*(list->tailp))->next = NULL;	// new tail node next points to NULL
			last->prev = NULL;				// old last previous points to NULL
		}

		result = last;
		list->size -= 1;
	}

	return result;
}

/*
 * Removes node that match data from list.
 * Returns reference to removed node if succeeded, NULL otherwise.
 * Note: Node to remove will be disconnected from list but not released from memory.
 * 		 You must do it yourself later.
 * */
struct dbllinkedlistnode* dbllinkedlist_remove(struct dbllinkedlist* list, const void* data) {
	struct dbllinkedlistnode* result = NULL;
	if (dbllinkedlist_isempty(list))
		return result;
	else {
		struct dbllinkedlistnode* node = dbllinkedlist_getnode(list, data);

		if (node != NULL) {
			if (node == (*(list->headp)))
				result = dbllinkedlist_remove_first(list);
			else if (node == (*(list->tailp)))
				result = dbllinkedlist_remove_last(list);
			else {
				node->next->prev = node->prev;	// disconnect from list
				node->prev->next = node->next;
				node->next = NULL;
				node->prev = NULL;
				list->size -= 1;
				result = node;
			}
		}
	}

	return result;
}

/*
 * Prints list data from start to end
 */
void dbllinkedlist_print(struct dbllinkedlist* list)
{
	if (dbllinkedlist_isempty(list))
		printf("The list is empty!\n");
	else
	{
		struct dbllinkedlistnode* node = dbllinkedlist_getfirst(list);
		while (node != NULL)
		{
			if (node->data)
				list->printdata(node->data);
			else
				printf("NULL");

			node = node->next;
			if (node)
				printf("<-->");
		}
	}
}

/*
 * Removes all elements from list.
 */
void dbllinkedlist_erase(struct dbllinkedlist* list)
{
	struct dbllinkedlistnode* node = NULL;
	while (!dbllinkedlist_isempty(list))
	{
		node = dbllinkedlist_remove_first(list);
		if (node)
		{
			if (node->data)
				if (list->freedata != NULL)
					list->freedata(node->data);

			free(node);
		}
	}
}

/**
 * Releases all resources from list.
 */
void dbllinkedlist_destroy(struct dbllinkedlist* list) {
	struct dbllinkedlistnode* node = NULL;

	while ((node = dbllinkedlist_remove_first(list)) != NULL) {
		if (list->freedata != NULL)
			if (node->data != NULL)
				list->freedata(node->data);

		free(node);
	}

	free(list->headp);
	free(list->tailp);
	free(list);
}


