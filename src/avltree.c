/*
 * avltree.c
 *
 *  Created on: 30/05/2023
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
 *    The tree balances itself when a new node is inserted or deleted. Therefore, the
 *    insertion and deletion operations are time-consuming.
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

#include <stdlib.h>
#include <stdio.h>
#include "avltree.h"
#include <string.h>
#include "linkedlistqueue.h"

// A utility function to get height of the tree
int height(struct avltreenode *n)
{
    if (n == NULL)
        return 0;

    return n->height;
}

// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}


/*
 * Function to create a new avl tree.
 * Returns pointer to created avl tree instance is succeeded, NULL otherwise.
 */
struct avltree* avltree_create(void* rootdata, avltree_cmp comparefunc, avltree_freedata freedatafunc,
		avltree_printnode printnodefunc, avltree_copydata copydatafunc)
{
	struct avltree* result = (struct avltree*)malloc(sizeof(*result));
	if (result != NULL) {
		result->root = avltree_createnode(rootdata);

		if (result->root == NULL) {
			free(result);
			result = NULL;
		}
		else {
			result->copydata = copydatafunc;
			result->compare = comparefunc;
			result->freedata = freedatafunc;
			result->printnode = printnodefunc;
		}
	}

	return result;
}

/*
 * Function to create a new avl tree node.
 */
struct avltreenode* avltree_createnode(void* data)
{
	struct avltreenode* result = (struct avltreenode*)malloc(sizeof(*result));
	if (result != NULL)
	{
		result->data = data;
		result->height = 1;
		result->left = result->right = NULL;
	}

	return result;
}

/*
 * A utility function to right rotate subtree rooted with y
 * See the diagram given above.
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
 */
struct avltreenode* rightrotate(struct avltreenode *y)
{
    struct avltreenode *x = y->left;
    struct avltreenode *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    // Return new root
    return x;
}

/*
 * A utility function to left rotate subtree rooted with x.
 * See the diagram given above.
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
 */
struct avltreenode *leftrotate(struct avltreenode *x)
{
	struct avltreenode *y = x->right;
	struct avltreenode *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left),
                    height(x->right)) + 1;
    y->height = max(height(y->left),
                    height(y->right)) + 1;

    // Return new root
    return y;
}

/*
 * Get balance factor of a given node N.
 */
