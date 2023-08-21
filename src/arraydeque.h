/*
 * arraydeque.h
 *
 *  Created on: 15/08/2023
 *      Author: Tiago C. Teixeira
 * Description: Headers for the implementation of a deque data structure using a
 * 				dynamic circular array.
 *
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
 *
 * Source: https://www.geeksforgeeks.org/deque-set-1-introduction-applications/
 *
 */

#ifndef ARRAYDEQUE_H_
	#define ARRAYDEQUE_H_

	#define ARRAYDEQUE_MIN_CAPACITY 16
	#define ARRAYDEQUE_DEF_CAPACITY 16

	typedef void (*arraydeque_freedata)(void* data);
	typedef void (*arraydeque_printdata)(void* data);

	struct arraydeque {
		size_t capacity, size;
		int frontindex, backindex;
		arraydeque_freedata freedata;
		arraydeque_printdata printdata;
		void** arr;	// variable sized array
	};

	/*
	 * Create deque instance.
	 */
	struct arraydeque* arraydeque_create_capacity( size_t capacity,
										  arraydeque_printdata printdatafunc,
										  arraydeque_freedata freedatafunc );

	/*
	 * Create deque instance with default capacity.
	 */
	struct arraydeque* arraydeque_create( arraydeque_printdata printdatafunc,
										  arraydeque_freedata freedatafunc );

	/*
	 * Function to check if deque is empty or not
	 */
	int arraydeque_empty(struct arraydeque* arrdeque);

	/*
	 * Function to check if deque is full or not
	 */
	int arraydeque_full(struct arraydeque* arrdeque);

	/*
	 * Function to find the front element of the deque
	 */
	void* arraydeque_front(struct arraydeque* arrdeque);

	/*
	 * Function to find the last element of the deque
	 */
	void* arraydeque_back(struct arraydeque* arrdeque);

	/*
	 * Function to insert the element to the back of the deque
	 *
	 * - If the deque is full, then double the size of the current array and copy the elements
	 * 		of the previous array into the new array.
	 * - If deque is empty(), then assign frontIndex = backIndex = 0 and then assign X to
	 * 		both arr[frontIndex] and arr[backIndex] and then increment sizeVar by one.
	 *   Else, update backIndex as backIndex = (backIndex+1) %capacityVar and then assign
	 *   	X to arr[backIndex] and increment sizeVar by one.
	 */
	void arraydeque_push_back(struct arraydeque* arrdeque, void* x);

	/*
	 * Function to insert the element
	 * to the front of the deque
	 *
	 * - If the deque is full, then double the size of the current array and copy the
	 * 		elements of the previous array into the new array.
	 * - If deque is empty(), then assign frontIndex = backIndex = 0 and then assign X
	 * 		to both arr[frontIndex] and arr[backIndex] and then increment sizeVar by one.
	 *   Else, update frontIndex as frontIndex = (frontIndex-1 + capacityVar)%capacityVar
	 *   	and then assign X to arr[frontIndex] and increment sizeVar by one.
	 */
	void arraydeque_push_front(struct arraydeque* arrdeque, void* x);

	/*
	 * Function to delete the element from the front of the deque.
	 * Returns removed element if succeeded.
	 *
	 * - If the deque is empty,
	 * 		print “Underflow”.
	 *   Else if sizeVar is equal to 1 then
	 *   	assign -1 to frontIndex and backIndex both and then decrement sizeVar by one.
	 *   Else,
	 *   	Update frontIndex as frontIndex = (frontIndex+1)%capacityVar and
	 *   	decrement sizeVar by one.
	 */
	void* arraydeque_pop_front(struct arraydeque* arrdeque);

	/*
	 * Function to remove the element from the back of the deque.
	 * Returns removed element if succeeded.
	 *
	 * - If the deque is empty,
	 * 		print “Underflow”.
	 *   Else if sizeVar is equal to 1 then
	 *   	assign -1 to frontIndex and backIndex both and then decrement sizeVar by one.
	 *   Else,
	 *   	Update backIndex as backIndex = (backndex-1 + capacityVar) % capacityVar and
	 *   	decrement sizeVar by one.
	 */
	void* arraydeque_pop_back(struct arraydeque* arrdeque);

	/*
	 * Release array deque instance from memory.
	 * */
	void arraydeque_destroy(struct arraydeque* arrdeque);

#endif /* ARRAYDEQUE_H_ */
