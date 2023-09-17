/****************************************************************************
 * circdbllinklist.h
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
 *****************************************************************************/


#ifndef CIRCDBLLINKEDLIST_H_
	#define CIRCDBLLINKEDLIST_H_

	#include <stdlib.h>

	// Represents a node in a double linked list
	struct circdbllinkedlistnode {
		void* data;
		struct circdbllinkedlistnode* next;
		struct circdbllinkedlistnode* prev;
	};

	typedef int (*circdbllinkedlist_isequal)(const void* a, const void* b);
	typedef void (*circdbllinkedlist_printdata)(const void* data);
	typedef void (*circdbllinkedlist_freedata)(void* data);

	// Double linked list data structure
	struct circdbllinkedlist {
		circdbllinkedlist_isequal isequal;
		circdbllinkedlist_printdata printdata;
		circdbllinkedlist_freedata freedata;
		struct circdbllinkedlistnode** headp;	// pointer to first node
		size_t size;	// number of elements in list
	};

	/*
	 * Creates a new circular double linked list.
	 * */
	struct circdbllinkedlist* circdbllinkedlist_create( circdbllinkedlist_isequal isequal,
														circdbllinkedlist_printdata printdata,
														circdbllinkedlist_freedata freedata );

	/*
	 * Inserts at beginning of list.
	 * Returns 1 if succeeded, 0 otherwise.
	 * */
	int circdbllinkedlist_insert_at_begin(struct circdbllinkedlist* list, void* data);

	/*
	 * Inserts at end of list.
	 * Returns 1 if succeeded, 0 otherwise.
	 * */
	int circdbllinkedlist_insert_at_end(struct circdbllinkedlist* list, void* data);

	/*
	 * Inserts after node.
	 * Returns 1 if succeeded, 0 otherwise.
	 * */
	int circdbllinkedlist_insert_after(struct circdbllinkedlist* list, struct circdbllinkedlistnode* node, void* data);

	/*
	 * Gets the start node.
	 * Returns reference to start node if succeeded, NULL otherwise.
	 * Note: Do not free memory from returned node reference. That is a job to be done
	 * 		 by the linked list when destroyed.
	 * */
	struct circdbllinkedlistnode* circdbllinkedlist_getstart(struct circdbllinkedlist* list);

	/*
	 * Gets data from a node that matches given data.
	 * Returns reference to founded data if succeeded, NULL otherwise.
	 * Note: Do not free memory from returned node reference. That is a job to be done
	 * 		 by the linked list when destroyed.
	 * */
	void* circdbllinkedlist_getdata(struct circdbllinkedlist* list, const void* data);

	/*
	 * Removes first item from list.
	 * Returns reference to removed node if succeeded, NULL otherwise.
	 * */
	struct circdbllinkedlistnode* circdbllinkedlist_remove_first(struct circdbllinkedlist* list);

	/*
	 * Removes item from list.
	 * Returns reference to removed node if succeeded, NULL otherwise.
	 * */
	struct circdbllinkedlistnode* circdbllinkedlist_remove(struct circdbllinkedlist* list, const void* data);

	/**
	 * Releases all resources from list.
	 */
	void circdbllinkedlist_destroy(struct circdbllinkedlist* list);



#endif /* CIRCDBLLINKEDLIST_H_ */





