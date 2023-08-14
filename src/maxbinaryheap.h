/*
 * maxheap.h
 *
 *  Created on: 09/07/2023
 *      Author: Tiago C. Teixeira
 * Description: C implementation of a max binary heap data structure.
 *
 * Definition:
 *
 * 	A Binary Heap is a complete Binary Tree which is used to store data efficiently to get the
 * 	max or min element based on its structure.
 *
 *---------------------------------------------------
 * A binary heap is typically represented as array.
 *---------------------------------------------------
 *
 * The root element will be at Arr[0].
 * Below table shows indexes of other nodes for the ith node, i.e., Arr[i]:
 * 	Arr[(i-1)/2]	Returns the parent node
 * 	Arr[(2*i)+1]	Returns the left child node
 * 	Arr[(2*i)+2]	Returns the right child node
 *
 * The traversal method use to achieve Array representation is Level Order
 *
 * Complete binary tree definition:
 *
 * 	A complete binary tree is a special type of binary tree where all the levels of the tree
 * 	are filled completely except the lowest level nodes which are filled from as left as
 * 	possible.
 *
 * Properties of Complete Binary Tree:
 *
 *     -A complete binary tree is said to be a proper binary tree where all leaves have the same
 *    depth.
 *    - In a complete binary tree number of nodes at depth d is 2^d.
 *    - In a  complete binary tree with n nodes height of the tree is log(n+1).
 *    - All the levels except the last level are completely full.
 *
 * If the height of the given binary tree is h then the maximum number of nodes in that tree
 * is n = 2^(h+1) - 1
 *
 * Binary Heap satisfies the Ordering Property.
 * The Ordering can be of two types:
 * 		1. Min Heap Property: The value of each node is greater than or equal to the value of its
 * 		   parent, with the minimum value at the root.
 *
 * 		Examples:
 *
 *   	       1
 *    	     /   \
 *     	   3       6
 *        / \     /
 *       5   9   8
 *
 *
 * 		2. Max Heap Property: The value of each node is less than or
 * 		   equal to the value of its parent, with the maximum value at the root.
 *
 * 		Examples:
 *
 *   	       9
 *    	     /   \
 *     	   8       6
 *        / \     /
 *       5   2   1
 *
 *
 * Operations of Heap:
 *
 *    - Heapify:   a process of creating a heap from an array.
 *
 *    - Insertion: process to insert an element in existing heap time complexity O(log N).
 *
 *    - Deletion:  deleting the top element of the heap or the highest priority element, and
 *    		 	   then organizing the heap and returning the element with time complexity O(log N).
 *
 *    - Peek:      to check or find the most prior element in the heap, (max or min element for max
 *    		       and min heap).
 *
 * Application of Heap Data Structure:
 *
 *    Priority queues:
 *    				The heap data structure is commonly used to implement priority queues,
 *    				where elements are stored in a heap and ordered based on their priority.
 *    				This allows constant-time access to the highest-priority element, making
 *    				it an efficient data structure for managing tasks or events that require
 *    				prioritization.
 *    Heapsort algorithm:
 *    				The heap data structure is the basis for the heapsort algorithm,
 *    				which is an efficient sorting algorithm with a worst-case time complexity
 *    				of O(n log n). The heapsort algorithm is used in various applications,
 *    				including database indexing and numerical analysis.
 *    Memory management:
 *    				The heap data structure is used in memory management systems to
*    				allocate and deallocate memory dynamically. The heap is used to
*    				store the memory blocks, and the heap data structure is used to
*    				efficiently manage the memory blocks and allocate them to programs as
*    				needed.
 *    Graph algorithms:
 *    				The heap data structure is used in various graph algorithms, including
 *    				Dijkstra’s algorithm, Prim’s algorithm, and Kruskal’s algorithm. These
 *    				algorithms require efficient priority queue implementation, which can
 *    				be achieved using the heap data structure.
 *    Job scheduling:
 *    				The heap data structure is used in job scheduling algorithms, where tasks
 *    				are scheduled based on their priority or deadline. The heap data structure
 *    				allows efficient access to the highest-priority task, making it a useful
 *    				data structure for job scheduling applications.
 *
 *
 * Real-Time Application of Heap:
 *
 *    Patient treatment: In a hospital, an emergency patient, or the patient with more injury
 *    					 is treated first. Here the priority is the degree of injury.
 *
 *    Systems concerned with security use heap sort, like the Linux kernel.
 *
 *
 * Advantages of Heap Data Structure:
 *
 *    Efficient insertion and deletion: The heap data structure allows efficient insertion
 *    		and deletion of elements. When a new element is added to the heap, it is placed
 *    		at the bottom of the heap and moved up to its correct position using the heapify
 *    		operation. Similarly, when an element is removed from the heap, it is replaced by
 *    		the bottom element, and the heap is restructured using the heapify operation.
 *
 *    Efficient priority queue: The heap data structure is commonly used to implement a
 *    		priority queue, where the highest priority element is always at the top of the
 *    		heap. The heap allows constant-time access to the highest priority element,
 *    		making it an efficient data structure for implementing priority queues.
 *
 *    Guaranteed access to the maximum or minimum element: In a max-heap, the top element is
 *    		always the maximum element, and in a min-heap, the top element is always the
 *    		minimum element. This provides guaranteed access to the maximum or minimum
 *    		element in the heap, making it useful in algorithms that require access to the
 *    		extreme values.
 *
 *    Space efficiency: The heap data structure requires less memory compared to other data
 *    		structures, such as linked lists or arrays, as it stores elements in a complete
 *    		binary tree structure.
 *
 *    Heap-sort algorithm: The heap data structure forms the basis for the heap-sort algorithm,
 *    		which is an efficient sorting algorithm that has a worst-case time complexity of
 *    		O(n log n).
 *
 * Disadvantages of Heap Data Structure:
 *
 *    Lack of flexibility: The heap data structure is not very flexible, as it is designed to
 *    		maintain a specific order of elements. This means that it may not be suitable for
 *    		some applications that require more flexible data structures.
 *
 *    Not ideal for searching: While the heap data structure allows efficient access to the
 *    		top element, it is not ideal for searching for a specific element in the heap.
 *    		Searching for an element in a heap requires traversing the entire tree, which has
 *    		a time complexity of O(n).
 *
 *    Not a stable data structure: The heap data structure is not a stable data structure,
 *    		which means that the relative order of equal elements may not be preserved when
 *    		the heap is constructed or modified.
 *
 *    Memory management: The heap data structure requires dynamic memory allocation, which
 *    		can be a challenge in some systems with limited memory. In addition, managing
 *    		the memory allocated to the heap can be complex and error-prone.
 *
 *    Complexity: While the heap data structure allows efficient insertion, deletion, and
 *    		priority queue implementation, it has a worst-case time complexity of O(n log n),
 *    		which may not be optimal for some applications that require faster algorithms.
 *
 *
 * Conclusion:
 *
 * 	In general, heaps are used in situations where elements need to be efficiently retrieved
 * 	and managed based on their priority. Heaps are efficient because they can retrieve, insert,
 * 	and delete elements in O(log n) time, which is faster than the O(n) time required by a
 * 	linear search. Additionally, heaps are easy to implement and use in a variety of algorithms
 * 	and data structures.
 *
 */

