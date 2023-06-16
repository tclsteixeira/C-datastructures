/**********************************************************************************
 * binarytree.h
 *
 *  Created on: 21/04/2023
 *      Author: Tiago C. Teixeira
 * Description: Implements a binary tree data structure in C.
 *
 * Definition
 *
 * 		A tree data structure is a hierarchical structure that is used to represent
 * 		and organize data in a way that is easy to navigate and search. It is a
 * 		collection of nodes that are connected by edges and has a hierarchical
 * 		relationship between the nodes. The topmost node of the tree is called the
 * 		root, and the nodes below it are called the child nodes. Each node can
 * 		have multiple child nodes, and these child nodes can also have their own
 * 		child nodes, forming a recursive structure.
 *
 *		The data in a tree are not stored in a sequential manner i.e, they are not
 *		stored linearly. Instead, they are arranged on multiple levels or we can say
 *		it is a hierarchical structure. For this reason, the tree is considered to
 *		be a non-linear data structure.
 *
 *
 *	Basic Terminologies In Tree Data Structure:
 *
 *   Parent Node: The node which is a predecessor of a node is called the parent
 *   node of that node. {B} is the parent node of {D, E}.
 *
 *   Child Node: The node which is the immediate successor of a node is called the
 *   child node of that node. Examples: {D, E} are the child nodes of {B}.
 *
 *   Root Node: The topmost node of a tree or the node which does not have any parent
 *   node is called the root node. {A} is the root node of the tree. A non-empty tree
 *   must contain exactly one root node and exactly one path from the root to all
 *   other nodes of the tree.
 *
 *   Leaf Node or External Node: The nodes which do not have any child nodes are called
 *   leaf nodes. {K, L, M, N, O, P} are the leaf nodes of the tree.
 *
 *   Ancestor of a Node: Any predecessor nodes on the path of the root to that node are
 *   called Ancestors of that node. {A,B} are the ancestor nodes of the node {E}
 *
 *   Descendant: Any successor node on the path from the leaf node to that node.
 *   {E,I} are the descendants of the node {B}.
 *
 *   Sibling: Children of the same parent node are called siblings. {D,E} are called
 *   siblings.
 *
 *   Level of a node: The count of edges on the path from the root node to that node.
 *   The root node has level 0.
 *
 *   Internal node: A node with at least one child is called Internal Node.
 *
 *   Neighbour of a Node: Parent or child nodes of that node are called neighbors of
 *   that node.
 *
 *   Subtree: Any node of the tree along with its descendant.
 *
 * Properties of a Tree:
 *
 *   Number of edges: An edge can be defined as the connection between two nodes.
 *   If a tree has N nodes then it will have (N-1) edges. There is only one path
 *   from each node to any other node of the tree.
 *
 *   Depth of a node: The depth of a node is defined as the length of the path
 *   from the root to that node. Each edge adds 1 unit of length to the path.
 *   So, it can also be defined as the number of edges in the path from the root
 *   of the tree to the node.
 *
 *   Height of a node: The height of a node can be defined as the length of the
 *   longest path from the node to a leaf node of the tree.
 *
 *   Height of the Tree: The height of a tree is the length of the longest path
 *   from the root of the tree to a leaf node of the tree.
 *
 *   Degree of a Node: The total count of subtrees attached to that node is called
 *   the degree of the node. The degree of a leaf node must be 0. The degree of a
 *   tree is the maximum degree of a node among all the nodes in the tree.
 *
 * Some more properties are:
 *
 *   Traversing in a tree is done by depth first search and breadth first search
 *   algorithm.
 *   It has no loop and no circuit
 *   It has no self-loop
 *   Its hierarchical model.
 *
 *
 * Advantages of Tree data structure
 *
 *   Efficient insertion, deletion, and search operations.
 *   Trees are flexibility in terms of the types of data that can be stored.
 *   It is used to represent hierarchical relationships.
 *   It has the ability to represent a recursive structure.
 *   Used in various algorithms and data structures such as Huffman coding and
 *   decision trees.
 *   Trees use less space than other data structures, like lists, and linked lists.
 *   Trees are dynamic in nature.
 *   Tree data structures can automatically self-organize as new data is added
 *   or removed,
 *   which can improve performance and reduce complexity.
 *
 * Disadvantages of Tree data structure
 *
 *   Trees require additional memory for pointers.
 *   Trees are not the best choice for data that does not have hierarchical relationships.
 *   Trees with many levels can become expensive to search and traverse.
 *   Limited scalability compared to other data structures such as hash tables.
 *   Trees are typically used for storing and manipulating hierarchical data, and may not be the best choice for other types of data.
 *   Not suitable for large datasets.
 *   Trees can become unbalanced, leading to poor performance and decreased efficiency.
 *
 * Applications of Tree data structure:
 *
 *	The applications of tree data structures are as follows:
 *
 *  1. Spanning trees: It is the shortest path tree used in the routers to direct
 *     the packets to the destination.
 *
 *  2. Binary Search Tree: It is a type of tree data structure that helps in
 *     maintaining a sorted stream of data.
 *
 *      Full Binary tree
 *      Complete Binary tree
 *      Skewed Binary tree
 *      Complete Binary tree
 *      Skewed Binary tree
 *      Strictly Binary tree
 *      Extended Binary tree
 *
 *  3. Storing hierarchical data: Tree data structures are used to store the
 *     hierarchical data, which means data is arranged in the form of order.
 *
 *  4. Syntax tree: The syntax tree represents the structure of the program’s
 *     source code, which is used in compilers.
 *
 *  5. Trie: It is a fast and efficient way for dynamic spell checking. It is
 *     also used for locating specific keys from within a set.
 *
 *  6. Heap: It is also a tree data structure that can be represented in a form
 *     of an array. It is used to implement priority queues.
 *
 *  7. Artificial intelligence: Decision trees and other tree-based models are
 *     commonly used in machine learning and artificial intelligence to make
 *     predictions and classify data.
 *
 *  8. Database: Some databases use trees to organize data for efficient searching
 *     and sorting.
 *
 *  9. Network: Routing algorithms for networks, such as Internet Protocol (IP) routing,
 *     use trees to find the best path for data to travel from one network to another.
 *
 *********************************************************************************/

