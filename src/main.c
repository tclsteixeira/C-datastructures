/*
 * main.c
 *
 *  Created on: 23/02/2023
 *      Author: Tiago C. Teixeira
 */

#include <stdio.h>

#include "arraylist.h"
#include "binarysearch.h"
#include "circdbllinkedlist.h"
#include "circlinkedlist.h"
#include "hashtable.h"
#include "linkedlist.h"
#include "dbllinkedlist.h"
#include "linkedlistqueue.h"
#include "linkedliststack.h"
#include "binarytree.h"
#include "binarysearchtree.h"
#include "avltree.h"

/*
 * AVL tree demo.
 * */
void avltree_demo() {

	/*
	 * Function to compare key with given data.
	 * Returns 1 if data > key, -1 if data < key, 0 if is equal.
	 * */
	int compare(void* data, const void* key) {

		if ((data == NULL) && (key == NULL))
			return 0;
		else if (data == NULL)
			return -1;
		else if (key == NULL)
			return 1;
		else {
			//struct binarytreenode* datanode = (struct binarytreenode*)data;
			int idata = *((int*)(data));
			int ikey = *((int*)key);

			if (idata == ikey)
				return 0;
			else if (idata > ikey)
				return 1;
			else
				return -1;
		}
	}

	/*
	 * Prints node data
	 * */
	void printnode(struct avltreenode* node) {
		if (node) {
			void* data = node->data;
			if (data) {
				printf("%d", *((int*)data));
			}
		}
	}

	/*
	 * (hard) copy data from source to dest
	 * */
	void copydata(void* dest, const void* from) {
		if (dest) {
			if (from) {
				*((int*)dest) = *((int*)from);
			}
		}
	}

	printf("___________\n");
	printf("AVL TREE\n");
	printf("\nAVL TREE demo -----------\n\n");

	int intdata[] = {1,2,3,4,5,6,7};
	int n = sizeof(intdata) / sizeof(intdata[0]);

	// put '3' as root
	struct avltree* tree = avltree_create(&intdata[0], compare, NULL,
			printnode, copydata);

	printf("AVL tree created successfully with root = '%d'\n", *((int*)(tree->root->data)));
	printf("Tree size: %d\n\n", avltree_getSizeIt(tree));
	printf("Build avl tree with elements in the following order:\n");

	for (int i = 0; i < n-1; ++i) {
		printf("'%d' ", intdata[i]);
	}

	printf("\n\n");

	tree->root = avltree_insert(tree, tree->root, &intdata[1]);	// 2
	tree->root = avltree_insert(tree, tree->root, &intdata[2]);	// 3
	tree->root = avltree_insert(tree, tree->root, &intdata[3]);	// 4
	tree->root = avltree_insert(tree, tree->root, &intdata[4]);	// 5
	tree->root = avltree_insert(tree, tree->root, &intdata[5]);	// 6

	printf("Print tree:\n\n");
	avltree_print(tree, "  ");
	printf("\n");
	/*
	 *           4
	 *		  2     5
	 * 	    1   3     6
	 *
	 * */

	printf("Tree size (iterative alg): %d\n", avltree_getSizeIt(tree));

	// search '1'
	int* intp = &intdata[0];
	printf("Search value '%d': ", *intp);
	struct avltreenode* n0 = avltree_search(tree, tree->root, intp);
	if (n0 != NULL)
		printf("Found value '%d'.\n", *((int*)(n0->data)));
	else
		printf("Not found :(?\n");

	// printf("Tree deep using rec alg (max number of edges from root to deepest leaf node): %d\n", bst_findNode(tree->root));
	printf("Height of tree (max number of edges from deepest leaf node to root node): ");
	printf("%d\n\n", avltree_treeHeightLevelOrder(tree));

	// root has depth 0
	printf("Node '%d' depth: %d\n", *((int*)(tree->root->data)),
			avltree_findNodeDepth(tree, tree->root->data));
	// '5' node has depth 1
	printf("Node '%d' depth: %d\n", intdata[4], avltree_findNodeDepth(tree, (void*)(&intdata[4])));
	// '6' node has depth 2
	printf("Node '%d' depth: %d\n", intdata[5], avltree_findNodeDepth(tree, (void*)(&intdata[5])));
	// root has height 2
	printf("Node '%d' height: %d\n", *((int*)(tree->root->data)),
			avltree_findNodeHeight(tree, tree->root->data));
	// '5' node has height 1
	printf("Node '%d' height: %d\n", intdata[4],
			avltree_findNodeHeight(tree, (void*)(&intdata[4])));
	// '6' node has height 0
	printf("Node '%d' height: %d\n\n", intdata[5],
			avltree_findNodeHeight(tree, (void*)(&intdata[5])));


	// delete '4' node
	int n3 = intdata[3];
	printf("Delete node '%d'\n", n3);
	tree->root = avltree_delete(tree, tree->root, (void*)(&intdata[3]));
	printf("Print tree:\n\n");
	avltree_print(tree, "  ");
	printf("\n");
	/*
	 *           5
	 *		  2     6
	 * 	    1   3
	 *
	 * */

	// delete '5' node
	printf("Delete node '%d'\n", *((int*)(&intdata[4])));
	tree->root = avltree_delete(tree, tree->root, (void*)(&intdata[4]));
	printf("Print tree:\n\n");
	avltree_print(tree, "  ");
	printf("\n");
	/*
	 *           3
	 *		  2     6
	 * 	    1
	 *
	 * */

	// Bug in Morris alg (wrong results in unbalanced trees)
    //	printf("Morris alg, height= %d\n\n", binarytree_findHeightMorrisTrav(tree->root));// findHeightMorrisTrav(tree->root));

	printf("Tree size (iterative alg): %d\n", avltree_getSizeIt(tree));

	avltree_destroy(tree);
	printf("AVL tree destroyed successfully.\n\n");
}

