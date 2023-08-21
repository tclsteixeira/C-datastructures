/******************************************************************************
 * dbllinklist.h
 *
 *  Created on: 05/03/2023
 *      Author: Tiago C. Teixeira
 * Description: C headers for a generic double linked list data structure.
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

#ifndef DBLLINKEDLIST_H_
	#define DBLLINKEDLIST_H_

	typedef void (*dbllinkedlist_freedata)(void* data);
	typedef void (*dbllinkedlist_printdata)(void* data);

	// Represents a node in a double linked list
	struct dbllinkedlistnode {
		void* data;
		struct dbllinkedlistnode* next;
		struct dbllinkedlistnode* prev;
	};

	// Double linked list data structure
	struct dbllinkedlist {
		dbllinkedlist_printdata printdata;
		dbllinkedlist_freedata freedata;
		int (*isequal)(const void* a, const void* b);
		struct dbllinkedlistnode** headp;	// pointer to first node
		struct dbllinkedlistnode** tailp;	// pointer to last node
		size_t size;	// number of elements in list
	};

	/*
	 * Creates a new double linked list.
	 * */
	struct dbllinkedlist* dbllinkedlist_create();

	/*
	 * Inserts at beginning of list.
	 * Returns 1 if succeeded, 0 otherwise.
	 * */
	int dbllinkedlist_insert_at_begin(struct dbllinkedlist* list, void* data);

	/*
	 * Inserts at end of list.
	 * Returns 1 if succeeded, 0 otherwise.
	 * */
	int dbllinkedlist_insert_at_end(struct dbllinkedlist* list, void* data);

	/*
	 * Inserts after node.
	 * Returns 1 if succeeded, 0 otherwise.
	 * */
	int dbllinkedlist_insert_after(struct dbllinkedlist* list, struct dbllinkedlistnode* node, void* data);

	/*
	 * Get first node of list.
	 * Returns first node if exists, NULL otherwise.
	 * */
	struct dbllinkedlistnode* dbllinkedlist_getfirst(struct dbllinkedlist* list);

	/*
	 * Get last node of list.
	 * Returns last node if exists, NULL otherwise.
	 * */
	struct dbllinkedlistnode* dbllinkedlist_getlast(struct dbllinkedlist* list);

	/*
	 * Gets data from a node that matches given data.
	 * Returns reference to founded data if succeeded, NULL otherwise.
	 * */
	void* dbllinkedlist_getdata(struct dbllinkedlist* list, const void* data);

	/*
	 * Gets data from a node at given position (zero based).
	 * Returns reference to founded data if succeeded, NULL otherwise.
	 * */
	void* dbllinkedlist_getdata_at(struct dbllinkedlist* list, uint position);

	/*
	 * Removes first node.
	 * Returns removed node if succeeded, NULL otherwise.
	 * */
	struct dbllinkedlistnode* dbllinkedlist_remove_first(struct dbllinkedlist* list);

	/*
	 * Removes last node.
	 * Returns removed node if succeeded, NULL otherwise.
	 * */
	struct dbllinkedlistnode* dbllinkedlist_remove_last(struct dbllinkedlist* list);

	/*
	 * Removes item from list.
	 * Returns reference to removed node if succeeded, NULL otherwise.
	 * */
	struct dbllinkedlistnode* dbllinkedlist_remove(struct dbllinkedlist* list, const void* data);

	/*
	 * Removes all elements from list.
	 */
	void dbllinkedlist_erase(struct dbllinkedlist* list);

	/**
	 * Releases all resources from list.
	 */
	void dbllinkedlist_destroy(struct dbllinkedlist* list);


#endif /* DBLLINKEDLIST_H_ */


