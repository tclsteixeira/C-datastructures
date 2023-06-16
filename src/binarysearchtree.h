/*
 * binarysearchtree.h
 *
 *  Created on: 21/05/2023
 *      Author: Tiago C. Teixeira
 * Description: Implements binary search tree functionality in C.
 *
 * A binary Search Tree is a special type of binary tree data structure that has the
 * following properties:
 *
 *    The left subtree of a node contains only nodes with keys lesser than the node’s key.
 *    The right subtree of a node contains only nodes with keys greater than the node’s key.
 *    The left and right subtree each must also be a binary search tree.
 *
 * There must be no duplicate nodes.
 *
 * The above properties of a Binary Search Tree provide an ordering among keys so that
 * the operations like search, minimum and maximum can be done fast.
 *
 * Applications of BST:
 *
 *    Graph algorithms:
 *    	BSTs can be used to implement graph algorithms, such as in
 *    	minimum spanning tree algorithms.
 *
 *    Priority Queues:
 *    	BSTs can be used to implement priority queues, where the
 *    	element with the highest priority is at the root of the tree, and elements
 *    	with lower priority are stored in the subtrees.
 *
 *    Self-balancing binary search tree:
 *    	BSTs can be used as a self-balancing data structures such as AVL tree and
 *    	Red-black tree.
 *
 *    Data storage and retrieval:
 *    	BSTs can be used to store and retrieve data quickly, such as in databases,
 *    	where searching for a specific record can be done in logarithmic time.
 *
 * Advantages:
 *
 *    Fast search: Searching for a specific value in a BST has an average time
 *    complexity of O(log n), where n is the number of nodes in the tree. This
 *    is much faster than searching for an element in an array or linked list,
 *    which have a time complexity of O(n) in the worst case.
 *
 *    In-order traversal: BSTs can be traversed in-order, which visits the left
 *    subtree, the root, and the right subtree. This can be used to sort a dataset.
 *
 *    Space efficient: BSTs are space efficient as they do not store any redundant
 *    information, unlike arrays and linked lists.
 *
 * Disadvantages:
 *
 *    Skewed trees: If a tree becomes skewed, the time complexity of search, insertion,
 *    and deletion operations will be O(n) instead of O(log n), which can make the
 *    tree inefficient.
 *
 *    Additional time required: Self-balancing trees require additional time to maintain
 *    balance during insertion and deletion operations.
 *
 *    Efficiency: BSTs are not efficient for datasets with many duplicates as they
 *    will waste space.
 *
 *
 * Sources: https://www.geeksforgeeks.org
 *
 */

#ifndef BINARYSEARCHTREE_H_
	#define BINARYSEARCHTREE_H_

	#include "binarytree.h"

	/*
	 * Function to create a new binary (search) tree.
	 * Returns pointer to created binary tree instance is succeeded, NULL otherwise.
	 */
	struct binarytree* bst_create(void* rootdata, binarytree_cmp comparefunc, binarytree_freedata freedatafunc,
										 binarytree_printnode printnodefunc, binarytree_copydata copydatafunc);

	/*
	 * Insert a value in a Binary Search Tree:
	 *
	 * A new key is always inserted at the leaf by maintaining the property of the
	 * binary search tree. We start searching for a key from the root until we hit
	 * a leaf node. Once a leaf node is found, the new node is added as a child of
	 * the leaf node. The below steps are followed while we try to insert a node
	 * into a binary search tree:
	 *
	 *     Check the value to be inserted (say X) with the value of the current node
	 *     (say val) we are in:
     *     If X is less than val move to the left subtree.
     *     Otherwise, move to the right subtree.
     *     Once the leaf node is reached, insert X to its right or left based on the
     *     relation between X and the leaf node’s value.
     *
     *  Time Complexity:
     *
     *      The worst-case time complexity of insert operations is O(h) where h is the
     *     	height of the Binary Search Tree.
     *      In the worst case, we may have to travel from the root to the deepest leaf
     *     	node. The height of a skewed tree may become n and the time complexity of
     *     	insertion operation may become O(n).
     *
     *  Auxiliary Space:
     *  	The auxiliary space complexity of insertion into a binary search tree is O(1).
	 *
	 * */
	struct binarytreenode* bst_insert(struct binarytree* tree, struct binarytreenode* root, void* data);

	/*
	 * Given a binary search tree and a key, this function deletes the key and
	 * returns the new root.
	 *
	 * Follow the below steps to solve the problem:
	 *
	 *   Create a recursive function (say deleteNode) which returns the correct node that will be in the position.
	 *   If the root is NULL, then return root (Base case)
	 *   If the key is less than the root’s value, then set root->left = deleteNode(root->left, key)
	 *   If the key is greater than the root’s value, then set root->right = deleteNode(root->right, key)
	 *   Else check
	 *       If the root is a leaf node then return null
	 *       Else if it has only the left child, then return the left child
	 *       Else if it has only the right child, then return the right child
	 *       Otherwise, set the value of root as of its inorder successor and
	 *       recur to delete the node with the value of the inorder successor.
	 *
	 * */
	struct binarytreenode* bst_deletenode(struct binarytree* tree, struct binarytreenode* root, void* key);

    /*
     *
     * Given a binary search tree and a key, this function
     * deletes the key and returns the new root (optimized version)
     *
     * Optimized approach for two children case:
     *
     *   We recursively call delete() for the successor in the above recursive code.
     *   We can avoid recursive calls by keeping track of the parent node of the
     *   successor so that we can simply remove the successor by making the child of
     *   a parent NULL. We know that the successor would always be a leaf node.
     *
     * Time Complexity: O(h), where h is the height of the BST.
     * Auxiliary Space: O(n).
     *
     */
	struct binarytreenode* bst_delete(struct binarytree* tree, struct binarytreenode* root, void* key);

	/*
	 * Searches for an element in the binary search tree.
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
	struct binarytreenode* bst_search(struct binarytree* tree, struct binarytreenode* root, const void* key);

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
	int bst_getSizeIt(const struct binarytree* tree);

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
	int bst_treeHeightLevelOrder(struct binarytree* tree);

	/*
	 * Function to find the depth of a given node with given key in a Binary Tree.
	 *
	 * The depth of a node is the number of edges present in path from the root node
	 * of a tree to that node.
	 *
	 * Follow the steps below to find the depth of the given node:
	 *
	 *  If the tree is empty, print -1.
	 *  Otherwise, perform the following steps:
	 *       Initialize a variable, say dist as -1.
	 *       Check if Key is matches the given node's data.
	 *       Otherwise, check if it is present in either of the subtrees, by recursively
	 *       checking for the left and right subtrees respectively.
	 *       If found to be true, print the value of dist + 1.
	 *       Otherwise, print dist.
	 *
	 *  Time Complexity: O(N)
	 * 	Auxiliary Space: O(1)
	 *
	 */
	int bst_findNodeDepth(struct binarytree* tree, struct binarytreenode* root, void* key);

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
	 * Time Complexity: O(N)
	 * Auxiliary Space: O(1)
	 */
	int bst_findNodeHeight(struct binarytree* tree, struct binarytreenode* root, void* key);

	/*
	 * Prints the binary search tree on console.
	 * */
	void bst_print(struct binarytree* tree, char* spaces);

	/*
	 * Releases all nodes from binary tree.
	 * */
	void bst_clear(struct binarytree* tree);

	/*
	 * Releases the tree and all nodes and his data from memory.
	 * */
	void bst_destroy(struct binarytree* tree) ;

#endif /* BINARYSEARCHTREE_H_ */