/*
 * Binary search tree demo.
 * */
void bst_demo() {

	/*
	 * Function to compare key with given data.
	 * Returns 1 if data > key, -1 if data < key, 0 if is equal.
	 * */
	int compare(void* data, const void* key) {

		if ((data == NULL) && (key == NULL))
			return 0;
		else if (data == NULL)
			return -1;
		else if (key == NULL)
			return 1;
		else {
			//struct binarytreenode* datanode = (struct binarytreenode*)data;
			int idata = *((int*)(data));
			int ikey = *((int*)key);

			if (idata == ikey)
				return 0;
			else if (idata > ikey)
				return 1;
			else
				return -1;
		}
	}

	/*
	 * Prints node data
	 * */
	void printnode(struct binarytreenode* node) {
		if (node) {
			void* data = node->data;
			if (data) {
				printf("%d", *((int*)data));
			}
		}
	}

	/*
	 * (hard) copy data from source to dest
	 * */
	void copydata(void* dest, const void* from) {
		if (dest) {
			if (from) {
				*((int*)dest) = *((int*)from);
			}
		}
	}

	printf("___________\n");
	printf("BINARY SEARCH TREE\n");
	printf("\nBINARY SEARCH TREE demo -----------\n\n");

	int intdata[] = {1,2,3,4,5,6,7};
	int n = sizeof(intdata) / sizeof(intdata[0]);

	// put '3' as root
	struct binarytree* tree = bst_create(&intdata[2], compare, NULL,
			printnode, copydata);

	printf("Binary search tree created successfully with root = '%d'\n", *((int*)(tree->root->data)));
	printf("Tree size: %d\n\n", bst_getSizeIt(tree));
	printf("Build search tree with elements:\n");

	for (int i = 0; i < n-1; ++i) {
		if (i == 2) continue;
		printf("'%d' ", intdata[i]);
	}

	printf("\n\n");

	//bst_insert(tree, tree->root, &intdata[2]);		// 3
	bst_insert(tree, tree->root, &intdata[1]);	// 2
	bst_insert(tree, tree->root, &intdata[0]);	// 1
	bst_insert(tree, tree->root, &intdata[4]);	// 5
	bst_insert(tree, tree->root, &intdata[3]);	// 4
	bst_insert(tree, tree->root, &intdata[5]);	// 6

	printf("Print tree:\n\n");
	bst_print(tree, "  ");
	printf("\n");
	/*
	 *           3
	 *		  2     5
	 * 	    1     4   6
	 *
	 * */

	printf("Tree size (iterative alg): %d\n", bst_getSizeIt(tree));

	// search '1'
	int* intp = &intdata[0];
	printf("Search value '%d': ", *intp);
	struct binarytreenode* n0 = bst_search(tree, tree->root, intp);
	if (n0 != NULL)
		printf("Found value '%d'.\n", *((int*)(n0->data)));
	else
		printf("Not found :(?\n");

	// printf("Tree deep using rec alg (max number of edges from root to deepest leaf node): %d\n", bst_findNode(tree->root));
	printf("Height of tree (max number of edges from deepest leaf node to root node): ");
	printf("%d\n\n", bst_treeHeightLevelOrder(tree));// findHeightMorrisTrav(tree->root));

	// root has depth 0
	printf("Node '%d' depth: %d\n", *((int*)(tree->root->data)), bst_findNodeDepth(tree, tree->root, tree->root->data));
	// '4' node has depth 2
	printf("Node '%d' depth: %d\n", intdata[3], bst_findNodeDepth(tree, tree->root, (void*)(&intdata[3])));
	// root has height 2
	printf("Node '%d' height: %d\n", *((int*)(tree->root->data)), bst_findNodeHeight(tree, tree->root, tree->root->data));
	// '5' node has height 0
	printf("Node '%d' height: %d\n\n", intdata[4], bst_findNodeHeight(tree, tree->root, (void*)(&intdata[4])));

	// delete '4' node
	int n3 = intdata[3];
	printf("Delete node '%d'\n", n3);

	// important: delete returns root node because if root were deleted, a new root must be set
	tree->root = bst_delete(tree, tree->root, (void*)(&intdata[3]));

	printf("Print tree:\n\n");
	bst_print(tree, "  ");
	printf("\n");
	/*
	 *           3
	 *		  2     5
	 * 	    1         6
	 *
	 * */

	// delete '5' node
	printf("Delete node '%d'\n", *((int*)(&intdata[4])));

	// important: delete returns root node because if root were deleted, a new root must be set
	tree->root = bst_delete(tree, tree->root, (void*)(&intdata[4]));
	printf("Print tree:\n\n");
	bst_print(tree, "  ");
	printf("\n");
	/*
	 *           3
	 *		  2     6
	 * 	    1
	 *
	 * */

	// Bug in Morris alg (wrong results in unbalanced trees)
    //	printf("Morris alg, height= %d\n\n", binarytree_findHeightMorrisTrav(tree->root));// findHeightMorrisTrav(tree->root));

	printf("Tree size (iterative alg): %d\n", bst_getSizeIt(tree));

	bst_destroy(tree);
	printf("Binary search tree destroyed successfully.\n\n");
}

