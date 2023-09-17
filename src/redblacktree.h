/*
 * redblacktree.h
 *
 *  Created on: 19/06/2023
 *      Author: Tiago C. Teixeira
 * Description: C implementation of a red-black tree data structure.
 *
 * When it comes to searching and sorting data, one of the most fundamental data structures
 * is the binary search tree. However, the performance of a binary search tree is highly
 * dependent on its shape, and in the worst case, it can degenerate into a linear structure
 * with a time complexity of O(n). This is where Red Black Trees come in, they are a type of
 * balanced binary search tree that use a specific set of rules to ensure that the tree is
 * always balanced. This balance guarantees that the time complexity for operations such as
 * insertion, deletion, and searching is always O(log n), regardless of the initial shape of
 * the tree.
 *
 * Red Black Trees are self-balancing, meaning that the tree adjusts itself automatically
 * after each insertion or deletion operation. It uses a simple but powerful mechanism to
 * maintain balance, by coloring each node in the tree either red or black.
 *
 * Red Black Tree-
 *
 * Red-Black tree is a binary search tree in which every node is colored with either red or
 * black. It is a type of self balancing binary search tree. It has a good efficient worst
 * case running time complexity.
 *
 * Properties of Red Black Tree:
 *
 * The Red-Black tree satisfies all the properties of binary search tree in addition to
 * that it satisfies following additional properties –
 *
 * 1. Root property: The root is black.
 *
 * 2. External property: Every leaf (Leaf is a NULL child of a node) is black in Red-Black tree.
 *
 * 3. Internal property: The children of a red node are black. Hence possible parent of red node
 * 	is a black node.
 *
 * 4. Depth property: All the leaves have the same black depth.
 *
 * 5. Path property: Every simple path from root to descendant leaf node contains same number
 *  of black nodes.
 *
 * The result of all these above-mentioned properties is that the Red-Black tree is roughly
 * balanced.
 * Rules That Every Red-Black Tree Follows:
 *
 *    Every node has a color either red or black.
 *    The root of the tree is always black.
 *    There are no two adjacent red nodes (A red node cannot have a red parent or red child).
 *    Every path from a node (including root) to any of its descendants NULL nodes has the same
 *    number of black nodes.
 *    Every leaf (e.i. NULL node) must be colored BLACK.
 *
 * Why Red-Black Trees?
 *
 * Most of the BST operations (e.g., search, max, min, insert, delete.. etc) take O(h) time
 * where h is the height of the BST. The cost of these operations may become O(n) for a
 * skewed Binary tree. If we make sure that the height of the tree remains O(log n) after
 * every insertion and deletion, then we can guarantee an upper bound of O(log n) for all
 * these operations. The height of a Red-Black tree is always O(log n) where n is the number
 * of nodes in the tree.
 *
 * Sr. No.	Algorithm	Time Complexity
 * 1.	Search	O(log n)
 * 2.	Insert	O(log n)
 * 3.	Delete	O(log n)
 *
 * “n” is the total number of elements in the red-black tree.
 *
 * Comparison with AVL Tree:
 *
 * 	The AVL trees are more balanced compared to Red-Black Trees, but they may cause more
 * 	rotations during insertion and deletion. So if your application involves frequent
 * 	insertions and deletions, then Red-Black trees should be preferred. And if the insertions
 * 	and deletions are less frequent and search is a more frequent operation, then AVL tree
 * 	should be preferred over the Red-Black Tree.
 *
 * Interesting points about Red-Black Tree:
 *
 *    The black height of the red-black tree is the number of black nodes on a path from the
 *    root node to a leaf node. Leaf nodes are also counted as black nodes. So, a red-black
 *    tree of height h has black height >= h/2.
 *    Height of a red-black tree with n nodes is h<= 2 log2(n + 1).
 *    All leaves (NIL) are black.
 *    The black depth of a node is defined as the number of black nodes from the root to that
 *    node i.e the number of black ancestors.
 *    Every red-black tree is a special case of a binary tree.
 *
 * Black Height of a Red-Black Tree :
 *
 * 	Black height is the number of black nodes on a path from the root to a leaf. Leaf nodes
 * 	are also counted black nodes. From the above properties 3 and 4, we can derive, a
 * 	Red-Black Tree of height h has black-height >= h/2.
 *
 *  Number of nodes from a node to its farthest descendant leaf is no more than twice as the
 *  number of nodes to the nearest descendant leaf.
 *
 * Every Red Black Tree with n nodes has height <= 2Log2(n+1)
 * This can be proved using the following facts:
 *
 *    For a general Binary Tree, let k be the minimum number of nodes on all root to NULL
 *    paths, then n >= 2k – 1 (Ex. If k is 3, then n is at least 7). This expression can
 *    also be written as k <= Log2(n+1).
 *    From property 4 of Red-Black trees and above claim, we can say in a Red-Black Tree
 *    with n nodes, there is a root to leaf path with at-most Log2(n+1) black nodes.
 *    From properties 3 and 5 of Red-Black trees, we can claim that the number of black
 *    nodes in a Red-Black tree is at least ⌊ n/2 ⌋ where n is the total number of nodes.
 *
 * 	From the above points, we can conclude the fact that Red Black Tree with n nodes has a
 * 	height <= 2Log2(n+1)
 *
 * Source: https://www.geeksforgeeks.org/introduction-to-red-black-tree/
 *
 */

