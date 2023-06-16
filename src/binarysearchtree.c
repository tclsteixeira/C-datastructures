/*
 * binarysearchtree.c
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
 **/

#include <stdlib.h>
#include "binarytree.h"


/*
 * Function to create a new binary (search) tree.
 * Returns pointer to created binary tree instance is succeeded, NULL otherwise.
 */
struct binarytree* bst_create(void* rootdata, binarytree_cmp comparefunc, binarytree_freedata freedatafunc,
									 binarytree_printnode printnodefunc, binarytree_copydata copydatafunc)
{
	struct binarytree* result = binarytree_create(rootdata, comparefunc, freedatafunc, printnodefunc, copydatafunc);
	return result;
}

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
struct binarytreenode* bst_insert(struct binarytree* tree, struct binarytreenode* root, void* data)
{
	// If the tree is empty, return a new node
	if (root == NULL) {
		return binarytree_createnode(data);
	}
	else {
		if (tree->compare(root->data, data) > 0)
			root->left = bst_insert(tree, root->left, data);
		else if (tree->compare(root->data, data) < 0)
			root->right = bst_insert(tree, root->right, data);
		else
		{
			// Duplicate data
		}
	}

	// Return the (unchanged) node pointer
	return root;
}

/* Given a non-empty binary search
   tree, return the node
   with minimum key value found in
   that tree. Note that the
   entire tree does not need to be searched. */
struct binarytreenode* bst_minValueNode(struct binarytreenode* node)
{
	struct binarytreenode* current = node;

	/* loop down to find the leftmost leaf */
	while (current && current->left != NULL)
		current = current->left;

	return current;
}

/*
 * Releases binary tree node and its data from memory.
 * */
void bst_destroynode(struct binarytree* t, struct binarytreenode* node) {
	binarytree_destroynode(t, node);
}

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
struct binarytreenode* bst_deletenode(struct binarytree* tree, struct binarytreenode* root, void* key)
{

    // base case
    if (root == NULL)
        return root;

    // If the key to be deleted
    // is smaller than the root's
    // key, then it lies in left subtree
    if (tree->compare(root->data, key) > 0)
        root->left = bst_deletenode(tree, root->left, key);

    // If the key to be deleted
    // is greater than the root's
    // key, then it lies in right subtree
    else if (tree->compare(root->data, key) < 0)
        root->right = bst_deletenode(tree, root->right, key);

    // if key is same as root's key,
    // then This is the node
    // to be deleted
    else {
        // node with only one child or no child
        if (root->left == NULL) {
            struct binarytreenode* temp = root->right;
            root->data = NULL;
            bst_destroynode(tree, root);	// release memory
            return temp;
        }
        else if (root->right == NULL) {
            struct binarytreenode* temp = root->left;
            root->data = NULL;
            bst_destroynode(tree, root);	// release memory
            return temp;
        }

        // node with two children:
        // Get the inorder successor
        // (smallest in the right subtree)
        struct binarytreenode* temp = bst_minValueNode(root->right);

        // Copy the inorder
        // successor's content to this node
        tree->copydata(root->data, temp->data);

        // Delete the inorder successor
        root->right = bst_deletenode(tree, root->right, temp->data);
    }

    return root;
}

/*
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
struct binarytreenode* bst_delete(struct binarytree* tree, struct binarytreenode* root, void* key)
{
    // Base case
    if (root == NULL)
        return root;

    // Recursive calls for ancestors of
    // node to be deleted
    if (tree->compare(root->data, key) > 0) { //(root->key > k) {
        root->left = bst_delete(tree, root->left, key);
        return root;
    }
    else if (tree->compare(root->data, key) < 0) { //(root->key < k) {
        root->right = bst_delete(tree, root->right, key);
        return root;
    }

    // We reach here when root is the node
    // to be deleted.

    // If one of the children is empty
    if (root->left == NULL) {
        struct binarytreenode* temp = root->right;
        root->data = NULL;	// avoid to free root data from memory
        bst_destroynode(tree, root);	// release node from memory
        return temp;
    }
    else if (root->right == NULL) {
    	struct binarytreenode* temp = root->left;
    	root->data = NULL;	// avoid to free root data from memory
    	bst_destroynode(tree, root);	// release node from memory
        return temp;
    }

    // If both children exist
    else {

    	struct binarytreenode* succParent = root;

        // Find successor
    	struct binarytreenode* succ = root->right;
        while (succ->left != NULL) {
            succParent = succ;
            succ = succ->left;
        }

        // Delete successor.  Since successor
        // is always left child of its parent
        // we can safely make successor's right
        // right child as left of its parent.
        // If there is no succ, then assign
        // succ->right to succParent->right
        if (succParent != root)
            succParent->left = succ->right;
        else
            succParent->right = succ->right;

        // Copy Successor Data to root
        tree->copydata(root->data, succ->data);
        succ->data = NULL;

        // Delete Successor and return root (succ always a leaf node)
        bst_destroynode(tree, succ);
        return root;
    }
}

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
struct binarytreenode* bst_search(struct binarytree* tree, struct binarytreenode* root, const void* key)
{
	// root is NULL or found element with key, return root
	if ((root == NULL) || (tree->compare(root->data, key) == 0))
		return root;

	// Key is greater than root's key, search right sub-tree
	if (tree->compare(root->data, key) < 0)
		return bst_search(tree, root->right, key);

	// Key is lesser than root's key, search left sub-tree
	return bst_search(tree, root->left, key);
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
int bst_getSizeIt(const struct binarytree* tree)
{
	return binarytree_getSizeIt(tree);
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
int bst_treeHeightLevelOrder(struct binarytree* tree)
{
	return binarytree_treeHeightLevelOrder(tree);
}

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
int bst_findNodeDepth(struct binarytree* tree, struct binarytreenode* root, void* key)
{
	return binarytree_findNodeDepth(tree, root, key);
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
 * Time Complexity: O(N)
 * Auxiliary Space: O(1)
 */
int bst_findNodeHeight(struct binarytree* tree, struct binarytreenode* root, void* key)
{
	return binarytree_findNodeHeight(tree, root, key);
}

/*
 * Prints the binary search tree on console.
 * */
void bst_print(struct binarytree* tree, char* spaces)
{
	binarytree_print(tree, spaces);
}

/*
 * Releases all nodes from binary tree.
 * */
void bst_clear(struct binarytree* tree) {
	binarytree_clear(tree);
}

/*
 * Releases the tree and all nodes and his data from memory.
 * */
void bst_destroy(struct binarytree* tree) {
	binarytree_destroy(tree);
}

