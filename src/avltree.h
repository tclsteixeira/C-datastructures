/**
 * avltree.h
 *
 *  Created on: 29/05/2023
 *      Author: Tiago C. Teixeira
 * Description: Implements AVL tree in C.
 *
 * Definition:
 *
 * 	  An AVL is a self-balancing Binary Search Tree (BST) where the difference
 * 	  between the heights of left and right subtrees of any node cannot be more
 * 	  than one.
 *
 * KEY POINTS
 *
 *    It is height balanced tree
 *    It is a binary search tree
 *    It is a binary tree in which the height difference between the left subtree and
 *      right subtree is almost one
 *    Height is the maximum depth from root to leaf
 *
 * Characteristics of AVL Tree:
 *
 *    It follows the general properties of a Binary Search Tree.
 *    Each subtree of the tree is balanced, i.e., the difference between the height of
 *    the left and right subtrees is at most 1.
 *    The tree balances itself when a new node is inserted. Therefore, the insertion
 *    operation is time-consuming
 *
 * Application of AVL Tree:
 *
 *    Most in-memory sets and dictionaries are stored using AVL trees.
 *    Database applications, where insertions and deletions are less common but
 *    frequent data lookups are necessary, also frequently employ AVL trees.
 *    In addition to database applications, it is employed in other applications that
 *    call for better searching.
 *    Most STL implementations of the ordered associative containers (sets, multisets,
 *    maps and multimaps) use red-black trees instead of AVL trees.
 *
 * Advantages of AVL Tree:
 *
 *    AVL trees can self-balance.
 *    It also provides faster search operations.
 *    AVL trees also have balancing capabilities with a different type of rotation
 *    Better searching time complexity than other trees, such as the binary Tree.
 *    Height must not be greater than log(N), where N is the total number of nodes in the Tree.
 *
 * Disadvantages of AVL Tree:
 *
 *    AVL trees are difficult to implement
 *    AVL trees have high constant factors for some operations.
 *
 * Maximum & Minimum number of Nodes
 * 	  Maximum number of nodes = 2^(H+1)  – 1
 * 	  Minimum number of nodes of height H = min no of nodes of height (H-1) + min no of nodes of height(H-2) + 1
 *
 * where H(0)=1
 *       H(1)=2
 *
 * The rotation operations (left and right rotate) take constant time as only a few
 * pointers are being changed there. Updating the height and getting the balance
 * factor also takes constant time. So the time complexity of the AVL insert remains
 * the same as the BST insert which is O(h) where h is the height of the tree.
 * Since the AVL tree is balanced, the height is O(Logn). So time complexity of
 * AVL insert is O(nLogn).
 *
 * Comparison with Red Black Tree:
 *
 * The AVL tree and other self-balancing search trees like Red Black are useful to get
 * all basic operations done in O(log n) time. The AVL trees are more balanced
 * compared to Red-Black Trees, but they may cause more rotations during insertion and
 * deletion. So if your application involves many frequent insertions and deletions,
 * then Red Black trees should be preferred. And if the insertions and deletions are
 * less frequent and search is the more frequent operation, then the AVL tree should
 * be preferred over Red Black Tree.
 *
 */