/*
 * Binary tree demo.
 * */
void binarytree_demo() {

	/*
	 * Function to compare key with given data.
	 * Returns 1 if data > key, -1 if data < key, 0 if is equal.
	 * */
	int compare(void* data, const void* key) {

		if ((data == NULL) && (key == NULL))
			return 0;
		else if (data == NULL)
			return -1;
		else if (key == NULL)
			return 1;
		else {
			//struct binarytreenode* datanode = (struct binarytreenode*)data;
			int idata = *((int*)(data));
			int ikey = *((int*)key);

			if (idata == ikey)
				return 0;
			else if (idata > ikey)
				return 1;
			else
				return -1;
		}
	}

	/*
	 * Prints node data
	 * */
	void printnode(struct binarytreenode* node) {
		if (node) {
			void* data = node->data;
			if (data) {
				printf("%d", *((int*)data));
			}
		}
	}

	/*
	 * (hard) copy data from source to dest
	 * */
	void copydata(void* dest, const void* from) {
		if (dest) {
			if (from) {
				*((int*)dest) = *((int*)from);
			}
		}
	}

	printf("___________\n");
	printf("BINARY TREE\n");
	printf("\nBINARY TREE demo -----------\n\n");

	int intdata[] = {1,2,3,4,5,6,7};
	int n = sizeof(intdata) / sizeof(intdata[0]);

	struct binarytree* tree = binarytree_create(&intdata[0], compare, NULL,
			printnode, copydata);

	printf("Binary tree created successfully with root = '%d'\n", *((int*)(tree->root->data)));

	printf("Tree size: %d\n\n", binarytree_getSize(tree->root));

	printf("Build tree with elements:\n");

	for (int i = 0; i < n-2; ++i) {
		printf("'%d' ", intdata[i]);
	}

	printf("\n\n");

	// build tree
	struct binarytreenode* root = tree->root;
	struct binarytreenode* node1 = binarytree_createnode(&intdata[1]);
	struct binarytreenode* node2 = binarytree_createnode(&intdata[2]);
	struct binarytreenode* node3 = binarytree_createnode(&intdata[3]);
	struct binarytreenode* node4 = binarytree_createnode(&intdata[4]);
//	struct binarytreenode* node5 = binarytree_createnode(&intdata[5]);
//	struct binarytreenode* node6 = binarytree_createnode(&intdata[6]);

	struct binarytreenode* delnode3 = binarytree_createnode(&intdata[3]);
	struct binarytreenode* delnode4 = binarytree_createnode(&intdata[4]);

	root->left = node1;
	root->right = node2;

	node1->left = node3;
	node1->right = node4;

//	node2->left = node5;
//	node2->right = node6;

	printf("Print tree:\n\n");
	binarytree_print(tree, "  ");
	printf("\n");
	/*
	 *           1
	 *		  2     3
	 * 	    4   5 6   7
	 *
	 * */

	printf("Tree size (iterative alg): %d\n", binarytree_getSizeIt(tree));

	int* intp = &intdata[4];
	printf("Search value '%d': ", *intp);
	struct binarytreenode* n5 = binarytree_search(tree, tree->root, intp);
	if (n5 != NULL)
		printf("Found value '%d'.\n", *((int*)(n5->data)));
	else
		printf("Not found :(?\n");

	printf("Tree deep using rec alg (max number of edges from root to deepest leaf node): %d\n", binarytree_treeDepth(tree->root));
	printf("Height of tree (max number of edges from deepest leaf node to root node): ");
	printf("%d\n\n", binarytree_treeHeightLevelOrder(tree));// findHeightMorrisTrav(tree->root));

	printf("Node '%d' depth: %d\n", 1, binarytree_findNodeDepth(tree, tree->root, tree->root->data));
	printf("Node '%d' depth: %d\n", 5, binarytree_findNodeDepth(tree, tree->root, node4->data));
	printf("Node '%d' height: %d\n", 1, binarytree_findNodeHeight(tree, tree->root, tree->root->data));
	printf("Node '%d' height: %d\n\n", 5, binarytree_findNodeHeight(tree, tree->root, node4->data));


	int n3 = *((int*)(delnode3->data));
	printf("Delete node '%d'\n", n3);

	// important: delete returns root node because if root were deleted, a new root must be set
	tree->root = binarytree_delete(tree, delnode3->data);
	printf("Print tree:\n\n");
	binarytree_print(tree, "  ");
	printf("\n");
	/*
	 *           1
	 *		  2     6
	 * 	    4   5     7
	 *
	 * */

	printf("Delete node '%d'\n", *((int*)(delnode4->data)));

	// important: delete returns root node because if root were deleted, a new root must be set
	tree->root = binarytree_delete(tree, delnode4->data);
	printf("Print tree:\n\n");
	binarytree_print(tree, "  ");
	printf("\n");
	/*
	 *           1
	 *		  2     6
	 * 	        5     7
	 *
	 * */

	// Bug in Morris alg (wrong results in unbalanced trees)
    //	printf("Morris alg, height= %d\n\n", binarytree_findHeightMorrisTrav(tree->root));// findHeightMorrisTrav(tree->root));

	printf("Tree size (iterative alg): %d\n", binarytree_getSizeIt(tree));

	binarytree_destroy(tree);
	printf("Binary tree destroyed successfully.\n\n");

	// clean up
	free(delnode3);
	free(delnode4);
}

