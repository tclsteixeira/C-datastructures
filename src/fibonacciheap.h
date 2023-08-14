/*
 * fibonacciheap.h
 *
 *  Created on: 19/07/2023
 *      Author: Tiago C. Teixeira
 * Description: C implementation of Fibonacci heap data structure.
 *
 * Definition
 *
 *    A Fibonacci heap is a data structure used for implementing priority queues. It is a type
 *    of heap data structure, but with several improvements over the traditional binary heap
 *    and binomial heap data structures.
 *    The key advantage of a Fibonacci heap over other heap data structures is its fast
 *    amortized running time for operations such as insert, merge and extract-min, making
 *    it one of the most efficient data structures for these operations. The running time of
 *    these operations in a Fibonacci heap is O(1) for insert, O(log n) for extract-min
 *    and O(1) amortized for merge.
 *    A Fibonacci heap is a collection of trees, where each tree is a heap-ordered multi-tree,
 *    meaning that each tree has a single root node with its children arranged in a
 *    heap-ordered manner. The trees in a Fibonacci heap are organized in such a way that the
 *    root node with the smallest key is always at the front of the list of trees.
 *    In a Fibonacci heap, when a new element is inserted, it is added as a singleton tree.
 *    When two heaps are merged, the root list of one heap is simply appended to the root list
 *    of the other heap. When the extract-min operation is performed, the tree with the
 *    minimum root node is removed from the root list and its children are added to the root
 *    list.
 *    One unique feature of a Fibonacci heap is the use of lazy consolidation, which is a
 *    technique for improving the efficiency of the merge operation. In lazy consolidation,
 *    the merging of trees is postponed until it is necessary, rather than performed
 *    immediately. This allows for the merging of trees to be performed more efficiently in
 *    batches, rather than one at a time.
 *
 * In summary, a Fibonacci heap is a highly efficient data structure for implementing
 * priority queues, with fast amortized running times for operations such as insert, merge
 * and extract-min. Its use of lazy consolidation and its multi-tree structure make it a
 * superior alternative to traditional binary and binomial heaps in many applications.
 *
 *
 * Time complexity:
 *
 * 1) Find Min:      Θ(1)     [Same as  Binary but not Binomial since binomial has o(log n)]
 * 2) Delete Min:    O(Log n) [Θ(Log n) in both Binary and Binomial]
 * 3) Insert:        Θ(1)     [Θ(Log n) in Binary and Θ(1) in Binomial]
 * 4) Decrease-Key:  Θ(1)     [Θ(Log n) in both Binary and Binomial]
 * 5) Merge:         Θ(1)     [Θ(m Log n) or Θ(m+n) in Binary and
 *                            Θ(Log n) in Binomial]
 *
 * Like Binomial Heap, Fibonacci Heap is a collection of trees with min-heap or max-heap
 * properties. In Fibonacci Heap, trees can have any shape even if all trees can be single
 * nodes (This is unlike Binomial Heap where every tree has to be a Binomial Tree).
 *
 * Fibonacci Heap maintains a pointer to the minimum value (which is the root of a tree). All
 * tree roots are connected using a circular doubly linked list, so all of them can be
 * accessed using a single ‘min’ pointer.
 *
 * The main idea is to execute operations in a “lazy” way. For example merge operation simply
 * links two heaps, insert operation simply adds a new tree with a single node. The operation
 * extract minimum is the most complicated operation. It does delay the work of
 * consolidating trees. This makes delete also complicated as delete first decreases the key
 * to minus infinite, then calls extract minimum.
 *
 * Below are some interesting facts about Fibonacci Heap
 *
 *    The reduced time complexity of Decrease-Key has importance in Dijkstra and Prim
 *    algorithms. With Binary Heap, the time complexity of these algorithms is O(VLogV + ELogV).
 *    If Fibonacci Heap is used, then time complexity is improved to O(VLogV + E)
 *    Although Fibonacci Heap looks promising time complexity-wise, it has been found slow in
 *    practice as hidden constants are high (Source Wiki).
 *    Fibonacci heaps is mainly called so because Fibonacci numbers are used in the running
 *    time analysis. Also, every node in Fibonacci Heap has a degree at most O(log n) and the
 *    size of a subtree rooted in a node of degree k is at least Fk+2, where Fk is the
 *    kth Fibonacci number.
 *
 * Advantages of Fibonacci Heap:
 *
 *    Fast amortized running time: The running time of operations such as insert, extract-min
 *    and merge in a Fibonacci heap is O(1) for insert, O(log n) for extract-min and O(1)
 *    amortized for merge, making it one of the most efficient data structures for these
 *    operations.
 *    Lazy consolidation: The use of lazy consolidation allows for the merging of trees to be
 *    performed more efficiently in batches, rather than one at a time, improving the
 *    efficiency of the merge operation.
 *    Efficient memory usage: Fibonacci heaps have a relatively small constant factor
 *    compared to other data structures, making them a more memory-efficient choice in some
 *    applications.
 *
 * Disadvantages of Fibonacci Heap:
 *
 *    Increased complexity: The structure and operations of a Fibonacci heap are more
 *    complex than those of a binary or binomial heap, making it a less intuitive
 *    data structure for some users.
 *    Less well-known: Compared to other data structures, Fibonacci heaps are less
 *    well-known and widely used, making it more difficult to find resources and support
 *    for implementation and optimization.
 *
 */

