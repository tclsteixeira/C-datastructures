/*
 * redblacktree.c
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

#include <stdlib.h>
#include "redblacktree.h"
#include "linkedlistqueue.h"
#include <stdio.h>
#include <string.h>

/*
 * Function to create a new red-black tree.
 * Returns pointer to created red-black tree instance is succeeded, NULL otherwise.
 */
struct rbtree* rbtree_create(void* rootdata, rbtree_calcdatasize calcdatasizefunc, rbtree_cmp comparefunc, rbtree_freedata freedatafunc,
		rbtree_printnode printnodefunc, rbtree_copydata copydatafunc)
{
	struct rbtree* result = (struct rbtree*)malloc(sizeof(*result));
	if (result != NULL) {
		if (rootdata != NULL)
			result->root = rbtree_createnode(NULL, rootdata);
		else
			result->root = NULL;

		if ((rootdata != NULL) && (result->root == NULL)) {
			free(result);
			result = NULL;
		}
		else {
			result->calcdatasize = calcdatasizefunc;
			result->copydata = copydatafunc;
			result->compare = comparefunc;
			result->freedata = freedatafunc;
			result->printnode = printnodefunc;
		}
	}

	return result;
}

/*
 * Function to create a new red-black tree node.
 */
struct rbtreenode* rbtree_createnode(struct rbtreenode* parent, void* data)
{
	struct rbtreenode* result = (struct rbtreenode*)malloc(sizeof(*result));
	if (result != NULL)
	{
		result->data = data;
		result->c = RB_RED;		// red by default
		result->parent = parent;
		result->left = result->right = NULL;
	}

	return result;
}

/*
 * Releases a given avl tree node and its data from memory.
 * */
void rbtree_destroynode(struct rbtree* t, struct rbtreenode* node)
{
	if ((t->freedata != NULL) && (node->data != NULL))
		t->freedata(node->data);

	node->parent = node->left = node->right = NULL;
	node->data = NULL;
	free(node);
}

/*
 * Swaps colors from two given nodes.
 */
void rbtree_swapcolors(struct rbtreenode *x1, struct rbtreenode *x2) {
    int temp;
    temp = x1->c;
    x1->c = x2->c;
    x2->c = temp;
}

/*
 * Swaps values from two given nodes.
 * Note: You can't do 'sizeof(*(u->data))' because returns always 1, so
 *  	 need callback function 'tree->calcdatasize(u->data)'
 */
void rbtree_swapvalues(struct rbtree* tree, struct rbtreenode* u, struct rbtreenode* v) {
	void* udata = (void*)malloc(tree->calcdatasize(u->data));
	tree->copydata(udata, u->data);
	tree->copydata(u->data, v->data);
	tree->copydata(v->data, udata);
	free(udata);
}

/*
 * Check if node is left child of parent.
 */
int rbtree_isOnLeft(struct rbtreenode* current) { return current == current->parent->left; }

/*
 * Returns pointer to uncle of given node.
 */
struct rbtreenode* rbtree_uncle(struct rbtreenode* current)
{
    // If no parent or grandparent, then no uncle
    if ((current->parent == NULL) || (current->parent->parent == NULL))
    	return NULL;

    if (rbtree_isOnLeft(current->parent))
    	// uncle on right
    	return current->parent->parent->right;
    else
    	// uncle on left
    	return current->parent->parent->left;
}

/*
 * Returns pointer to sibling of given node.
 */
struct rbtreenode* rbtree_sibling(struct rbtreenode* current)
{
	// sibling null if no parent
    if (current->parent == NULL)
      return NULL;

    if (rbtree_isOnLeft(current))
      return current->parent->right;

    return current->parent->left;
}

/*
 * Moves node down and moves given node in its place
 */
void rbtree_moveDown(struct rbtreenode* nParent, struct rbtreenode* current)
{
	if (current->parent != NULL) {
	  if (rbtree_isOnLeft(current)) {
		  current->parent->left = nParent;
	  } else {
		  current->parent->right = nParent;
	  }
	}
	nParent->parent = current->parent;
	current->parent = nParent;
}

/*
 * Checks if given node has a red child.
 */
int rbtree_hasRedChild(struct rbtreenode* current)
{
	return ((current->left != NULL && current->left->c == RB_RED) ||
			(current->right != NULL && current->right->c == RB_RED));
}