/*
 * Linked list queue demo.
 * */
void linkedlistqueue_demo() {
	printf("___________\n");
	printf("LINKED LIST QUEUE\n");
	printf("\nLINKED LIST QUEUE demo -----------\n\n");

	int intdata[] = {1,2,3,4,5,6,7};
	int n = sizeof(intdata) / sizeof(intdata[0]);

	struct linkedlistqueue* queue = linkedlistqueue_create(7);

	printf("Size: %d\n\n", linkedlistqueue_getsize(queue));

	for (int i = 0; i < n; ++i) {
		linkedlistqueue_enqueue(queue, &intdata[i]);
	    printf("Enqueue value at rear '%d':\n", intdata[i]);
	}

	printf("Size: %d\n\n", linkedlistqueue_getsize(queue));

	//peek queue front
	printf("Queue front: %d\n", *((int*)linkedlistqueue_peekfront(queue)));

	//peek queue rear
	printf("Queue rear: %d\n", *((int*)linkedlistqueue_peekrear(queue)));
	printf("\n");

	//Dequeue
	printf("Dequeue: %d\n", *((int*)linkedlistqueue_dequeue(queue)));

	//Dequeue
	printf("Dequeue: %d\n", *((int*)linkedlistqueue_dequeue(queue)));
	printf("\n");

	//peek queue front
	printf("Queue front: %d\n", *((int*)linkedlistqueue_peekfront(queue)));


	int x = 50;
	int* new_data = &x;

	//Enqueue 50
	if (linkedlistqueue_enqueue(queue, new_data))
		printf("Enqueue value '%d'\n", *((int*)linkedlistqueue_peekrear(queue)));
	else
		printf("Fail enqueue!\n");

	printf("\n");

	printf("Size: %d\n\n", linkedlistqueue_getsize(queue));

	//peek queue front
	printf("Queue front: %d\n", *((int*)linkedlistqueue_peekfront(queue)));

	//peek queue rear
	printf("Queue rear: %d\n", *((int*)linkedlistqueue_peekrear(queue)));
	printf("\n");

	linkedlistqueue_destroy(queue);
	printf("Linked list queue destroyed successfully.\n");
}