#ifndef FIBONACCIHEAP_H_
	#define FIBONACCIHEAP_H_
	#include <stddef.h>

	#define FIBHEAP_FLAG_NO  'N'
	#define FIBHEAP_FLAG_YES  'Y'
	#define FIBHEAP_MARK_WHITE  'W'
	#define FIBHEAP_MARK_BLACK  'B'


	// Creating a structure to represent a node in the heap
	struct fibheapnode {
		struct fibheapnode* parent; // Parent pointer
		struct fibheapnode* child; 	// Child pointer
		struct fibheapnode* left; 	// Pointer to the node on the left
		struct fibheapnode* right; 	// Pointer to the node on the right
		void* key; 	// Value of the node
		int degree; // Degree of the node
		char mark; 	// Black or white mark of the node
		char c; 	// Flag for assisting in the Find node function
	};

	typedef int (*fibheap_cmp)(const void* key1, const void* key2);
	typedef void (*fibheap_freedata)(void* data);
	typedef void (*fibheap_printdata)(void* data);

	struct fibheap {
		// Creating min pointer as "mini"
		struct fibheapnode* mini;
		fibheap_cmp compare;
		fibheap_freedata freedata;
		fibheap_printdata printdata;

		// Declare an integer for number of nodes in the heap
		int no_of_nodes;
		void* MINVALUE;
	};

	/*
	 * Creates a new fibonacci heap instance.
	 */
	struct fibheap* fibheap_create(void* minlimit, fibheap_cmp comparefunc,
											fibheap_printdata printdatafunc,
											fibheap_freedata freedatafunc);

	/*
	 * Creates a new fibonacci heap node
	 */
	struct fibheapnode* fibheap_createnode(void* val);

	/*
	 * To insert a node in a Fibonacci heap H, the following algorithm is followed:
	 *
	 *       1- Create a new node ‘x’.
	 *       2- Check whether heap H is empty or not.
	 *       3- If H is empty then:
	 *            Make x as the only node in the root list.
	 *            Set H(min) pointer to x.
	 *       4- Else:
	 *            Insert x into root list and update H(min) if needed.
	 */
	void fibheap_insert(struct fibheap* fh, void* val);

	/*
	 * Union of two Fibonacci heaps h1 with h2 and return result heap as h1 in O(1)
	 *
	 * Union: Union of two Fibonacci heaps H1 and H2 can be accomplished as follows:
	 *
	 *       1- Join root lists of Fibonacci heaps H1 and H2 and make a single Fibonacci heap H.
	 *       2- If H1(min) < H2(min) then:
	 *            H(min) = H1(min).
	 *       3- Else:
	 *            H(min) = H2(min).
	 */
	struct fibheap* fibheap_union(struct fibheap* h1, struct fibheap* h2);

	/*
	 * Function to extract minimum node in the heap
	 *
	 *   1- Delete the min node.
	 *   2- Set head to the next min node and add all the trees of the deleted node in the
	 *   	root list.
	 *   3- Create an array of degree pointers of the size of the deleted node.
	 *   4- Set degree pointer to the current node.
	 *   5- Move to the next node.
	 *       If degrees are different then set degree pointer to next node.
	 *       If degrees are the same then join the Fibonacci trees by union operation.
	 *   6- Repeat steps 4 and 5 until the heap is completed.
	 *
	 */
	struct fibheapnode* fibheap_extract_min(struct fibheap* fh);

	/*
	 * Function to decrease the value of a node in the heap
	 *
	 * To decrease the value of any element in the heap, we follow the following algorithm:
	 *
	 *    Decrease the value of the node ‘x’ to the new chosen value.
	 *    CASE 1) If min-heap property is not violated,
	 *        Update min pointer if necessary.
	 *    CASE 2) If min-heap property is violated and parent of ‘x’ is unmarked,
	 *        Cut off the link between ‘x’ and its parent.
	 *        Mark the parent of ‘x’.
	 *        Add tree rooted at ‘x’ to the root list and update min pointer if necessary.
	 *    CASE 3)If min-heap property is violated and parent of ‘x’ is marked,
	 *        Cut off the link between ‘x’ and its parent p[x].
	 *        Add ‘x’ to the root list, updating min pointer if necessary.
	 *        Cut off link between p[x] and p[p[x]].
	 *        Add p[x] to the root list, updating min pointer if necessary.
	 *        If p[p[x]] is unmarked, mark it.
	 *        Else, cut off p[p[x]] and repeat steps 4.2 to 4.5, taking p[p[x]] as ‘x’.
	 *
	 */
	void fibheap_decrease_key(struct fibheap* fh, struct fibheapnode* found, void* val);

	/*
	 * Function to find the given node and decrease his value
	 */
	void fibheap_find_and_decrease(struct fibheap* fh, struct fibheapnode* mini,
									void* old_val, void* val);

	/*
	 * Deleting a node from the heap
	 *
	 * To delete any element in a Fibonacci heap, the following algorithm is followed:
	 *
	 *    1- Decrease the value of the node to be deleted ‘x’ to a minimum by Decrease_key()
	 *    	function.
	 *    2- By using min-heap property, heapify the heap containing ‘x’, bringing ‘x’ to
	 *    	the root list.
	 *    3- Apply Extract_min() algorithm to the Fibonacci heap.
	 *
	 */
	struct fibheapnode* fibheap_delete(struct fibheap* fh, void* val);

	/*
	 * Function to display the heap
	 */
	void fibheap_print(struct fibheap* fh);

	/*
	 * Destroys and releases fibonacci heap node resources from memory.
	 */
	void fibheap_destroynode(struct fibheap* fh, struct fibheapnode* node);

	/*
	 * Destroys and releases heap resources from memory.
	 */
	void fibheap_destroy(struct fibheap* fh);

#endif /* FIBONACCIHEAP_H_ */
