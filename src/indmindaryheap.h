/*
 * indexedmindaryheap.h
 *
 *  Created on: 21/09/2023
 *      Author: Tiago C. Teixeira
 * Description: C Headers for implementation of an indexed min D-ary heap priority queue.
 *
 *
 * Definition
 *
 * 		An Indexed Priority Queue is a data structure that combines the properties of
 * 		both an indexable data structure (like an array or a list) and a priority queue.
 * 		It is used in computer science and algorithms to efficiently manage a collection
 * 		of elements with associated priorities, allowing for quick updates to both
 * 		priorities and values. Indexed Priority Queues are particularly useful in graph
 * 		algorithms, shortest path algorithms (e.g., Dijkstra's algorithm), and other
 * 		scenarios where efficient priority-based operations are required.
 *
 *
 * This implementation supports arbitrary keys with comparable values. To use arbitrary keys
 * (such as strings or objects) first map all your keys to the integer domain [0, N) where N is the
 * number of keys you have and then use the mapping with this indexed priority queue.
 *
 * As convention, I denote 'ki' as the index value in the domain [0, N) associated with a key k,
 * therefore: ki = map[k]
 *
 * Often the keys themselves are integers in rhe range [0..N) so there's no need for
 * mapping. but it's handy to be able to support any type of key (like names).
 *
 *  Hashtable example:
 *
 *  	--------------------
 *  	| key		|	ki |
 *  	|------------------|
 *  	| "Ana"		| 	0  |
 *  	| "John"	|	1  |
 *  	| "Richard	|	2  |
 *  	| "James"	| 	3  |
 *  	--------------------
 *
 * |In a normal priority queue search, delete and update operations can take O(n) time
 * where in a indexed priority queue (indexed binary PQ) this operations are done in
 * O(logn).
 *
 * 		  Time complexity by operation
 *	-----------------------------------------
 * 	|	valueof(ki)   			| O(1)		|
 * 	|	contains(ki) 			| O(1)		|
 * 	|	peekminkeyindex 		| O(1)		|
 * 	|	poolminkeyindex 		| O(logn)	|
 * 	|	peekminvalue 			| O(1)		|
 * 	|	poolminvalue 			| O(logn)	|
 * 	|	insert(ki, value) 		| O(logn)	|
 *	|	update(ki, value) 		| O(logn)	|
 * 	|	decreasekey(ki, value) 	| O(logn)	|
 * 	|	increasekey(ki, value) 	| O(logn)	|
 *	-----------------------------------------
 * 	where ki = key index
 *
 * Structure:
 *
 * 		An Indexed Priority Queue is typically implemented using a binary heap or a
 *    	Fibonacci heap as the underlying data structure.
 *    	It consists of a collection of elements, each associated with a unique index and
 *    	a priority value.
 *    	Elements are organized in a way that allows for efficient extraction of the
 *    	element with the highest (or lowest, depending on the implementation) priority.
 *
 * Pros:
 *
 *    	Efficient Priority-Based Operations:
 *    		Indexed Priority Queues allow for efficient insertion, deletion, and
 *    		priority change operations, typically with logarithmic time complexity.
 *
 *    	Indexed Access:
 *    		You can quickly access elements by their unique index, making it suitable
 *    		for graph algorithms and other scenarios where you need to associate data
 *    		with specific vertices or nodes.
 *
 *   	Used in Various Algorithms:
 *   		It is a fundamental data structure in algorithms like Dijkstra's algorithm,
 *   		Prim's algorithm, and A* search, which are used in graph traversal and
 *   		shortest path problems.
 *
 * Cons:
 *
 *    	Complexity:
*    		Implementing an efficient indexed priority queue can be complex,
*    		especially when using data structures like Fibonacci heaps. Simpler
*    		implementations using binary heaps may have slightly worse time complexity
*    		for some operations.
*
 *    	Space Overhead:
 *    		Indexed Priority Queues may have a higher space overhead compared to
 *    		simpler data structures like arrays or lists, especially if additional
 *    		data (e.g., values) is associated with each element.
 *
 *
 * Sources: This source code is ported and adapted from William Fiset Java implementation.
 * 		    https://github.com/williamfiset/Algorithms/blob/master/src/main/java/com/williamfiset/algorithms/datastructures/priorityqueue/MinIndexedDHeap.java
 *
 * 			Texts and a more simpler c++ implementation can be found at:
 * 			https://www.geeksforgeeks.org/indexed-priority-queue-with-implementation/
 *
 */