/*
 * Linked list stack demo.
 * */
void linkedliststack_demo() {
	printf("___________\n");
	printf("LINKED LIST STACK\n");
	printf("\nLINKED LIST STACK demo -----------\n\n");

	int intdata[] = {1,2,3,4,5,6,7};
	int n = sizeof(intdata) / sizeof(intdata[0]);

	struct linkedliststack* stack = linkedliststack_create();

	printf("Size: %d\n\n", linkedliststack_size(stack));

	for (int i = 0; i < n; ++i) {
		linkedliststack_push(stack, &intdata[i]);
	    printf("Inserted value at top '%d':\n", intdata[i]);
	}

	printf("Size: %d\n\n", linkedliststack_size(stack));

	// print array
	printf("Stack top: %d\n", *((int*)linkedliststack_peek(stack)));
	printf("\n");

	// Pop top element
	printf("Pop stack:\n");
	void* el = linkedliststack_pop(stack);
	if (el != NULL) {
		printf("Pop element '%d' successfully!\n", *((int*)el));
		printf("Size: %d\n\n", linkedliststack_size(stack));
	}
	else {
		printf("Fail to pop from stack!\n\n");
	}

	// Pop all elements
	while (el != NULL) {
		el = linkedliststack_pop(stack);
	}

	printf("All elements popped from stack.\n");
	printf("Size: %d\n", linkedliststack_size(stack));

	linkedliststack_destroy(stack);
	printf("\nLinked list stack destroyed successfully.\n");
}

/*
 * Arraylist demo.
 * */
void arraylist_demo() {

	/*
	 * Prints array of ints
	 * */
	void print_arraylist(struct arraylist* a) {
		for (int i = 0; i < a->length; ++i) {
			printf("%d ", *((int*)arraylist_get_item_at(a, i)));
		}
	}

	printf("___________\n");
	printf("ARRAYLIST\n");
	printf("\nARRAYLIST demo -----------\n\n");


	int intdata[] = {1,2,3,4,5,6,7};
	int n = sizeof(intdata) / sizeof(intdata[0]);

	struct arraylist* alist = arraylist_create_capacity(6);

	printf("Capacity: %d\n", alist->capacity);
	printf("Length: %d\n\n", alist->length);

	for (int i = 0; i < n; ++i) {
	    arraylist_add(alist, &intdata[i]);
	    printf("Inserted value at end '%d':\n", intdata[i]);
	}

	printf("\nCapacity: %d\n", alist->capacity);
	printf("Length: %d\n\n", alist->length);

	// print array
	printf("Print arraylist:\n");
	print_arraylist(alist);
	printf("\n\n");

	printf("Remove first item:\n");
	void* el = arraylist_remove_at(alist, 0);
	if (el != NULL) printf("Item '%d' removed successfully!\n", *((int*)el));

	printf("\nRemove last item:\n");
	el = arraylist_remove_at(alist, alist->length-1);
	if (el != NULL) printf("Item '%d' removed successfully!\n", *((int*)el));

	printf("\nCapacity: %d\n", alist->capacity);
	printf("Length: %d\n\n", alist->length);

	printf("Shrink to fit.\n");
	if (!arraylist_shrink_to_fit(alist))
		printf("Failed to shrink array list!\n");
	else
	{
		printf("Capacity: %d\n", alist->capacity);
		printf("Length: %d\n", alist->length);
	}

	// print array
	printf("\nPrint arraylist:\n");
	print_arraylist(alist);
	printf("\n");

	arraylist_destroy(alist);
	printf("\nArraylist destroyed successfully.\n");
}


/*
 * Binary search demo.
 * */