#ifndef REDBLACKTREE_H_
	#define REDBLACKTREE_H_

	#define RB_BLACK 0	// black node
	#define RB_RED 1	// red node

	// red black tree node
	struct rbtreenode {
		int c;	// color: 1-red or 0-black
		void* data;
		struct rbtreenode* parent;
		struct rbtreenode* left;
		struct rbtreenode* right;
	};

	// callback function to (hard) copy data from one tree node to another
	typedef size_t (*rbtree_calcdatasize)(const void* data);
	typedef void (*rbtree_copydata)(void* dest, const void* from);
	typedef int (*rbtree_cmp)(const void* data1, const void* data2);
	typedef void (*rbtree_freedata)(void* data);
	typedef void (*rbtree_printdata)(const void* data);
//	typedef void (*rbtree_printnode)(struct rbtreenode* node);


		struct rbtree {
			struct rbtreenode* root;
			rbtree_calcdatasize calcdatasize; // function to calculate size of data in bytes
			rbtree_copydata copydata;	// (hard) copy data function from one node to another
			rbtree_cmp compare;			// compare function (returns 0, 1 or -1)
			rbtree_freedata freedata;	// function to release data from memory.
			rbtree_printdata printdata;	// function to print node's data

//			rbtree_printnode printnode;	// function to print data node
		};

		/*
		 * Function to create a new red black tree.
		 * Returns pointer to created red black tree instance is succeeded, NULL otherwise.
		 */
		struct rbtree* rbtree_create(void* rootdata, rbtree_calcdatasize calcdatasizefunc,
				rbtree_cmp comparefunc, rbtree_freedata freedatafunc,
				rbtree_printdata printdatafunc, rbtree_copydata copydatafunc);

		/*
		 * Function to create a new red black tree node.
		 */
		struct rbtreenode* rbtree_createnode(struct rbtreenode* parent, void* data);

		/*
		 * Inserts the given value to tree.
		 * Returns '1' (true) if succeeded, '0' (false) otherwise.
		 *
		 * Algorithm:
		 *
		 * Let x be the newly inserted node.
		 *
		 *    Perform standard BST insertion and make the colour of newly inserted nodes as RED.
		 *    If x is the root, change the colour of x as BLACK (Black height of complete tree
		 *    increases by 1).
		 *    Do the following if the color of x’s parent is not BLACK and x is not the root.
		 *
		 *    	a) If x’s uncle is RED (Grandparent must have been black from property 4)
		 *    		(i) Change the colour of parent and uncle as BLACK.
		 *    		(ii) Colour of a grandparent as RED.
		 *    		(iii) Change x = x’s grandparent, repeat steps 2 and 3 for new x.
		 *
		 *    	b) If x’s uncle is BLACK, then there can be four configurations for x, x’s parent (p) and x’s grandparent (g) (This is similar to AVL Tree)
		 *    		(i) Left Left Case (p is left child of g and x is left child of p)
		 *    		(ii) Left Right Case (p is left child of g and x is the right child of p)
		 *    		(iii) Right Right Case (Mirror of case i)
		 *    		(iv) Right Left Case (Mirror of case ii)
		 *
		 *
		 * Re-coloring after rotations:
		 *
		 * 	For Left Left Case [3.b (i)] and Right Right case [3.b (iii)], swap colors of grandparent
		 * 	and parent after rotations
		 * 	For Left Right Case [3.b (ii)]and Right Left Case [3.b (iv)], swap colors of grandparent
		 * 	and inserted node after rotations.
		 *
		 * Time complexity: O(log N)
		 * Space complexity: O(N)
		 *
		 * 	where N is the total number of nodes in the tree.
		 *
		 * Source: https://www.geeksforgeeks.org/insertion-in-red-black-tree/
		 *
		 */
		int rbtree_insert(struct rbtree* tree, void* data);

		/*
		 * Deletes the given node
		 * Returns deleted node data if succeeded, NULL otherwise.
		 *
		 * Like Insertion, recoloring and rotations are used to maintain the Red-Black properties.
		 * In the insert operation, we check the color of the uncle to decide the appropriate case.
		 * In the delete operation, we check the color of the sibling to decide the appropriate case.
		 * The main property that violates after insertion is two consecutive reds. In delete, the
		 * main violated property is, change of black height in subtrees as deletion of a black node
		 * may cause reduced black height in one root to leaf path.
		 * To understand deletion, the notion of double black is used. When a black node is deleted
		 * and replaced by a black child, the child is marked as double black. The main task now
		 * becomes to convert this double black to single black.
		 *
		 * Deletion Steps
		 *
		 * Following are detailed steps for deletion.
		 * 1) Perform standard BST delete. When we perform standard delete operation in BST, we
		 * 	always end up deleting a node which is an either leaf or has only one child (For an
		 * 	internal node, we copy the successor and then recursively call delete for successor,
		 * 	successor is always a leaf node or a node with one child). So we only need to handle
		 * 	cases where a node is leaf or has one child. Let v be the node to be deleted and u be
		 * 	the child that replaces v (Note that u is NULL when v is a leaf and color of NULL is
		 * 	considered as Black).
		 *
		 * 2) Simple Case: If either u or v is red, we mark the replaced child as black
		 * 	(No change in black height). Note that both u and v cannot be red as v is parent of u
		 * 	and two consecutive reds are not allowed in red-black tree.
		 *
		 * 3) If Both u and v are Black.
		 * 	3.1) Color u as double black.  Now our task reduces to convert this double black to
		 * 		single black. Note that If v is leaf, then u is NULL and color of NULL is considered
		 * 		black. So the deletion of a black leaf also causes a double black.
		 *
		 * 	3.2) Do following while the current node u is double black, and it is not the root.
		 * 		Let sibling of node be s.
		 *
		 * .….(a): If sibling s is black and at least one of sibling’s children is red, perform
		 * 		rotation(s). Let the red child of s be r. This case can be divided in four subcases
		 * 		depending upon positions of s and r.
		 * 		(see rbtree_fixDoubleBlack comments)
		 *
		 * …..(b): If sibling is black and its both children are black, perform recoloring, and
		 * 		recur for the parent if parent is black.
		 * 		In this case, if parent was red, then we didn’t need to recur for parent, we can simply
		 * 		make it black (red + double black = single black)
		 *
		 * …..(c): If sibling is red, perform a rotation to move old sibling up, recolor the old
		 * 		sibling and parent. The new sibling is always black (See the below diagram).
		 * 		This mainly converts the tree to black sibling case (by rotation) and leads to case
		 * 		(a) or (b). This case can be divided in two subcases.
		 * 	…………..(i) Left Case (s is left child of its parent). This is mirror of right right
		 * 			case shown in below diagram. We right rotate the parent p.
		 * 	…………..(ii) Right Case (s is right child of its parent). We left rotate the parent p.
		 *
		 * 3.3) If u is root, make it single black and return (Black height of complete tree reduces
		 * 		by 1).
		 *
		 * Time complexity: O(log N)
		 * Space complecity: O(N)
		 *
		 * 	where N is the total number of nodes in the tree.
		 *
		 * Source: https://www.geeksforgeeks.org/deletion-in-red-black-tree/
		 *
		 */
		void* rbtree_delete(struct rbtree* tree, const void* val);	//, int* success);
//		struct rbtreenode* rbtree_delete(struct rbtree* tree, struct rbtreenode* v);

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
		struct rbtreenode* rbtree_search(struct rbtree* tree, struct rbtreenode* root, const void* key);

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
		int rbtree_getSizeIt(const struct rbtree* tree);

		/*
		 * Function to find the depth of a given node with given key in a binary Tree.
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
		int rbtree_findNodeDepth(struct rbtree* tree, struct rbtreenode* root, void* key);

		/*
		 * Function to find the height of a given node in a binary tree
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
		int rbtree_findNodeHeight(struct rbtree* tree, void* key);

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
		int rbtree_treeHeightLevelOrder(struct rbtree* tree);

		/*
		 * Prints tree nodes data.
		 * */
		void rbtree_print(struct rbtree* tree, char* spaces);

		/*
		 * Releases all nodes and data instance from red-black tree.
		 * */
		void rbtree_clear(struct rbtree* tree);

		/*
		 * Releases all nodes, his data, and the red-black tree structure instance from memory.
		 * */
		void rbtree_destroy(struct rbtree* tree);


#endif /* REDBLACKTREE_H_ */