/*
 * Find node that do not have a left child
 * in the subtree of the given node
 */
struct rbtreenode* rbtree_successor(struct rbtreenode* x) {
	struct rbtreenode* temp = x;

	while (temp->left != NULL)
		temp = temp->left;

	return temp;
}

/*
 * Find node that replaces a deleted node in BST.
 */
struct rbtreenode* rbtree_BSTreplace(struct rbtreenode* x)
{
	// when node have 2 children
	if (x->left != NULL && x->right != NULL)
		return rbtree_successor(x->right);

	// when leaf
	if (x->left == NULL && x->right == NULL)
		return NULL;

	// when single child
	if (x->left != NULL)
		return x->left;
	else
		return x->right;
}

/*
 * Rotates temp node to the right.
 * Returns new root.
 *
 * T1, T2 and T3 are subtrees of the tree rooted with y (on left side)
 * or x (on right side)
 *                y                               x
 *               / \     Right Rotation          /  \
 *              x   T3   – - – - – - – >        T1   y
 *             / \       < - - - - - - -            / \
 *            T1  T2     Left Rotation            T2  T3
 * Keys in both of the above trees follow the following order
 *      keys(T1) < key(x) < keys(T2) < key(y) < keys(T3)
 * So BST property is not violated anywhere.
 *
 * */
struct rbtreenode* rbtree_rightrotate(struct rbtreenode* temp, struct rbtreenode* root)
{
	struct rbtreenode* result = root;
    struct rbtreenode* left = temp->left;

    temp->left = left->right;
    if (temp->left)
        temp->left->parent = temp;
    left->parent = temp->parent;
    if (!temp->parent)
        result = left;
    else if (temp == temp->parent->left)
        temp->parent->left = left;
    else
        temp->parent->right = left;
    left->right = temp;
    temp->parent = left;

    return result;
}

/*
 * Rotates temp node to the left.
 * Returns new root.
 *
 * T1, T2 and T3 are subtrees of the tree rooted with y (on left side)
 * or x (on right side)
 *                y                               x
 *               / \     Right Rotation          /  \
 *              x   T3   – - – - – - – >        T1   y
 *             / \       < - - - - - - -            / \
 *            T1  T2     Left Rotation            T2  T3
 * Keys in both of the above trees follow the following order
 *      keys(T1) < key(x) < keys(T2) < key(y) < keys(T3)
 * So BST property is not violated anywhere.
 *
 * */
struct rbtreenode* rbtree_leftrotate(struct rbtreenode* temp, struct rbtreenode* root)
{
	struct rbtreenode* result = root;
    struct rbtreenode* right = temp->right;
    temp->right = right->left;
    if (temp->right)
        temp->right->parent = temp;

    right->parent = temp->parent;
    if (!temp->parent)
        result = right;
    else if (temp == temp->parent->left)
        temp->parent->left = right;
    else
        temp->parent->right = right;
    right->left = temp;
    temp->parent = right;

    return result;
}

/*
 * Searches for given value to insertion or deletion.
 * If found returns the node (used for delete)
 * else returns the last node while traversing (used in insert)
 */
struct rbtreenode* rbtree_search_for_delete_insert(const struct rbtree* tree, const void* val)
{
	struct rbtreenode* temp = tree->root;
    while (temp != NULL) {
    	if (tree->compare(val, temp->data) < 0) {
    		if (temp->left == NULL)
    			break;	// position for insert
    		else
    			temp = temp->left;	// search left subtree
    	} else if (tree->compare(val, temp->data) == 0) {
    		break;	// found node for delete
    	} else {
    		if (temp->right == NULL)
    			break;	// position for insert
    		else
    			temp = temp->right;	// search right subtree
    	}
    }

	return temp;
}

