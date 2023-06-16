/*************************************************************************
 * circlinklist.h
 *
 *  Created on: 24/02/2023
 *      Author: Tiago C. Teixeira
 * Description: Implements a generic circular linked list.
 *
 *---------------------------------------------------------
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


#ifndef CIRCLINKEDLIST_H_
	#define CIRCLINKEDLIST_H_

	#include <stdlib.h>

	// Represents a node in list
	struct circlinkedlistnode {
		void* data;
		struct circlinkedlistnode* next;
	};

	// Circular linked list data structure
	struct circlinkedlist {
		int (*isequal)(const void* a, const void* b);
		struct circlinkedlistnode** tailp;	// pointer to last node
		size_t size;	// number of elements in list
	};

	/*
	 * Creates a new linked list.
	 * */
	struct circlinkedlist* circlinkedlist_create();

	/*
	 * Inserts at beginning of list.
	 * Returns 1 if succeeded, 0 otherwise.
	 * */
	int circlinkedlist_insert_at_begin(struct circlinkedlist* list, void* data);

	/*
	 * Inserts at end of list.
	 * Returns 1 if succeeded, 0 otherwise.
	 * */
	int circlinkedlist_insert_at_end(struct circlinkedlist* list, void* data);

	/*
	 * Inserts after node.
	 * Returns 1 if succeeded, 0 otherwise.
	 * */
	int circlinkedlist_insert_after(struct circlinkedlist* list, struct circlinkedlistnode* node, void* data);

	/*
	 * Gets the start node.
	 * Returns reference to start node if succeeded, NULL otherwise.
	 * Note: Do not free memory from returned reference. That is a job to be done
	 * 		 by the linked list when destroyed.
	 * */
	struct circlinkedlistnode* circlinkedlist_getstart(struct circlinkedlist* list);

	/*
	 * Gets data from a node that matches given data.
	 * Returns reference to founded data if succeeded, NULL otherwise.
	 * Note: Do not free memory from returned reference. That is a job to be done
	 * 		 by the linked list when destroyed.
	 * */
	void* circlinkedlist_getdata(struct circlinkedlist* list, const void* data);

	/*
	 * Removes item from list.
	 * Returns reference to removed item if succeeded, NULL otherwise.
	 * */
	struct circlinkedlistnode* circlinkedlist_remove(struct circlinkedlist* list, const void* data);

	/**
	 * Releases all resources from list.
	 */
	void circlinkedlist_destroy(struct circlinkedlist* list);


#endif /* CIRCLINKEDLIST_H_ */