int getbalance(struct avltreenode *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

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
struct avltreenode* avltree_insert(struct avltree* tree, struct avltreenode* node, void* data)
{
	/* 1. Perform the normal BST insertion */
	if (node == NULL)
		return avltree_createnode(data);

	if (tree->compare(node->data, data) > 0)
		node->left = avltree_insert(tree, node->left, data);
	else if (tree->compare(node->data, data) < 0)
		node->right = avltree_insert(tree, node->right, data);
	else // Equal keys are not allowed in BST
		return node;

	/* 2. Update height of this ancestor node */
	node->height = 1 + max(height(node->left),
						height(node->right));

	/* 3. Get the balance factor of this ancestor
		node to check whether this node became
		unbalanced */
	int balance = getbalance(node);

	// If this node becomes unbalanced, then
	// there are 4 cases

	// Left Left Case
	if (balance > 1 && tree->compare(node->left->data, data) > 0)
		return rightrotate(node);

	// Right Right Case
	if (balance < -1 && tree->compare(node->right->data, data) < 0)
		return leftrotate(node);

	// Left Right Case
	if (balance > 1 && tree->compare(node->left->data, data) < 0)
	{
		node->left = leftrotate(node->left);
		return rightrotate(node);
	}

	// Right Left Case
	if (balance < -1 && tree->compare(node->right->data, data) > 0)
	{
		node->right = rightrotate(node->right);
		return leftrotate(node);
	}

	/* return the (unchanged) node pointer */
	return node;
}

/*
 * Releases a given avl tree node and its data from memory.
 * */
void avltree_destroynode(struct avltree* t, struct avltreenode* node)
{
	if ((t->freedata != NULL) && (node->data != NULL))
		t->freedata(node->data);

	free(node);
}

/*
 * Given a non-empty binary search tree,
 * return the node with minimum key value
 * found in that tree. Note that the entire
 * tree does not need to be searched.
 * */
struct avltreenode * minvaluenode(struct avltreenode* node)
{
	struct avltreenode* current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}

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
struct avltreenode* avltree_delete(struct avltree* tree,  struct avltreenode* root, void* key)
{
	// STEP 1: PERFORM STANDARD BST DELETE

	if (root == NULL)
		return root;

	// If the key to be deleted is smaller than the
	// root's key, then it lies in left subtree
	if (tree->compare(root->data, key) > 0)
		root->left = avltree_delete(tree, root->left, key);

	// If the key to be deleted is greater than the
	// root's key, then it lies in right subtree
	else if (tree->compare(root->data, key) < 0)
		root->right = avltree_delete(tree, root->right, key);

	// if key is same as root's key, then This is
	// the node to be deleted
	else
	{
		// node with only one child or no child
		if( (root->left == NULL) || (root->right == NULL) )
		{
			struct avltreenode *temp = root->left ? root->left :
											 root->right;

			// No child case
			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else // One child case
				*root = *temp; 	// Copy the contents of
								// the non-empty child
			temp->data = NULL;	// release pointer data
			avltree_destroynode(tree, temp);	// do not release data from memory
		}
		else
		{
			// node with two children: Get the inorder
			// successor (smallest in the right subtree)
			struct avltreenode* temp = minvaluenode(root->right);

			// Copy the inorder successor's data to this node
			tree->copydata(root->data, temp->data);

			// Delete the inorder successor
			root->right = avltree_delete(tree, root->right, temp->data);
		}
	}

	// If the tree had only one node then return
	if (root == NULL)
	  return root;

	// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
	root->height = 1 + max(height(root->left),
						   height(root->right));

	// STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
	// check whether this node became unbalanced)
	int balance = getbalance(root);

	// If this node becomes unbalanced, then there are 4 cases

	// Left Left Case
	if (balance > 1 && getbalance(root->left) >= 0)
		return rightrotate(root);

	// Left Right Case
	if (balance > 1 && getbalance(root->left) < 0)
	{
		root->left = leftrotate(root->left);
		return rightrotate(root);
	}

	// Right Right Case
	if (balance < -1 && getbalance(root->right) <= 0)
		return leftrotate(root);

	// Right Left Case
	if (balance < -1 && getbalance(root->right) > 0)
	{
		root->right = rightrotate(root->right);
		return leftrotate(root);
	}

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
struct avltreenode* avltree_search(struct avltree* tree, struct avltreenode* root, const void* key)
{
	// root is NULL or found element with key, return root
	if ((root == NULL) || (tree->compare(root->data, key) == 0))
		return root;

	// Key is greater than root's key, search right sub-tree
	if (tree->compare(root->data, key) < 0)
		return avltree_search(tree, root->right, key);

	// Key is lesser than root's key, search left sub-tree
	return avltree_search(tree, root->left, key);
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
int avltree_treeHeightLevelOrder(struct avltree* tree)
{
    // Initialising a variable to count the
    // height of tree
    int depth = 0;
    struct avltreenode* root = tree->root;
    if (!root)
    	return -1;

    struct linkedlistqueue* q = linkedlistqueue_create();
    linkedlistqueue_enqueue(q, root);
    linkedlistqueue_enqueue(q, NULL);

    while (!linkedlistqueue_isempty(q)) {
    	struct avltreenode* temp = linkedlistqueue_peekfront(q);
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
int avltree_getSizeIt(const struct avltree* tree)
{
	struct avltreenode* root = tree->root;
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
        struct avltreenode *temp = linkedlistqueue_peekfront(q);

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
int avltree_findNodeDepth(struct avltree* tree, void* key)
{
    // Base case
    if (tree->root == NULL)
        return -1;

    struct avltreenode* temp = avltree_search(tree, tree->root, key);
    if (temp) {
    	return tree->root->height - temp->height;
    }
    else
    	return -1;
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
int avltree_findNodeHeight(struct avltree* tree, void* key)
{
	// Base case
	if (tree->root == NULL)
		return -1;

	struct avltreenode* temp = avltree_search(tree, tree->root, key);
	if (temp) {
		return temp->height - 1;
	}
	else
		return -1;
}

/*
 * Prints tree nodes data.
 * */
void avltree_print(struct avltree* tree, char* spaces) {

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
	void printTree( int x, int y, struct avltreenode* M[x][y], struct avltreenode *root, int col, int row, int height,
					char* spaces) {
	    if (root == NULL)
	        return;
	    M[row][col] = root;
	    printTree(x, y, M, root->left, col - intpow(2, height - 2), row + 1, height - 1, spaces);
	    printTree(x, y, M, root->right, col + intpow(2, height - 2), row + 1, height - 1, spaces);
	}

    int h = avltree_treeHeightLevelOrder(tree) + 1;//  findHeightMorrisTrav(tree->root);
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

    struct avltreenode* M[h][col];

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
void avltree_deallocate(struct avltree* tree, struct avltreenode* root) {
	if (root == NULL)
		return;

	avltree_deallocate(tree, root->left);
	avltree_deallocate(tree, root->right);

	avltree_destroynode(tree, root);
}

/*
 * Releases all nodes and their data from avl tree.
 * */
void avltree_clear(struct avltree* tree)
{
	avltree_deallocate(tree, tree->root);
}

/*
 * Releases all nodes, his data, and the avl tree structure instance from memory.
 * */
void avltree_destroy(struct avltree* tree)
{
	avltree_clear(tree);
	free(tree);
}


