/*
 * dbllinkedlistdeque.h
 *
 *  Created on: 18/08/2023
 *      Author: Tiago C. Teixeira
 * Description: C headers for a deque data structure using a double linked list.
 *
  * Definition:
 * 		Deque or Double Ended Queue is a generalized version of Queue data structure
 * 		that allows insert and delete at both ends.
 *
 * Operations on Deque:
 * 		Below is a table showing some basic operations along with their time
 * 		complexity, performed on deques.
 *
 --------------------------------------------------------------------------------------
 | Operation	|	Description								  		| Time Complexity |
 |--------------|---------------------------------------------------|-----------------|
 | push_front()	|	Inserts the element at the beginning.     		| O(1)			  |
 | push_back()	|	Adds element at the end.				  		| O(1)			  |
 | pop_front()	|	Removes the first element from the deque. 		| O(1)			  |
 | pop_back()	|	Removes the last element from the deque.  		| O(1)		  	  |
 | front()		|	Gets the front element from the deque.	  		| O(1)			  |
 | back()		|	Gets the last element from the deque.	  		| O(1)			  |
 | empty()		|	Checks whether the deque is empty or not. 		| O(1)			  |
 | size()		|	Determines the number of elements in the deque.	| O(1)			  |
 --------------------------------------------------------------------------------------
 *
 * Applications of Deque:
 *
 * 		Since Deque supports both stack and queue operations, it can be used as both.
 * 		The Deque data structure supports clockwise and anticlockwise rotations in O(1)
 * 		time which can be useful in certain applications. Also, the problems where
 * 		elements need to be removed and or added to both ends can be efficiently solved
 * 		using Deque. For example see the Maximum of all subarrays of size k problem.,
 * 		0-1 BFS, and Find the first circular tour that visits all petrol pumps. See the
 * 		wiki page for another example of the A-Steal job scheduling algorithm where
 * 		Deque is used as deletions operation is required at both ends.
 *
 * Some Practical Applications of Deque:
 *
 *    	Applied as both stack and queue, as it supports both operations.
 *    	Storing a web browser’s history.
 *    	Storing a software application’s list of undo operations.
 *    	Job scheduling algorithm
 *
 *
 * Other Applications:
 *
 *		Deques have several other applications, some of which include:
 *
 *    	Palindrome checking:
 *    		Deques can be used to check if a word or phrase is a
 *    		palindrome. By inserting each character of the word or phrase into a deque,
 *    		it is possible to check if the word or phrase is a palindrome by comparing
 *    		the first and last characters, the second and second-to-last characters,
 *    		and so on.
 *
 *    	Graph traversal:
 *    		Deques can be used to implement Breadth-First Search (BFS) on a graph.
 *    		BFS uses a queue to keep track of the vertices to be visited next, and
 *    		a deque can be used as an alternative to a queue in this case.
 *
 *    Task scheduler:
 *    		Deques can be used to implement a task scheduler that keeps track of
 *    		tasks to be executed. Tasks can be added to the back of the deque, and
 *    		the scheduler can remove tasks from the front of the deque and execute them.
 *
 *    Multi-level undo/redo functionality:
 *    		Deques can be used to implement undo and redo functionality in applications.
 *    		Each time a user performs an action, the current state of the application is
 *    		pushed onto the deque. When the user undoes an action, the front of the
 *    		deque is popped, and the previous state is restored. When the user redoes
 *    		an action, the next state is popped from the deque.
 *
 *    In computer science, deque can be used in many algorithms like LRU Cache,
 *    Round Robin Scheduling, Expression Evaluation.
 *
 *
 * Implementation:
 * 		A Deque can be implemented either using a doubly-linked list or a
 * 		circular array. In both implementations, we can implement all operations
 * 		in O(1) time.
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
 * Sources: https://www.geeksforgeeks.org/deque-set-1-introduction-applications/
 * 			https://www.geeksforgeeks.org/implementation-deque-using-doubly-linked-list/?ref=ml_lbp
 */

#ifndef DBLLINKEDLISTDEQUE_H_
	#define DBLLINKEDLISTDEQUE_H_

	#include "dbllinkedlist.h"

	struct dbllinkedlistdeque {
		struct dbllinkedlist* list;
	};

	/*
	 * Create deque instance.
	 */
	struct dbllinkedlistdeque* dbllinkedlistdeque_create( dbllinkedlist_printdata printdatafunc,
			dbllinkedlist_freedata freedatafunc );

	/*
	 * Function to check if deque is empty or not
	 */
	int dbllinkedlistdeque_empty(struct dbllinkedlistdeque* q);

	/*
	 * Function to remove all elements from list
	 */
	void dbllinkedlistdeque_erase(struct dbllinkedlistdeque* q);

	/*
	 * Function to get number of elements of deque
	 */
	size_t dbllinkedlistdeque_size(struct dbllinkedlistdeque* q);

	/*
	 * Function to find the front element of the deque
	 */
	void* dbllinkedlistdeque_front(struct dbllinkedlistdeque* q);

	/*
	 * Function to find the last element of the deque
	 */
	void* dbllinkedlistdeque_back(struct dbllinkedlistdeque* q);

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
	void dbllinkedlistdeque_push_back(struct dbllinkedlistdeque* q, void* x);

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
	void dbllinkedlistdeque_push_front(struct dbllinkedlistdeque* q, void* x);

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
	void* dbllinkedlistdeque_pop_front(struct dbllinkedlistdeque* q);

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
	void* dbllinkedlistdeque_pop_back(struct dbllinkedlistdeque* q);

	/*
	 * Release array deque instance from memory.
	 * */
	void dbllinkedlistdeque_destroy(struct dbllinkedlistdeque* q);

#endif /* DBLLINKEDLISTDEQUE_H_ */