void binarysearch_demo() {

	/*
	 * Prints array of ints
	 * */
	void print_array(void* arr[], int n) {
		for (int i = 0; i < n; ++i) {
			printf("%d ", *((int*)arr[i]));
		}
	}

	/*
	 * Compares to elements.
	 * Returns 1 if a > b, -1 if a < b, 0 if a = b.
	 * */
	int compare(void* a, void* b) {
		int v1 = *((int*)a);
		int v2 = *((int*)b);
		if (v1 > v2) return 1;
		else if (v1 < v2) return -1;
		else return 0;
	}

	printf("___________\n");
	printf("BINARY SEARCH\n");
	printf("\nBinary search demo -----------\n\n");

	int sortarr[8] = {0,10,20,30,40,50,60,70};
	int n = sizeof(sortarr) / sizeof(sortarr[0]);
	void* data[n];// = malloc(n * sizeof(void*));
	for (int i = 0; i < n; ++i) {
		data[i] = &sortarr[i];
	}

	printf("Print sorted data:\n");
	print_array(data, n);
	printf("\n");

	// search values list
	int svalues[] = {0, 10, 20, 34, 70};
	int nvals = sizeof(svalues) / sizeof(svalues[0]);

	for (int i = 0; i < nvals; ++i) {
		printf("\nSearch position of '%d':", svalues[i]);
		int pos = binarySearch(data, 0, n, &svalues[i], compare);

		if (pos < 0)
			printf(" Element not found!");
		else
			printf(" Position %d", pos);
	}

	printf("\n\n----------------\n");
}

/*
 * Circular double linked list demo.
 * */
void circdoublelinklist_demo() {

	/*
	 * Print list data.
	 * Note: Assumes data stores pointer to integer value.
	 * */
	void print_list(struct circdbllinkedlist* list, uint num_nodes) {
		struct circdbllinkedlistnode* node = circdbllinkedlist_getstart(list);
		if (node == NULL)
		{
			printf("Can not print empty list!\n");
			return;
		}

		// print forward
		for (int i = 0; i < num_nodes; ++i) {
			if (node->data == NULL)
				printf("-- ");
			else
				printf("%d ", *((int*)(node->data)));

			node = node->next;
		}

		node = node->prev;

		// print backward
		for (int i = num_nodes; i > 0; --i) {
			if (node->data == NULL)
				printf("-- ");
			else
				printf("%d ", *((int*)(node->data)));

			node = node->prev;
		}

		printf("\n");
	}

	/*
	 * Checks for equality
	 * */
	int isequal(const void* a, const void* b) {
		if (*(int*)a == *(int*)b)
			return 1;
		else
			return 0;
	}

	struct circdbllinkedlist* list = circdbllinkedlist_create(isequal);

	int data[] = {1,2,3,4};
	int n = sizeof(data) / sizeof(data[0]);

	printf("___________\n");
	printf("CIRCULAR DOUBLE LINKED LIST\n");

	printf("\nCircular double linked list demo -----------\n\n");

	for(int i = 0; i != n; ++i) {
		circdbllinkedlist_insert_at_begin(list, &data[i]);
		printf("Insert at start value '%d'.\n", data[i]);
	}

	int num_nodes = 8;

	printf("\nPrint list %d nodes (forward and reserve):\n", num_nodes);
	print_list(list, num_nodes);


/*
	printf("\nGet data at position %d: ", 0);
	int* vp0 = (int*)(dbllinkedlist_getdata_at(list, 0));
	printf("%d", *vp0);

	printf("\nGet data at position %d: ", 3);
	int v3 = *((int*)(dbllinkedlist_getdata_at(list, 3)));
	printf("%d\n", v3);

*/

	printf("\nRemove first node\n");
	struct circdbllinkedlistnode* rnode = circdbllinkedlist_remove_first(list);

	if (rnode != NULL) {
		printf("Node removed successfully\n");
		free(rnode);
	}

	printf("\nPrint list %d nodes (forward and reverse):\n", num_nodes);
	print_list(list, num_nodes);

	// free resources
	circdbllinkedlist_destroy(list);
	printf("\nCircular double linked list destroyed successfully.\n");
}


/*
 * Double linked list demo.
 * */