/*
 * fix red red at given node.
 * returns root node.
 *
 * This function fixes violations
 * caused by BST insertion.
 *
 * In AVL tree insertion, we used rotation as a tool to do balancing after insertion caused imbalance.
 * In Red-Black tree, we use two tools to do balancing.
 *
 *    Recoloring
 *    Rotation
 *
 * We try recoloring first, if recoloring doesn’t work, then we go for rotation. Following is
 * detailed algorithm. The algorithms has mainly two cases depending upon the color of uncle.
 * If uncle is red, we do recoloring. If uncle is black, we do rotations and/or recoloring.
 * Color of a NULL node is considered as BLACK.
 *
 * Algorithm:
 *
 * Let x be the newly inserted node.
 *
 *    Perform standard BST insertion and make the colour of newly inserted nodes as RED.
 *    If x is the root, change the colour of x as BLACK (Black height of complete tree
 *    increases by 1).
 *    Do the following if the color of x’s parent is not BLACK and x is not the root.
 *    a) If x’s uncle is RED (Grandparent must have been black from property 4)
 *    	(i) Change the colour of parent and uncle as BLACK.
 *    	(ii) Colour of a grandparent as RED.
 *    	(iii) Change x = x’s grandparent, repeat steps 2 and 3 for new x.
 *
 *    b) If x’s uncle is BLACK, then there can be four configurations for x, x’s parent (p)
 *    and x’s grandparent (g) (This is similar to AVL Tree)
 *    	(i) Left Left Case (p is left child of g and x is left child of p)
 *    	(ii) Left Right Case (p is left child of g and x is the right child of p)
 *    	(iii) Right Right Case (Mirror of case i)
 *    	(iv) Right Left Case (Mirror of case ii)
 *
 * Re-coloring after rotations:
 * 	For Left Left Case [3.b (i)] and Right Right case [3.b (iii)], swap colors of grandparent
 * 	and parent after rotations
 * 	For Left Right Case [3.b (ii)]and Right Left Case [3.b (iv)], swap colors of grandparent
 * 	and inserted node after rotations
 *
 * Time Complexity:  O(log n), as the height of red-black tree is O(log n) at most, and
 * 					 complexity of rotation is constant.
 * Auxiliary Space:  O(n),  here ‘n’ is the number of nodes in the red-black trees.
 *
 * Source: https://www.geeksforgeeks.org/c-program-red-black-tree-insertion/
 */
struct rbtreenode* rbtree_fixRedRed(struct rbtreenode* root, struct rbtreenode* x)
{
    // if x is root color it black and return
    if (x == root) {
    	x->c = RB_BLACK;
    	return root;
    }

    // initialize parent, grandparent, uncle
    struct rbtreenode* parent = x->parent;
    struct rbtreenode* grandparent = parent->parent;
    struct rbtreenode* uncle = rbtree_uncle(x);

    if (parent->c != RB_BLACK) {
    	if (uncle != NULL && uncle->c == RB_RED) {
    		// uncle red, perform recoloring and recurse
    		parent->c = RB_BLACK;
    		uncle->c = RB_BLACK;
    		grandparent->c = RB_RED;
    		root = rbtree_fixRedRed(root, grandparent);
    	} else {
    		// Else perform LR, LL, RL, RR
    		if (rbtree_isOnLeft(parent)) {
    			if (rbtree_isOnLeft(x)) {
    				// for left right
    				rbtree_swapcolors(parent, grandparent);
    			} else {
    				root = rbtree_leftrotate(parent, root);
    				rbtree_swapcolors(x, grandparent);
    			}
    			// for left left and left right
    			root = rbtree_rightrotate(grandparent, root);
    		} else {
    			if (rbtree_isOnLeft(x)) {
    				// for right left
    				root = rbtree_rightrotate(parent, root);
    				rbtree_swapcolors(x, grandparent);
    			} else {
    				rbtree_swapcolors(parent, grandparent);
    			}

    			// for right right and right left
    			root = rbtree_leftrotate(grandparent, root);
    		}
    	}
    }

    return root;
}

/*
 * Inserts the given value to tree.
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
 * 	and inserted node after rotations
 *
 * Time complexity: O(log N)
 * Space complecity: O(N)
 *
 * 	where N is the total number of nodes in the tree.
 *
 * Source: https://www.geeksforgeeks.org/insertion-in-red-black-tree/
 *
 */