#ifndef BINARYTREE_H_
	#define BINARYTREE_H_

	// represents a node in the binary tree
	struct binarytreenode {
		void* data;
		struct binarytreenode* left;
		struct binarytreenode* right;
	};

	// callback function to (hard) copy data from one tree node to another
	typedef void (*binarytree_copydata)(void* dest, const void* from);
	typedef int (*binarytree_cmp)(void* data, const void* key);
	typedef void (*binarytree_freedata)(void* data);
	typedef void (*binarytree_printnode)(struct binarytreenode* node);

	struct binarytree {
		struct binarytreenode* root;
		binarytree_copydata copydata;	// (hard) copy data from source to dest
		binarytree_cmp compare;			// comoare function (returns 0, 1 or -1)
		binarytree_freedata freedata;	// function to release data from memory.
		binarytree_printnode printnode;	// function to print data node
	};

	/*
	 * Function to create a new binary tree..
	 * Returns pointer to created binary tree instance is succeeded, NULL otherwise.
	 */
	struct binarytree* binarytree_create(void* rootdata, binarytree_cmp comparefunc, binarytree_freedata freedatafunc,
			binarytree_printnode printnodefunc, binarytree_copydata copydatafunc);

	/*
	 * Function to create a new binary tree node.
	 */
	struct binarytreenode* binarytree_createnode(void* data);

	/*
	 * Computes the number of nodes in a binary tree using recursion.
	 *
	 * Algorithm:
	 *
	 * 1. If tree is empty then return 0
	 * 2. Else
	 *     (a) Get the size of left subtree recursively  i.e., call
	 *          size( tree->left-subtree)
	 *     (a) Get the size of right subtree recursively  i.e., call
	 *          size( tree->right-subtree)
	 *     (c) Calculate size of the tree as following:
	 *            tree_size  =  size(left-subtree) + size(right-
	 *                               subtree) + 1
	 *     (d) Return tree_size
	 *
	 * Time Complexity: O(N)
	 * As every node is visited once.
	 *
	 * Auxiliary Space: O(N)
	 *
	 * The extra space is due to the recursion call stack and the worst case occurs
	 * when the tree is either left skewed or right skewed.
	 *
	 * Since this program is similar to traversal of tree, time and space
	 * complexities will be same as Tree traversal.
	 *
	 * */
	int binarytree_getSize(struct binarytreenode* root);

	/*
	 * Computes the number of nodes in a binary tree using recursion.
	 *
	 * The idea is to use Level Order Traversing .
	 *
	 * 1) Create an empty queue q
	 * 2) temp_node = root 		(start from root)
	 * 3) Loop while temp_node is not NULL
	 * 		a) Enqueue temp_node’s children (first left then right children) to q
	 *  	b) Increase count with every enqueuing.
	 *  	c) Dequeue a node from q and assign it’s value to temp_node
	 *
	 * */
	int binarytree_getSizeIt(const struct binarytree* tree);

   /*
    * Function to insert element in binary tree.
    * Given a binary tree and a key, insert the key into the binary tree at the
    * first position available in level order.
    *
    * The idea is to do an iterative level order traversal of the given tree using
    * queue. If we find a node whose left child is empty, we make a new key as the
    * left child of the node. Else if we find a node whose right child is empty,
    * we make the new key as the right child. We keep traversing the tree until
    * we find a node whose either left or right child is empty.
    *
    * Returns root node.
    *
    * */
	struct binarytreenode* binarytree_insertnode_levelordered(struct binarytreenode* root, void* data);

   /*
    * Given a binary tree, process its nodes in inorder.
    *
    * Algorithm Inorder(tree)
    *
    *   Traverse the left subtree, i.e., call Inorder(left->subtree)
    *   Visit the root.
    *   Traverse the right subtree, i.e., call Inorder(right->subtree)
    *
    *  In the case of binary search trees (BST), Inorder traversal gives nodes
    *  in non-decreasing order. To get nodes of BST in non-increasing order,
    *  a variation of Inorder traversal where Inorder traversal is reversed can be used.
    *
    * */
	void binarytree_inorder(struct binarytreenode* node, void (*visit)(struct binarytreenode* node));

   /*
    * Given a binary tree, visit its nodes in preorder
    *
    *  Algorithm Preorder(tree)
    *
    *    Visit the root.
    *    Traverse the left subtree, i.e., call Preorder(left->subtree)
    *    Traverse the right subtree, i.e., call Preorder(right->subtree)
    *
    *   Preorder traversal is used to create a copy of the tree.
    *   Preorder traversal is also used to get prefix expressions on an
    *   expression tree.
    *
    * */
	void binarytree_preorder(struct binarytreenode* node, void (*visit)(struct binarytreenode* node));

   /*
    *  Given a binary tree, visit its nodes according to the
    *  "bottom-up" postorder traversal.
    *
    *  Algorithm Postorder(tree)
    *
    *    Traverse the left subtree, i.e., call Postorder(left->subtree)
    *    Traverse the right subtree, i.e., call Postorder(right->subtree)
    *    Visit the root
    *
    *   Postorder traversal is used to delete the tree.
    *   Postorder traversal is also useful to get the postfix expression
    *   of an expression tree
    */
	void binarytree_postorder(struct binarytreenode* node, void (*visit)(struct binarytreenode* node));

   /*
    * Function to delete element in binary tree
    *
    * Given a binary tree, delete a node from it by making sure that the tree
    * shrinks from the bottom (i.e. the deleted node is replaced by the bottom-
    * most and rightmost node).
    *
    * */
	struct binarytreenode* binarytree_delete(struct binarytree* tree, void* key);

	/*
	 * Searches for a node whose data matches a given key.
	 * Returns founded node if succeeded, NULL otherwise.
	 * */
	struct binarytreenode* binarytree_search(struct binarytree* tree, struct binarytreenode* root, void* key);

	/*
	 * Compute the "maxDepth" of a tree -- the number of
	 * nodes along the longest path from the root node
	 * down to the farthest leaf node.
	 */
	int binarytree_treeDepth(struct binarytreenode* node);

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
	int binarytree_treeHeightLevelOrder(struct binarytree* tree);

	/*
	 * Function to find the height of a binary tree using Morris
	 * Traversal technique
	 *
	 * An Efficient Approach  To Solve This Problem Can Be “Using Morris Traversal Algorithm”:
	 *
	 * The basic idea behind the algorithm is to traverse the left subtree of each node
	 * first and then move to its right subtree. During the traversal, we keep track of
	 * the maximum depth of the tree by incrementing a counter variable each time we move
	 * down a level in the tree.
	 *
	 * follow the below steps to implement the above idea:
	 *
	 *    Initialize the current node as the root of the tree.
	 *    While the current node is not NULL:
	 *    a. If the left child of the current node is NULL, visit the current node and move
	 *    to its right child.
	 *    b. If the left child of the current node is not NULL:
	 *    i. Find the rightmost node in the left subtree of the current node.
	 *    ii. If the right child of this node is NULL, set it to the current node and move
	 *    to the left child of the current node.
	 *    iii. If the right child of this node is not NULL, set it back to NULL, visit
	 *    the current node, and move to its right child.
	 *    Return the maximum depth of the tree.
	 *
	 * Time Complexity: (N) , The time complexity of finding the height of a binary tree
	 * using Morris traversal is O(n), where n is the number of nodes in the tree.
	 *
	 * Auxiliary Space:(1) , The space complexity of the algorithm is O(1), which is
	 * constant space complexity. This is because we are not using any additional data
	 * structures to store nodes or keep track of the traversal
	 *
	 * */
	int binarytree_findHeightMorrisTrav(struct binarytreenode* root);

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
	int binarytree_findNodeDepth(struct binarytree* tree, struct binarytreenode* root, void* key);

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
	 *
	 */
	int binarytree_findNodeHeight(struct binarytree* tree, struct binarytreenode* root, void* key);

	/*
	 * Function to visit the node
	 * which are present at the maximum depth.
	 * While traversing the nodes compare the level
	 * of the node with max_level
	 * (Maximum level till the current node).
	 * If the current level exceeds the maximum level,
	 * update the max_level as current level.
	 * If the max level and current level are same,
	 * visit the root data.
	 *
	 */
	void binarytree_visitNodesAtMaxDepth(struct binarytreenode* root, int level, int* max_level, void (*visit)(struct binarytreenode*));

	/*
	 * Prints the binary tree on console.
	 * */
	void binarytree_print(struct binarytree* tree, char* spaces);

	/*
	 * Releases node instance and its data from memory.
	 */
	void binarytree_destroynode(struct binarytree* t, struct binarytreenode* node);

	/*
	 * Releases all nodes from binary tree.
	 * */
	void binarytree_clear(struct binarytree* tree);

	/*
	 * Releases all nodes and his data from memory.
	 * */
	void binarytree_destroy(struct binarytree* tree);

#endif /* BINARYTREE_H_ */