void doublelinklist_demo() {

	/*
	 * Print list data
	 * */
	void print_list(struct dbllinkedlist* list) {
		struct dbllinkedlistnode* node = dbllinkedlist_getfirst(list);

		// print forward
		while (node != NULL) {
			if (node->data == NULL)
				printf("-- ");
			else
				printf("%d ", *((int*)(node->data)));

			node = node->next;
		}

		node = dbllinkedlist_getlast(list);

		// print reverse
		while (node != NULL) {
			if (node->data == NULL)
				printf("-- ");
			else
				printf("%d ", *((int*)(node->data)));

			node = node->prev;
		}

		printf("\n");
	}

	/*
	 * Checks for equality
	 * */
	int isequal(const void* a, const void* b) {
		if (*(int*)a == *(int*)b)
			return 1;
		else
			return 0;
	}

	struct dbllinkedlist* list = dbllinkedlist_create(isequal);

	int data[] = {1,2,3,4};
	int n = sizeof(data) / sizeof(data[0]);

	printf("___________\n");
	printf("DOUBLE LINKED LIST\n");

	printf("\nDouble linked list demo -----------\n\n");

	for(int i = 0; i != n; ++i) {
		dbllinkedlist_insert_at_begin(list, &data[i]);
		printf("Insert at start value '%d'.\n", data[i]);
	}

	printf("\nPrint list (forward aand reserve):\n");
	print_list(list);

	printf("\nGet data at position %d: ", 0);
	int* vp0 = (int*)(dbllinkedlist_getdata_at(list, 0));
	printf("%d", *vp0);

	printf("\nGet data at position %d: ", 3);
	int v3 = *((int*)(dbllinkedlist_getdata_at(list, 3)));
	printf("%d\n", v3);

	printf("\nRemove first node\n");
	struct dbllinkedlistnode* rnode = dbllinkedlist_remove(list, (void*)vp0);

	if (rnode != NULL) {
		printf("Node removed successfully\n");
		free(rnode);
	}

	printf("\nPrint list (forward and reverse):\n");
	print_list(list);

	// free resources
	dbllinkedlist_destroy(list);
	printf("\nDouble linked list destroyed successfully.\n");
}

/*
 * Linked list demo.
 * */
void singlelinklist_demo() {

	/*
	 * Print list data
	 * */
	void print_list(struct linkedlist* list) {
		struct linkedlistnode* node = linkedlist_getfirst(list);

		while (node != NULL) {
			if (node->data == NULL)
				printf("-- ");
			else
				printf("%d ", *((int*)(node->data)));

			node = node->next;
		}

		printf("\n");
	}

	/*
	 * Checks for equality
	 * */
	int isequal(const void* a, const void* b) {
		if (*(int*)a == *(int*)b)
			return 1;
		else
			return 0;
	}

	struct linkedlist* list = linkedlist_create(isequal);

	int data[] = {1,2,3,4};
	int n = sizeof(data) / sizeof(data[0]);

	printf("___________\n");
	printf("LINKED LIST\n");

	printf("\nSingle linked list demo -----------\n\n");

	for(int i = 0; i != n; ++i) {
		linkedlist_push(list, &data[i]);
		printf("Insert at start value '%d'.\n", data[i]);
	}

	printf("\nPrint list:\n");
	print_list(list);

	printf("\nReverse linked list:\n");
	linkedlist_reverse(list);
	print_list(list);

	printf("\nReverse linked list again:\n");
	linkedlist_reverse(list);
	print_list(list);

	printf("\nGet data at position %d: ", 0);
	int* vp0 = (int*)(linkedlist_getdata_at(list, 0));
	printf("%d", *vp0);

	printf("\nGet data at position %d: ", 3);
	int v3 = *((int*)(linkedlist_getdata_at(list, 3)));
	printf("%d\n", v3);

	printf("\nRemove first node\n");
	struct linkedlistnode* rnode = linkedlist_remove(list, (void*)vp0);

	if (rnode != NULL) {
		printf("Node removed successfully\n");
		free(rnode);
	}

	printf("\nPrint list:\n");
	print_list(list);

	/*
	 printf("\nGet data at position %d: ", 0);
	int v0 = *((int*)(linkedlist_getdata_at(list, 0)));
	printf("%d\n", v0);
	*/

	// free resources
	linkedlist_destroy(list);
	printf("\nLinked list destroyed successfully.\n");
}

/*
 * Linked list demo.
 * */
void circsinglelinklist_demo() {

	/*
	 * Print list data
	 * */
	void print_list(struct circlinkedlist* list, int num_nodes) {
		struct circlinkedlistnode* node = circlinkedlist_getstart(list);

		for (int i = 0; i < num_nodes; ++i) {
			if (node->data == NULL)
				printf("-- ");
			else
				printf("%d ", *((int*)(node->data)));

			node = node->next;
		}

		printf("\n");
	}

	/*
	 * Checks for equality
	 * */
	int isequal(const void* a, const void* b) {
		if (*(int*)a == *(int*)b)
			return 1;
		else
			return 0;
	}

	struct circlinkedlist* list = circlinkedlist_create(isequal);

	int data[] = {1,2,3,4};
	int n = sizeof(data) / sizeof(data[0]);

	printf("____________________\n");
	printf("CIRCULAR LINKED LIST\n");

	printf("\nCircular single linked list demo -----------\n\n");

	for(int i = 0; i != n; ++i) {
		circlinkedlist_insert_at_end(list, &data[i]);
		printf("Insert at end value '%d'.\n", data[i]);
	}

	int num_nodes = 10;
	printf("\nPrint list (%d nodes):\n", num_nodes);
	print_list(list, 10);

	int startval = 1000;

	printf("\nInsert at start value '%d'.\n", startval);
	circlinkedlist_insert_at_begin(list, &startval);

	printf("\nPrint list (%d nodes):\n", num_nodes);
	print_list(list, num_nodes);

	printf("\nRemove first node\n");
	struct circlinkedlistnode* rnode = circlinkedlist_remove(list, (void*)(&startval));

	if (rnode != NULL) {
		printf("Node removed successfully\n");
		free(rnode);
	}

	printf("\nPrint list:\n");
	print_list(list, num_nodes);

	// free resources
	circlinkedlist_destroy(list);
	printf("\nCircular linked list destroyed successfully.\n");
}