#ifndef MAXBINARYHEAP_H_
	#define MAXBINARYHEAP_H_

	/*
	 * Function to create a min heap.
	 */
	struct heap* maxbinaryheap_createHeap(int capacity, void** datalist,
										int listsize,
										void* minlimit, void* maxlimit,
//										heap_calcdatasize calcdatasizefunc,
										heap_cmp comparefunc,
//										heap_minlimitkey minlimitfunc,
//										heap_maxlimitkey maxlimitfunc,
										heap_printdata printdatafunc,
										heap_freedata freedatafunc);

	 /*
	  * Inserts a new value in the heap.
	  * Inserting a new key takes O(log N) time. We add a new key at the end of the tree.
	  * If the new key is smaller than its parent, then we don’t need to do anything. Otherwise,
	  * we need to traverse up to fix the violated heap property.
	  */
	 void maxbinaryheap_insert(struct heap* h, void* data);

	 /*
	  * Method to remove priority element (or root) from heap.
	  * The time Complexity of this Operation is O(log N) as this operation needs to maintain
	  * the heap property (by calling heapify()) after removing the root.
	  */
	 void* maxbinaryheap_extract(struct heap* h);

	 /*
	  * Returns the priority value (at root) from heap but does not remove it.
	  * The time Complexity of this operation is O(1).
	  */
	 void* maxbinaryheap_peek(struct heap* h);

	 /*
	   * Increases value of key at index 'i' to new_val. It is assumed that
	   * new_val is bigger than h->arr[i].
	   * Increases the value of the key. The time complexity of this operation is O(log N).
	   * If the increased key value of a node is smaller than the parent of the node, then
	   * we don’t need to do anything. Otherwise, we need to traverse up to fix the violated
	   * heap property.
	   */
	 void maxbinaryheap_increasekey(struct heap* h, int i, void* new_val);

	 /*
	  * This function deletes key at index i. It first increased value to plus
	  * infinite, then calls extract().
	  * Deleting a key also takes O(log N) time. We replace the key to be deleted with the
	  * maximum infinite by calling increaseKey(). After increaseKey(), the plus infinite value
	  * must reach root, so we call extract() to remove the key.
	  */
	 void maxbinaryheap_delete(struct heap* h, int i);

	 /*
	  * Prints the heap elements (equivalent to level order traversal in a binary tree).
	  * */
	 void maxbinaryheap_print(struct heap* h);

	 /*
	  * Destroys and releases heap resources from memory.
	  */
	 void maxbinaryheap_destroy(struct heap* h);


#endif /* MAXBINARYHEAP_H_ */
