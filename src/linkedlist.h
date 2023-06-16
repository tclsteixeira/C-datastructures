/*************************************************************************
 * linklist.h
 *
 *  Created on: 24/02/2023
 *      Author: Tiago C. Teixeira
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

#ifndef LINKEDLIST_H_

	#define LINKEDLIST_H_

	// Represents a node in list
	struct linkedlistnode {
		void* data;
		struct linkedlistnode* next;
	};

	// Linked list data structure
	struct linkedlist {
		int (*isequalfunc)(const void* a, const void* b);	// function to check if two elements are equal
		struct linkedlistnode** headp;			// pointer to first node
		struct linkedlistnode** tailp;			// pointer to last node
		size_t size;							// number of elements in list
	};

	/*
	 * Creates a new linked list.
	 * */
	struct linkedlist* linkedlist_create();

	/*
	 * Checks if list is empty.
	 * Returns 1 if is empty, 0 otherwise.
	 * */
	int linkedlist_isempty(const struct linkedlist* list);

	/*
	 * Adds a new element at begin of linked list.
	 * Returns 1 if succeeded, 0 otherwise.
	 * */
	int linkedlist_push(struct linkedlist* list, void* new_data);

	/*
	 * Adds a new element at end of linked list.
	 * Returns 1 if succeeded, 0 otherwise.
	 * */
	int linkedlist_append(struct linkedlist* list, void* new_data);

	/*
	 * Gets the first node.
	 * */
	struct linkedlistnode* linkedlist_getfirst(const struct linkedlist* list);

	/*
	 * Gets the last node.
	 * */
	struct linkedlistnode* linkedlist_getlast(const struct linkedlist* list);

	/*
	 * Gets data from a node at given position (zero based) in list.
	 * Returns reference to founded data if succeeded, NULL otherwise.
	 * */
	void* linkedlist_getdata_at(const struct linkedlist* list, uint position);


	/*
	 * Gets data from a node that matches given value.
	 * Returns reference to founded data if succeeded, NULL otherwise.
	 * */
	void* linkedlist_getdata(const struct linkedlist* list, const void* data);

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
	void linkedlist_reverse(struct linkedlist* l);

	/*
	 * Removes the first node from list.
	 * Returns the remove node if succeeded, NULL otherwise.
	 * */
	struct linkedlistnode* linkedlist_remove_first(struct linkedlist* list);

	/*
	 * Removes the node from list that references given data.
	 * Returns the remove node if succeeded, NULL otherwise.
	 * */
	struct linkedlistnode* linkedlist_remove(struct linkedlist* list, const void* data);

	/*
	 * Releases the entire list..
	 * */
	void linkedlist_destroy(struct linkedlist* list);

#endif /* LINKEDLIST_H_ */