struct rbtreenode* rbtree_insert(struct rbtree* tree, void* data)
{
	struct rbtreenode* root = tree->root;
    struct rbtreenode* newNode = rbtree_createnode(NULL, data);
    if (root == NULL) {
    	// when root is null
    	// simply insert value at root
    	newNode->c = RB_BLACK;
    	root = newNode;
    } else {
    	struct rbtreenode* temp = rbtree_search_for_delete_insert(tree, data);

    	if (tree->compare(temp->data, data) == 0) {
    		// return if value already exists
    		return root;
    	}

    	// if value is not found, search returns the node
    	// where the value is to be inserted

    	// connect new node to correct node
    	newNode->parent = temp;

    	if (tree->compare(temp->data, data) > 0)
    		temp->left = newNode;
    	else
    		temp->right = newNode;

    	// fix red red violation if exists
    	root = rbtree_fixRedRed(root, newNode);
    }

    return root;
}

///*
// * Function to perform BST insertion of a node.
// */
//struct rbtreenode* rbtree_bstinsert(struct rbtree* tree, struct rbtreenode* trav,
//		struct rbtreenode* newnode)	//struct rbtreenode* temp)
//{
//    // If the tree is empty,
//    // return a new node
//    if (trav == NULL)
//    	return newnode;
//
//    // Otherwise recur down the tree
//    if (tree->compare(newnode->data, trav->data) < 0)	// (temp->d < trav->d)
//    {
//        trav->left = rbtree_bstinsert(tree, trav->left, newnode);
//        trav->left->parent = trav;
//    }
//    else if (tree->compare(newnode->data, trav->data) > 0)	// (temp->d > trav->d)
//    {
//        trav->right = rbtree_bstinsert(tree, trav->right, newnode);
//        trav->right->parent = trav;
//    }
//
//    // Return the (unchanged) node pointer
//    return trav;
//}

///*
// * This function fixes violations
// * caused by BST insertion.
// *
// * In AVL tree insertion, we used rotation as a tool to do balancing after insertion caused imbalance.
// * In Red-Black tree, we use two tools to do balancing.
// *
// *    Recoloring
// *    Rotation
// *
// * We try recoloring first, if recoloring doesn’t work, then we go for rotation. Following is
// * detailed algorithm. The algorithms has mainly two cases depending upon the color of uncle.
// * If uncle is red, we do recoloring. If uncle is black, we do rotations and/or recoloring.
// * Color of a NULL node is considered as BLACK.
// *
// * Algorithm:
// *
// * Let x be the newly inserted node.
// *
// *    Perform standard BST insertion and make the colour of newly inserted nodes as RED.
// *    If x is the root, change the colour of x as BLACK (Black height of complete tree
// *    increases by 1).
// *    Do the following if the color of x’s parent is not BLACK and x is not the root.
// *    a) If x’s uncle is RED (Grandparent must have been black from property 4)
// *    	(i) Change the colour of parent and uncle as BLACK.
// *    	(ii) Colour of a grandparent as RED.
// *    	(iii) Change x = x’s grandparent, repeat steps 2 and 3 for new x.
// *
// *    b) If x’s uncle is BLACK, then there can be four configurations for x, x’s parent (p)
// *    and x’s grandparent (g) (This is similar to AVL Tree)
// *    	(i) Left Left Case (p is left child of g and x is left child of p)
// *    	(ii) Left Right Case (p is left child of g and x is the right child of p)
// *    	(iii) Right Right Case (Mirror of case i)
// *    	(iv) Right Left Case (Mirror of case ii)
// *
// * Re-coloring after rotations:
// * 	For Left Left Case [3.b (i)] and Right Right case [3.b (iii)], swap colors of grandparent
// * 	and parent after rotations
// * 	For Left Right Case [3.b (ii)]and Right Left Case [3.b (iv)], swap colors of grandparent
// * 	and inserted node after rotations
// *
// * Time Complexity:  O(log n), as the height of red-black tree is O(log n) at most, and
// * 					 complexity of rotation is constant.
// * Auxiliary Space:  O(n),  here ‘n’ is the number of nodes in the red-black trees.
// *
// * Source: https://www.geeksforgeeks.org/c-program-red-black-tree-insertion/
// *
// * */
//struct rbtreenode* rbtree_fixup(struct rbtreenode* root, struct rbtreenode* pt)
//{
//    struct rbtreenode* parent_pt = NULL;
//    struct rbtreenode* grand_parent_pt = NULL;
//
//    while ((pt != root) && (pt->c != RB_BLACK)
//           && (pt->parent->c == RB_RED))
//    {
//        parent_pt = pt->parent;
//        grand_parent_pt = pt->parent->parent;
//
//        /*  Case : A
//             Parent of pt is left child
//             of Grand-parent of
//           pt */
//        if (parent_pt == grand_parent_pt->left)
//        {
//            struct rbtreenode* uncle_pt = grand_parent_pt->right;
//
//            /* Case : 1
//                The uncle of pt is also red
//                Only Recoloring required */
//            if (uncle_pt != NULL && uncle_pt->c == RB_RED)
//            {
//                grand_parent_pt->c = RB_RED;
//                parent_pt->c = RB_BLACK;
//                uncle_pt->c = RB_BLACK;
//                pt = grand_parent_pt;
//            }
//
//            else {
//
//                /* Case : 2
//                     pt is right child of its parent
//                     Left-rotation required */
//                if (pt == parent_pt->right) {
//                    root = rbtree_leftrotate(parent_pt, root);
//                    pt = parent_pt;
//                    parent_pt = pt->parent;
//                }
//
//                /* Case : 3
//                     pt is left child of its parent
//                     Right-rotation required */
//                root = rbtree_rightrotate(grand_parent_pt, root);
//                int t = parent_pt->c;
//                parent_pt->c = grand_parent_pt->c;
//                grand_parent_pt->c = t;
//                pt = parent_pt;
//            }
//        }
//
//        /* Case : B
//             Parent of pt is right
//             child of Grand-parent of
//           pt */
//        else {
//            struct rbtreenode* uncle_pt = grand_parent_pt->left;
//
//            /*  Case : 1
//                The uncle of pt is also red
//                Only Recoloring required */
//            if ((uncle_pt != NULL) && (uncle_pt->c == RB_RED))
//            {
//                grand_parent_pt->c = RB_RED;
//                parent_pt->c = RB_BLACK;
//                uncle_pt->c = RB_BLACK;
//                pt = grand_parent_pt;
//            }
//            else {
//                /* Case : 2
//                   pt is left child of its parent
//                   Right-rotation required */
//                if (pt == parent_pt->left) {
//                    root = rbtree_rightrotate(parent_pt, root);
//                    pt = parent_pt;
//                    parent_pt = pt->parent;
//                }
//
//                /* Case : 3
//                     pt is right child of its parent
//                     Left-rotation required */
//                root = rbtree_leftrotate(grand_parent_pt, root);
//                int t = parent_pt->c;
//                parent_pt->c = grand_parent_pt->c;
//                grand_parent_pt->c = t;
//                pt = parent_pt;
//            }
//        }
//    }
//
//    return root;
//}