#ifndef AVLTREE_H_
	#define AVLTREE_H_

	// An AVL tree node
	struct avltreenode
	{
		void* data;
		struct avltreenode *left;
		struct avltreenode *right;
		int height;
	};

	// callback function to (hard) copy data from one tree node to another
	typedef void (*avltree_copydata)(void* dest, const void* from);
	typedef int (*avltree_cmp)(void* data, const void* key);
	typedef void (*avltree_freedata)(void* data);
	typedef void (*avltree_printnode)(struct avltreenode* node);

	struct avltree {
		struct avltreenode* root;
		avltree_copydata copydata;		// (hard) copy data function from one node to another
		avltree_cmp compare;			// comoare function (returns 0, 1 or -1)
		avltree_freedata freedata;		// function to release data from memory.
		avltree_printnode printnode;	// function to print data node
	};

	/*
	 * Function to create a new avl tree..
	 * Returns pointer to created avl tree instance is succeeded, NULL otherwise.
	 */
	struct avltree* avltree_create(void* rootdata, avltree_cmp comparefunc, avltree_freedata freedatafunc,
			avltree_printnode printnodefunc, avltree_copydata copydatafunc);

	/*
	 * Function to create a new avl tree node.
	 */
	struct avltreenode* avltree_createnode(void* data);

	/*
	 * Recursive function to insert a key in the avl subtree rooted
	 * with node and returns the new root of the subtree.
	 *
	 * The idea is to use recursive BST insert, after insertion, we get pointers to
	 * all ancestors one by one in a bottom-up manner. So we don’t need a parent
	 * pointer to travel up. The recursive code itself travels up and visits all
	 * the ancestors of the newly inserted node.
	 *
	 * Follow the steps mentioned below to implement the idea:
	 *
	 *    Perform the normal BST insertion.
	 *    The current node must be one of the ancestors of the newly inserted node.
	 *    Update the height of the current node.
	 *    Get the balance factor (left subtree height – right subtree height) of
	 *    the current node.
	 *    If the balance factor is greater than 1, then the current node is unbalanced
	 *    and we are either in the Left Left case or left Right case. To check
	 *    whether it is left left case or not, compare the newly inserted key with
	 *    the key in the left subtree root.
	 *    If the balance factor is less than -1, then the current node is unbalanced
	 *    and we are either in the Right Right case or Right-Left case.
	 *    To check whether it is the Right Right case or not, compare the newly
	 *    inserted key with the key in the right subtree root.
	 *
	 * Complexity Analysis
	 *
	 *   Time Complexity: O(n*log(n)), For Insertion
	 *   Auxiliary Space: O(1)
	 *
	 */
	struct avltreenode* avltree_insert(struct avltree* tree, struct avltreenode* node, void* data);

	/*
	 * Recursive function to delete a node with given key
	 * from avl subtree with given root. It returns root of
	 * the modified subtree.
	 *
	 * The following C implementation uses the recursive BST delete as basis. In the
	 * recursive BST delete, after deletion, we get pointers to all ancestors one by
	 * one in bottom up manner. So we don’t need parent pointer to travel up. The
	 * recursive code itself travels up and visits all the ancestors of the deleted node.
     *
     *    Perform the normal BST deletion.
     *    The current node must be one of the ancestors of the deleted node. Update the
     *    height of the current node.
     *    Get the balance factor (left subtree height – right subtree height) of the
     *    current node.
     *    If balance factor is greater than 1, then the current node is unbalanced and
     *    we are either in Left Left case or Left Right case. To check whether it is
     *    Left Left case or Left Right case, get the balance factor of left subtree. If
     *    balance factor of the left subtree is greater than or equal to 0, then it is
     *    Left Left case, else Left Right case.
     *    If balance factor is less than -1, then the current node is unbalanced and we
     *    are either in Right Right case or Right Left case. To check whether it is Right
     *    Right case or Right Left case, get the balance factor of right subtree. If
     *    the balance factor of the right subtree is smaller than or equal to 0, then
     *    it is Right Right case, else Right Left case.
	 *
	 * Time Complexity:
	 *   The rotation operations (left and right rotate) take constant
	 *   time as only few pointers are being changed there. Updating the height and
	 *   getting the balance factor also take constant time. So the time complexity of
	 *   AVL delete remains same as BST delete which is O(h) where h is height of the
	 *   tree. Since AVL tree is balanced, the height is O(Logn). So time complexity of
	 *   AVL delete is O(Log n).
	 *
	 * Auxiliary Space:
	 *   O(1), since no extra space is used.
	 *
	 * */
	struct avltreenode* avltree_delete(struct avltree* tree,  struct avltreenode* root, void* key);

	/*
	 * Searches for an element in the avl tree (based on binary search tree).
	 * Returns element instance if found, NULL otherwse.
	 *
	 * Steps:
	 *    We start at the root, and then we compare the value to be searched with the
	 *    value of the root,
	 *    If it’s equal we are done with the search if it’s smaller we know that we
	 *    need to go to the left subtree because in a binary search tree all the
	 *    elements in the left subtree are smaller and all the elements in the right
	 *    subtree are larger.
	 *    Searching an element in the binary search tree is basically this traversal,
	 *    at each step we go either left or right and at each step we discard one of
	 *    the sub-trees.
	 *
	 * If the tree is balanced, (we call a tree balanced if for all nodes the
	 * difference between the heights of left and right subtrees is not greater
	 * than one) we start with a search space of ‘n’ nodes and as we discard one
	 * of the sub-trees, we discard ‘n/2’ nodes so our search space gets reduced
	 * to ‘n/2’. In the next step, we reduce the search space to ‘n/4’ and we repeat
	 * until we find the element or our search space is reduced to only one node.
	 * The search here is also a binary search hence the name; Binary Search Tree.
	 *
	 * Time complexity: O(h), where h is the height of the BST.
	 * Space complexity: O(h), where h is the height of the BST. This is because the
	 * maximum amount of space needed to store the recursion stack would be h.
	 *
	 **/
	struct avltreenode* avltree_search(struct avltree* tree, struct avltreenode* root, const void* key);

	/*
	 * Iterative function to compute the size of a tree.
	 *
	 * Algorithm:
	 *
	 * 1) Create an empty queue q
	 * 2) temp_node = root   (start from root)
	 * 3) Loop while temp_node is not NULL
	 *    a) Enqueue temp_node’s children (first left then right children) to q
	 *    b) Increase count with every enqueuing.
	 *    c) Dequeue a node from q and assign it’s value to temp_node
	 *
	 * Time Complexity: O(n)
	 * Auxiliary Space: O(level_max) where level max is maximum number of node in any level.
	 *
	 * */
	int avltree_getSizeIt(const struct avltree* tree);

	/*
	 * Function to find the depth of a given node with given key in a avl Tree.
	 *
	 * The depth of a node is the number of edges present in path from the root node
	 * of a tree to that node.
	 *
	 *	See search function;
	 *
	 *	Same as search:
	 *  Time Complexity: O(h)
	 * 	Auxiliary Space: O(h)
	 *
	 */
	int avltree_findNodeDepth(struct avltree* tree, void* key);

	/*
	 * Function to find the height of a given node in a Binary Tree
	 * whose data matches the given key.
	 *
	 * Height of a node K (of a Binary Tree) = Number of edges in the longest path
	 * connecting K to any leaf node.
	 *
	 * Follow the steps below to find the height of the given node:
	 *
	 *   If the tree is empty, print -1.
	 *   Otherwise, perform the following steps:
	 *       Calculate the height of the left subtree recursively.
	 *       Calculate the height of the right subtree recursively.
	 *       Update height of the current node by adding 1 to the maximum of the two
	 *       heights obtained in the previous step. Store the height in a variable,
	 *       say ans.
	 *       If the current node is equal to the given node Key, print the value of
	 *       ans as the required answer.
	 *
	 * See search function;
	 *
	 * Same as search:
	 * Time Complexity: O(h)
	 * Auxiliary Space: O(h)
	 *
	 */
	int avltree_findNodeHeight(struct avltree* tree, void* key);

	/*
	 * Function to find the height(depth) of the tree using level order traversal.
	 *
	 * This method also uses the concept of Level Order Traversal but we wont be adding
	 * null in the Queue. Simply increase the counter when the level increases and push
	 * the children of current node into the queue, then remove all the nodes from the
	 * queue of the current Level.
	 *
	 * Do Level Order Traversal, while adding Nodes at each level to Queue, we have to
	 * add NULL Node so that whenever it is encountered, we can increment the value of
	 * variable and that level get counted.
	 *
	 * Follow the below steps to Implement the idea:
	 *
	 *   Traverse the tree in level order traversal starting from root.
	 *       Initialize an empty queue Q, a variable depth and push root, then push null into the Q.
	 *       Run a while loop till Q is not empty.
	 *           Store the front element of Q and Pop out the front element.
	 *           If the front of Q is NULL then increment depth by one and if queue is not empty then push NULL into the Q.
	 *           Else if the element is not NULL then check for its left and right children and if they are not NULL push them into Q.
	 *   Return depth.
	 *
	 * Time Complexity: O(N)
	 * Auxiliary Space: O(N)
	 *
	 * */
	int avltree_treeHeightLevelOrder(struct avltree* tree);

	/*
	 * Prints tree nodes data.
	 * */
	void avltree_print(struct avltree* tree, char* spaces);

	/*
	 * Releases all nodes and data instance from avl tree.
	 * */
	void avltree_clear(struct avltree* tree);

	/*
	 * Releases all nodes, his data, and the avl tree structure instance from memory.
	 * */
	void avltree_destroy(struct avltree* tree);


#endif /* AVLTREE_H_ */