#ifndef INDMINDARYHEAP_H_
	#define INDMINDARYHEAP_H_
	#include <stdlib.h>

	typedef int (*idarypq_comparefunc)(const void* a, const void* b);
	typedef void (*idarypq_freedata)(void* data);
	typedef void (*idarypq_printdata)(const void* data);

	struct idarypq {
		size_t D;			// The degree of every node in the heap.
		size_t N;			// Maximum number of elements in the heap.
		size_t sz;			// Current number of elements in the heap.

		idarypq_comparefunc compare;	// function to compare to priority keys
		idarypq_freedata freedata;		// function to release an element from memory
		idarypq_printdata printdata;	// function to prints an element

		int* child;	// Lookup arrays to track the child/parent indexes of each node.
		int* parent;

		// The Position Map (pm) maps Key Indexes (ki) to where the position of that
		// key is represented in the priority queue in the domain [0, sz).
		int* pm;

		// The Inverse Map (im) stores the indexes of the keys in the range
		// [0, sz) which make up the priority queue. It should be noted that
		// 'im' and 'pm' are inverses of each other, so: pm[im[i]] = im[pm[i]] = i
		int* im;

		// The values associated with the keys. It is very important  to note
		// that this array is indexed by the key indexes (aka 'ki').
		// this values store the priority of the heap nodes in the represented tree.
		void** values;
	};

	/*
	 * Initializes a D-ary heap with a maximum capacity of maxSize.
	 */
	struct idarypq* imindarypq_create( size_t degree, size_t maxSize,
											   idarypq_comparefunc comparefunc,
											   idarypq_printdata printdatafunc,
											   idarypq_freedata freedatafunc );

	/*
	 * Returns the heap element value stored at a given key index.
	 */
	void* imindarypq_valueof(struct idarypq* ipq, int ki);

	/*
	 * Checks if the priority heap is empty.
	 */
	int imindarypq_isempty(struct idarypq* ipq);

	/*
	 * Gets the number of elements on the indexed priority queue.
	 */
	size_t imindarypq_getsize(struct idarypq* ipq);

	/*
	 * Checks if an element with a given key index exists in the heap or not.
	 */
	int imindarypq_contains( struct idarypq* ipq , int ki );

	/*
	 * Inserts a new element in the heap at a given key index.
	 * Note: If key index already contains an element in the heap, an error will be throw.
	 */
	void imindarypq_insert( struct idarypq* ipq, int ki, void* value );

	/*
	 * Deletes an element (value) in the heap for a given key index.
	 * Returns the deleted element if succeeded, NULL otherwise.
	 */
	void* imindarypq_delete(struct idarypq* ipq, int ki);

	/*
	 * Returns the priority value (at root) from heap but does not remove it.
	 * The time Complexity of this operation is O(1).
	 */
	void* imindarypq_peek( struct idarypq* ipq );

	/*
	 * Extracts element (with high priority) at top of the heap.
	 */
	void* imindarypq_extractkey( struct idarypq* ipq );

	/*
	 * Returns the next key index to be pooled from the heap.
	 */
	int imindarypq_peekkeyindex( struct idarypq* ipq );

	/*
	 * Removes the high priority element from the heap at a given key index (ki).
	 * Returns the key index of the removed element.
	 */
	int imindarypq_extractkeyindex( struct idarypq* ipq );

	/*
	 * Updates a given value and returns old value.
	 */
	void* imindarypq_update(struct idarypq* ipq, int ki, void* value);

	/*
	 * Strictly decreases the value associated with 'ki' to 'value'
	 * Note: If freedata() is defined it will be executed to release old value resources!
	 */
	void imindarypq_decrease(struct idarypq* ipq, int ki, void* value);

	/*
	 * Strictly increases the value associated with 'ki' to 'value'
	 * Note: If freedata() is defined it will be executed to release old value resources!
	 */
	void imindarypq_increase(struct idarypq* ipq, int ki, void* value);

	/*
	 * Prints the heap indexed priority queue elements.
	 */
	void imindarypq_print( struct idarypq* ipq );

	/*
	 * Releases priority queue instance from memory.
	 */
	void imindarypq_destroy(struct idarypq* ipq);

#endif /* INDMINDARYHEAP_H_ */