///*
// * Inserts a new node in the tree.
// * Returns root node if succeeded.
// * */
//struct rbtreenode* rbtree_insert(struct rbtree* tree, void* data)
//{
//	struct rbtreenode* root = tree->root;
//	struct rbtreenode* newnode = rbtree_createnode(NULL, data);
//	root = rbtree_bstinsert(tree, root, newnode);
//	root = rbtree_fixup(root, newnode);
//	root->c = RB_BLACK;
//	return root;
//}

/*
 * Fixes double-black violation in red-black tree after deletion.
 * Returns root node.
 *
 *  Do following while the current node u is double black, and it is not the root.
 * 	Let sibling of node be s.
 *
 * .….(a): If sibling s is black and at least one of sibling’s children is red, perform
 * 		rotation(s). Let the red child of s be r. This case can be divided in four subcases
 * 		depending upon positions of s and r.
 *
 * …………..(i) Left Left Case (s is left child of its parent and r is left child of s or both
 * 			children of s are red). This is mirror of right right case shown in below diagram.
 * …………..(ii) Left Right Case (s is left child of its parent and r is right child). This is
 * 			mirror of right left case shown in below diagram.
 * …………..(iii) Right Right Case (s is right child of its parent and r is right child of s or
 * 			both children of s are red)
 * …………..(iv) Right Left Case (s is right child of its parent and r is left child of s)
 *
 * …..(b): If sibling is black and its both children are black, perform recoloring, and
 * 		recur for the parent if parent is black.
 *
 * …..(c): If sibling is red, perform a rotation to move old sibling up, recolor the old
 * 		sibling and parent. The new sibling is always black (See the below diagram).
 * 		This mainly converts the tree to black sibling case (by rotation) and leads to case
 * 		(a) or (b). This case can be divided in two subcases.
 *
 * 	…………..(i) Left Case (s is left child of its parent). This is mirror of right right
 * 			case shown in below diagram. We right rotate the parent p.
 * 	…………..(ii) Right Case (s is right child of its parent). We left rotate the parent p.
 *
 * For more references see delete.
 *
 */