/*
 * Hash table demo.
 * */
void hashtable_demo() {
	int hashfunc(const void* key) {
		return *((int*)key);
	}

	int isequalfunc(const void* key1, const void* key2) {
		int i1 = *((int*)key1);
		int i2 = *((int*)key2);
		if (i1 == i2)
			return 1;
		else
			return 0;
	}

	struct hashtable* htable = hashtable_create(11, 0.75, 2.0, hashfunc, isequalfunc);

	int* key1 = malloc(sizeof(int));
	int* key2 = malloc(sizeof(int));
	int* key3 = malloc(sizeof(int));
	int* key4 = malloc(sizeof(int));
	int* key5 = malloc(sizeof(int));
	int* key6 = malloc(sizeof(int));

	*key1 = 1;
	*key2 = 2;
	*key3 = 3;
	*key4 = 4;
	*key5 = 5;
	*key6 = 6;

	float* v1 = malloc(sizeof(float));
	float* v2 = malloc(sizeof(float));
	float* v3 = malloc(sizeof(float));
	float* v4 = malloc(sizeof(float));
	float* v5 = malloc(sizeof(float));
	float* v6 = malloc(sizeof(float));

	*v1 = 5.3;
	*v2 = 7.9;
	*v3 = 8.78;
	*v4 = 9.1;
	*v5 = 2.76;
	*v6 = 1.0;

	printf("_________\n");
	printf("HASHTABLE\n");
	printf("\nHash table demo ------------\n\n");

	hashtable_put(htable, key1, v1);
	printf("Insert key '%d' value '%.2f'\n", *key1, *v1);

	hashtable_put(htable, key2, v2);
	printf("Insert key '%d' value '%.2f'\n", *key2, *v2);

	hashtable_put(htable, key3, v3);
	printf("Insert key '%d' value '%.2f'\n", *key3, *v3);

	hashtable_put(htable, key4, v4);
	printf("Insert key '%d' value '%.2f'\n", *key4, *v4);

	hashtable_put(htable, key5, v5);
	printf("Insert key '%d' value '%.2f'\n", *key5, *v5);

	hashtable_put(htable, key6, v6);
	printf("Insert key '%d' value '%.2f'\n", *key6, *v6);

	float* fp = hashtable_get(htable, key3);
	printf("\nGet key '%d': %f.\n", *key3, *fp);

	// delete key3
	void* delkey3 = hashtable_delete(htable, key3);

	if (delkey3 == NULL)
	{
		printf("Failed to delete key '%d' from hash table.\n", *key3);
	}
	else
	{
		printf("Delete key '%d' succeeded.\n", *key3);
	}

	fp = hashtable_get(htable, key3);

	if (fp == NULL) {
		printf("Get key '%d': %s", *key3, "Element not found.\n");
	}
	else {
		printf("Get key '%d': %s", *key3, "Error: something went wrong.\n");
	}



	hashtable_destroy(htable);
	printf("End: %s", "Hash table destroyed successfully.\n");

	// free memory
	free(v1);
	free(v2);
	free(v3);
	free(v4);
	free(v5);
	free(v6);

	free(key1);
	free(key2);
	free(key3);
	free(key4);
	free(key5);
	free(key6);

}


int main() {
	printf("\n");
	arraylist_demo();
	printf("\n\n");
	singlelinklist_demo();
	printf("\n\n");
	circsinglelinklist_demo();
	printf("\n\n");
	doublelinklist_demo();
	printf("\n\n");
	circdoublelinklist_demo();
	printf("\n\n");
	hashtable_demo();
	printf("\n\n");
	binarysearch_demo();
	printf("\n\n");
	linkedliststack_demo();
	printf("\n\n");
	linkedlistqueue_demo();
	printf("\n\n");
	binarytree_demo();
	printf("\n\n");
	bst_demo();
	printf("\n\n");
	avltree_demo();
	return EXIT_SUCCESS;
}