struct rbtreenode* rbtree_fixDoubleBlack(struct rbtreenode* root, struct rbtreenode* x)
{
	if (x == root)
		// Reached root
		return root;

    struct rbtreenode* sibling = rbtree_sibling(x);
    struct rbtreenode* parent = x->parent;

    if (sibling == NULL) {
    	// No sibling, double black pushed up
    	root = rbtree_fixDoubleBlack(root, parent);
    } else {
    	if (sibling->c == RB_RED) {
    		// Sibling red
    		parent->c = RB_RED;
    		sibling->c = RB_BLACK;

    		if (rbtree_isOnLeft(sibling)) {
    			// left case
    			root = rbtree_rightrotate(parent, root);
    		} else {
    			// right case
    			root = rbtree_leftrotate(parent, root);
    		}

    		root = rbtree_fixDoubleBlack(root, x);
    	} else {
    		// Sibling black
    		if (rbtree_hasRedChild(sibling)) {
    			// at least 1 red children
    			if (sibling->left != NULL && sibling->left->c == RB_RED) {
    				if (rbtree_isOnLeft(sibling)) {
    					// left left
    					sibling->left->c = sibling->c;
    					sibling->c = parent->c;
    					root = rbtree_rightrotate(parent, root);
    				} else {
    					// right left
    					sibling->left->c = parent->c;
    					root = rbtree_rightrotate(sibling, root);
    					root = rbtree_leftrotate(parent, root);
    				}
    			} else {
    				if (rbtree_isOnLeft(sibling)) {
    					// left right
    					sibling->right->c = parent->c;
    					root = rbtree_leftrotate(sibling, root);
    					root = rbtree_rightrotate(parent, root);
    				} else {
    					// right right
    					sibling->right->c = sibling->c;
    					sibling->c = parent->c;
    					root = rbtree_leftrotate(parent, root);
    				}
    			}

    			parent->c = RB_BLACK;
    		} else {
    			// 2 black children
    			sibling->c = RB_RED;
    			if (parent->c == RB_BLACK)
    				root = rbtree_fixDoubleBlack(root, parent);
    			else
    				parent->c = RB_BLACK;
    		}
    	}
    }

    return root;
}

/*
 * Deletes the given node
 * Returns root node.
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
struct rbtreenode* rbtree_deletenode(struct rbtree* tree, struct rbtreenode* v)
{
	struct rbtreenode* root = tree->root;
	struct rbtreenode* u = rbtree_BSTreplace(v);

	// True when u and v are both black
	int uvBlack = ((u == NULL || u->c == RB_BLACK) && (v->c == RB_BLACK));
	struct rbtreenode* parent = v->parent;

	if (u == NULL)
	{
		// u is NULL therefore v is leaf
		if (v == root) {
			// v is root, making root null
			root = NULL;
		} else {
			if (uvBlack) {
				// u and v both black
				// v is leaf, fix double black at v
				root = rbtree_fixDoubleBlack(root, v);
			} else {
				// u or v is red
				if (rbtree_sibling(v) != NULL)
					// sibling is not null, make it red"
					rbtree_sibling(v)->c = RB_RED;
			}

			// delete v from the tree
			if (rbtree_isOnLeft(v)) {
				parent->left = NULL;
			} else {
				parent->right = NULL;
			}
		}

		rbtree_destroynode(tree, v);
		return root;
	}

	if (v->left == NULL || v->right == NULL) {
		// v has 1 child
		if (v == root) {
			// v is root, assign the value of u to v, and delete u
			tree->copydata(v, u);
			//v->val = u->val;
			v->left = v->right = NULL; v->parent = NULL;
			rbtree_destroynode(tree, u);
		} else {
			// Detach v from tree and move u up
			if (rbtree_isOnLeft(v)) {
				parent->left = u;
			} else {
				parent->right = u;
			}

			rbtree_destroynode(tree, v);
			u->parent = parent;

			if (uvBlack) {
				// u and v both black, fix double black at u
				root = rbtree_fixDoubleBlack(root, u);
			} else {
				// u or v red, color u black
				u->c = RB_BLACK;
			}
		}

		return root;
	}

    // v has 2 children, swap values with successor and recurse
    rbtree_swapvalues(tree, u, v);
    root = rbtree_deletenode(tree, u);

    return root;
}

/*
 * Utility function that deletes the node with given value.
 * Returns root node.
 *
 * See rbtree_deletenode(struct rbtree* tree, struct rbtreenode* v)
 *
 * */
struct rbtreenode* rbtree_delete(struct rbtree* tree, const void* val, int* success)
{
	*success = 1;
	struct rbtreenode* root = tree->root;
	if (root == NULL)
		// Tree is empty
		return root;

	struct rbtreenode* v = rbtree_search_for_delete_insert(tree, val);

    if (tree->compare(v->data, val) != 0) {
    	*success = 0;
    	printf("No node found to delete!");
    	return root;
    }

    root = rbtree_deletenode(tree, v);
    return root;
}

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
struct rbtreenode* rbtree_search(struct rbtree* tree, struct rbtreenode* root, const void* key)
{
	// root is NULL or found element with key, return root
	if ((root == NULL) || (tree->compare(root->data, key) == 0))
		return root;

	// Key is greater than root's key, search right sub-tree
	if (tree->compare(root->data, key) < 0)
		return rbtree_search(tree, root->right, key);

	// Key is lesser than root's key, search left sub-tree
	return rbtree_search(tree, root->left, key);
}

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
int rbtree_treeHeightLevelOrder(struct rbtree* tree)
{
    // Initialising a variable to count the
    // height of tree
    int depth = 0;
    struct rbtreenode* root = tree->root;
    if (!root)
    	return -1;

    struct linkedlistqueue* q = linkedlistqueue_create();
    linkedlistqueue_enqueue(q, root);
    linkedlistqueue_enqueue(q, NULL);

    while (!linkedlistqueue_isempty(q)) {
    	struct rbtreenode* temp = linkedlistqueue_peekfront(q);
    	linkedlistqueue_dequeue(q);

        // When NULL encountered, increment the value
        if (temp == NULL) {
            depth++;
        }

        // If NULL not encountered, keep moving
        if (temp != NULL) {
            if (temp->left) {
            	linkedlistqueue_enqueue(q, temp->left);
            }
            if (temp->right) {
            	linkedlistqueue_enqueue(q, temp->right);
            }
        }

        // If queue still have elements left,
        // push NULL again to the queue.
        else if (!linkedlistqueue_isempty(q)) {
        	linkedlistqueue_enqueue(q, NULL);
        }
    }

    if (q != NULL)
    	linkedlistqueue_destroy(q);

    return depth - 1;
}

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
int rbtree_getSizeIt(const struct rbtree* tree)
{
	struct rbtreenode* root = tree->root;
    // if tree is empty it will
    // return 0
    if(root == NULL)
        return 0;

    // Using level order Traversal.
    struct linkedlistqueue* q = linkedlistqueue_create();
    int count = 1;

    linkedlistqueue_enqueue(q, root);

    while (!linkedlistqueue_isempty(q))
    {
        struct rbtreenode *temp = linkedlistqueue_peekfront(q);

        if(temp->left)
        {
            // Enqueue left child
        	linkedlistqueue_enqueue(q, temp->left);

            // Increment count
            count++;
        }

        if(temp->right)
        {
            // Enqueue right child
        	linkedlistqueue_enqueue(q, temp->right);

            // Increment count
            count++;
        }

        linkedlistqueue_dequeue(q);
    }

    linkedlistqueue_destroy(q);
    return count;
}

/*
 * Function to find the depth of a given node with given key in a red-black Tree.
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
int rbtree_findNodeDepth(struct rbtree* tree,  struct rbtreenode* root, void* key)
{
//	struct rbtreenode* root = tree->root;
	// Base case
	if (root == NULL)
		return -1;

	// Initialize distance as -1
	int dist = -1;

	// Check if x is current node=
	if ((tree->compare(root->data, key) == 0)

		// Otherwise, check if x is
		// present in the left subtree
		|| (dist = rbtree_findNodeDepth(tree, root->left, key)) >= 0

		// Otherwise, check if x is
		// present in the right subtree
		|| (dist = rbtree_findNodeDepth(tree, root->right, key)) >= 0)

		// Return depth of the node
		return dist + 1;

	return dist;
}

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
int rbtree_findNodeHeight(struct rbtree* tree, void* key)
{
	/*
	 * Helper function to find the height
	 * of a given node in the binary tree.
	 */
	int findHeightUtil(struct rbtree* tree, struct rbtreenode* root, void* key,
					   int* height)
	{
		// Base Case
		if (root == NULL) {
			return -1;
		}

		// Store the maximum height of
		// the left and right subtree
		int leftHeight = findHeightUtil(
			tree, root->left, key, height);

		int rightHeight
			= findHeightUtil(
				tree, root->right, key, height);

		// Update height of the current node
		int ans = ((leftHeight > rightHeight) ? leftHeight : rightHeight) + 1;

		// If current node is the required node
		if (tree->compare(root->data, key) == 0)
			*height = ans;

		return ans;
	}


	// Store the height of
	// the given node
	int* hp = malloc(sizeof(int));
	*hp = -1;

	// Stores height of the Tree in 'hp'
	findHeightUtil(tree, tree->root, key, hp);

	int result = *hp;
	free(hp);

	// Return the height
	return result;
}

/*
 * Prints tree nodes data.
 * */
void rbtree_print(struct rbtree* tree, char* spaces) {

	int getcol(int h) {
	    if (h == 1)
	        return 1;
	    return getcol(h - 1) + getcol(h - 1) + 1;
	}

	/*
	 * Computes an integer raised to a power integer.
	 * */
	int intpow(int base, int power) {
		int result = 1;
		for (int i = 0; i < power; ++i) {
			result *= base;
		}

		return result;
	}

	/*
	 * Applies a tree preorder traversal to store tree nodes in a matrix.
	 * */
	void printTree( int x, int y, struct rbtreenode* M[x][y], struct rbtreenode *root, int col, int row, int height,
					char* spaces) {
	    if (root == NULL)
	        return;
	    M[row][col] = root;
	    printTree(x, y, M, root->left, col - intpow(2, height - 2), row + 1, height - 1, spaces);
	    printTree(x, y, M, root->right, col + intpow(2, height - 2), row + 1, height - 1, spaces);
	}

    int h = rbtree_treeHeightLevelOrder(tree) + 1;//  findHeightMorrisTrav(tree->root);
    int col = getcol(h);

    if (strlen(spaces) == 0) spaces = " ";

    int hslen = strlen(spaces);
    char hs[hslen];

	for (int i = 0; i < hslen; ++i) {
			hs[i] = ' ';
	}

    // avoid print trash
    if (hslen > 0)
    	hs[hslen-1] = '\0';

    struct rbtreenode* M[h][col];

    for (int row = 0; row < h; ++row) {
    	for (int co = 0; co < col; ++co) {
    		M[row][co] = NULL;
    	}
	}

    printTree(h, col, M, tree->root, col / 2, 0, h, spaces);
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < col; j++) {
        	if ((M[i][j] == NULL) || (M[i][j]->data == NULL))
        		printf(spaces);
        	else
        	{
        		tree->printnode(M[i][j]);
        		printf(hs);
        	}
        }

        printf("\n");
    }
}

/*
 * Releases all tree nodes and associated data from memory.
 * Uses postorder traversal.
 * Note: Private function.
 * */
void rbtree_deallocate(struct rbtree* tree, struct rbtreenode* root) {
	if (root == NULL)
		return;

	rbtree_deallocate(tree, root->left);
	rbtree_deallocate(tree, root->right);

	rbtree_destroynode(tree, root);
}

/*
 * Releases all nodes and their data from tree.
 * */
void rbtree_clear(struct rbtree* tree)
{
	rbtree_deallocate(tree, tree->root);
}

/*
 * Releases all nodes, his data, and the tree structure instance from memory.
 * */
void rbtree_destroy(struct rbtree* tree)
{
	rbtree_clear(tree);
	free(tree);
}


