/*
 * fibonacciheap.c
 *
 *  Created on: 27/07/2023
 *      Author: Tiago C. Teixeira
 * Description: C implementation of a Fibonacci heap data structure.
 */

#include <stdlib.h>
#include <stdio.h>
#include "fibonacciheap.h"


#define FIBHEAP_EULER_CONST 2.718281828459045235
#define FIBHEAP_TAYLOR_ITERATIONS 20

/*
 * Computes the natural log of a number.
 * Note: no need for math.h (4 to 5 decimals precision but is enough)
 */
double fibheap_nat_log(double x) {
    // Trap illegal values
    if (x <= 0) {
        return 0.0/0.0;  // NaN
    }

    // Confine x to a sensible range
    int power_adjust = 0;
    while (x > 1.0) {
        x /= FIBHEAP_EULER_CONST;
        power_adjust++;
    }
    while (x < .25) {
        x *= FIBHEAP_EULER_CONST;
        power_adjust--;
    }

    // Now use the Taylor series to calculate the logarithm
    x -= 1.0;
    double t = 0.0, s = 1.0, z = x;
    for (int k = 1; k <= FIBHEAP_TAYLOR_ITERATIONS; k++) {
        t += z * s / k;
        z *= x;
        s = -s;
    }

    // Combine the result with the power_adjust value and return
    return t + power_adjust;
}

/*
 * Creates a new fibonacci heap instance.
 */
struct fibheap* fibheap_create(void* minlimit, fibheap_cmp comparefunc,
										fibheap_printdata printdatafunc,
										fibheap_freedata freedatafunc)
{
	struct fibheap* result = (struct fibheap*)malloc(sizeof(*result));
	if (result == NULL)
	{
		printf("Memory error allocating fibonacci heap structure instance.");
		return NULL;
	}

	result->mini = NULL;
	result->no_of_nodes = 0;
	result->MINVALUE = minlimit;
	result->compare = comparefunc;
	result->freedata = freedatafunc;
	result->printdata = printdatafunc;
	return result;
}

/*
 * Creates a new fibonacci heap node
 */
struct fibheapnode* fibheap_createnode(void* val)
{
	struct fibheapnode* result = (struct fibheapnode*)malloc(sizeof(*result));
	if (result != NULL) {
		result->key = val;
		result->degree = 0;
		result->c = FIBHEAP_FLAG_NO;
		result->mark = FIBHEAP_MARK_WHITE;
		result->parent = result->child = NULL;
		result->left = result->right = result;	// point to himself
	}

	return result;
}

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
void fibheap_insert(struct fibheap* fh, void* val)
{
    struct fibheapnode* new_node = fibheap_createnode(val);

    if (new_node != NULL) {
		if (fh->mini != NULL) {
			(fh->mini->left)->right = new_node;
			new_node->right = fh->mini;
			new_node->left = fh->mini->left;
			fh->mini->left = new_node;
			if (fh->compare(new_node->key, fh->mini->key) < 0)
				fh->mini = new_node;
		}
		else {
			fh->mini = new_node;
		}

		fh->no_of_nodes++;
    }
}

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
struct fibheap* fibheap_union(struct fibheap* h1, struct fibheap* h2)
{
	struct fibheapnode* mini = NULL;

	// set min to lesser of h1.min and h2.min
	if (h1->compare(h1->mini->key, h2->mini->key) > 0)
		mini = h2->mini;
	else
		mini = h1->mini;

	// fix pointers to combine root lists
	struct fibheapnode* last = h2->mini->left;
	h2->mini->left = h1->mini->left;
	h1->mini->left->right =  h2->mini;
	h1->mini->left = last;
	h1->mini->left->right = h1->mini;

	h1->mini = mini;

	// update total nodes
	h1->no_of_nodes = h1->no_of_nodes + h2->no_of_nodes;

	// reset h2
	h2->mini = NULL;
	h2->no_of_nodes = 0;
	return h1;
}

/*
 * Linking the heap nodes in parent child relationship
 * Makes ptr2 child of ptr1
 */
void fibheap_fibonnaci_link(struct fibheap* fh, struct fibheapnode* ptr2, struct fibheapnode* ptr1)
{
	// free ptr2 from his double linked list
    (ptr2->left)->right = ptr2->right;
    (ptr2->right)->left = ptr2->left;
    if (ptr1->right == ptr1)
    	fh->mini = ptr1;

    // free left/right ponteirs of ptr2
    ptr2->left = ptr2;
    ptr2->right = ptr2;
    ptr2->parent = ptr1;
    if (ptr1->child == NULL)
        ptr1->child = ptr2;

    ptr2->right = ptr1->child;
    ptr2->left = (ptr1->child)->left;

    ((ptr1->child)->left)->right = ptr2;
    (ptr1->child)->left = ptr2;

    if (fh->compare(ptr2->key, (ptr1->child)->key) < 0)
        ptr1->child = ptr2;

    ptr1->degree++;
}

/*
 * Consolidating the heap.
 */
void fibheap_consolidate(struct fibheap* fh)
{
//	struct fibheapnode* mini = fh->mini;
    int temp1;
    float temp2 = (fibheap_nat_log(fh->no_of_nodes)) / (fibheap_nat_log(2)) + 1;
    int temp3 = temp2;
    int size = temp3+1;
    struct fibheapnode* arr[temp3+1];
    for (int i = 0; i <= temp3; i++)
        arr[i] = NULL;
    struct fibheapnode* ptr1 = fh->mini;
    struct fibheapnode* ptr2;
    struct fibheapnode* ptr3;
    struct fibheapnode* ptr4 = ptr1;
    do {
        ptr4 = ptr4->right;
        temp1 = ptr1->degree;
        while ((arr[temp1] != NULL) && (temp1 < size)) {
            ptr2 = arr[temp1];
            if (fh->compare(ptr1->key, ptr2->key) > 0)	// (ptr1->key > ptr2->key)
            {
                ptr3 = ptr1;	// swap pointers
                ptr1 = ptr2;
                ptr2 = ptr3;
            }
            if (ptr2 == fh->mini)
                fh->mini = ptr1;
            // fh->mini = mini;
            fibheap_fibonnaci_link(fh, ptr2, ptr1);
            if (ptr1->right == ptr1)
                fh->mini = ptr1;
            arr[temp1] = NULL;
            temp1++;
        }
        arr[temp1] = ptr1;
        ptr1 = ptr1->right;
    } while (ptr1 != fh->mini);

    fh->mini = NULL;
    for (int j = 0; j <= temp3; j++) {
        if (arr[j] != NULL) {
            arr[j]->left = arr[j];
            arr[j]->right = arr[j];
            if (fh->mini != NULL) {
                ((fh->mini)->left)->right = arr[j];
                arr[j]->right = fh->mini;
                arr[j]->left = (fh->mini)->left;
                (fh->mini)->left = arr[j];
                if (fh->compare(arr[j]->key, (fh->mini)->key) < 0)	// (arr[j]->key < mini->key)
                    fh->mini = arr[j];
            }
            else {
                fh->mini = arr[j];
            }
            if (fh->mini == NULL)
            	fh->mini = arr[j];
            else if (fh->compare(arr[j]->key, (fh->mini)->key) < 0)	// (arr[j]->key < mini->key)
            	fh->mini = arr[j];
        }
    }
}

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
struct fibheapnode* fibheap_extract_min(struct fibheap* fh)
{
//	struct fibheapnode* mini = fh->mini;
	struct fibheapnode* result = fh->mini;

    if (fh->mini == NULL)
    	printf("The heap is empty");
    else {
    	struct fibheapnode* temp = fh->mini;
    	struct fibheapnode* pntr;
        pntr = temp;
        struct fibheapnode* x = NULL;

        // attach child nodes to root list
        if (temp->child != NULL) {
            x = temp->child;
            do {
                pntr = x->right;
                (fh->mini->left)->right = x;
                x->right = fh->mini;
                x->left = fh->mini->left;
                fh->mini->left = x;
                if (fh->compare(x->key, fh->mini->key) < 0) //(x->key < mini->key)
                	fh->mini = x;
                x->parent = NULL;
                x = pntr;
            } while (pntr != temp->child);
        }

        (temp->left)->right = temp->right;
        (temp->right)->left = temp->left;
        fh->mini = temp->right;
        if ((temp == temp->right) && (temp->child == NULL))
        	fh->mini = NULL;
        else {
            fh->mini = temp->right;
            fibheap_consolidate(fh);

        }

        fh->no_of_nodes--;
    }

    return result;
}

/*
 * Cutting a node in the heap to be placed in the root list
 */
void fibheap_cut(struct fibheap* fh, struct fibheapnode* found, struct fibheapnode* temp)
{
	struct fibheapnode* mini = fh->mini;
    if (found == found->right)
        temp->child = NULL;

    (found->left)->right = found->right;
    (found->right)->left = found->left;
    if (found == temp->child)
        temp->child = found->right;

    temp->degree = temp->degree - 1;
    found->right = found;
    found->left = found;
    (mini->left)->right = found;
    found->right = mini;
    found->left = mini->left;
    mini->left = found;
    found->parent = NULL;
    found->mark = FIBHEAP_MARK_BLACK;	// 'B';
}

/*
 * Recursive cascade cutting function
 */
void fibheap_cascade_cut(struct fibheap* fh, struct fibheapnode* temp)
{
	struct fibheapnode* ptr5 = temp->parent;
    if (ptr5 != NULL) {
        if (temp->mark == FIBHEAP_MARK_WHITE) {
            temp->mark = FIBHEAP_MARK_BLACK;	//'B';
        }
        else {
            fibheap_cut(fh, temp, ptr5);
            fibheap_cascade_cut(fh, ptr5);
        }
    }
}

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
void fibheap_decrease_key(struct fibheap* fh, struct fibheapnode* found, void* val)
{
	struct fibheapnode* mini = fh->mini;

    if (mini == NULL)
    	printf("The Heap is Empty");

    if (found == NULL)
    	printf("Node not found in the Heap");

    found->key = val;

    struct fibheapnode* temp = found->parent;
    if (temp != NULL && (fh->compare(found->key, temp->key) < 0))
    {	//  found->key < temp->key)
        fibheap_cut(fh, found, temp);
        fibheap_cascade_cut(fh, temp);
    }
    if (fh->compare(found->key, mini->key) < 0)	//(found->key < mini->key)
        mini = found;

    fh->mini = mini;
}

/*
 * Function to find the given node and decrease his value
 */
void fibheap_find_and_decrease(struct fibheap* fh, struct fibheapnode* mini, void* old_val, void* val)
{
    struct fibheapnode* found = NULL;
    struct fibheapnode* temp5 = mini;
    temp5->c = FIBHEAP_FLAG_YES;	// 'Y';
    struct fibheapnode* found_ptr = NULL;
    if (fh->compare(temp5->key, old_val) == 0)	// (temp5->key == old_val)
    {
        found_ptr = temp5;
        temp5->c = FIBHEAP_FLAG_NO;	// 'N';
        found = found_ptr;
        fibheap_decrease_key(fh, found, val);
    }
    if (found_ptr == NULL) {
        if (temp5->child != NULL)
            fibheap_find_and_decrease(fh, temp5->child, old_val, val);
        if ((temp5->right)->c != FIBHEAP_FLAG_YES)	// 'Y'
        	fibheap_find_and_decrease(fh, temp5->right, old_val, val);
    }

    temp5->c = FIBHEAP_FLAG_NO;	//'N';
    found = found_ptr;
}

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
struct fibheapnode* fibheap_delete(struct fibheap* fh, void* val)
{
	struct fibheapnode* result = NULL;

    if (fh->mini == NULL)
    	printf("The heap is empty");
    else {
        // Decreasing the value of the node to minimum
    	fibheap_find_and_decrease(fh, fh->mini, val, fh->MINVALUE);

        // Calling Extract_min function to
        // delete minimum value node, which is minimum
        result = fibheap_extract_min(fh);
        printf("Key deleted");
    }

    return result;
}

/*
 * Function to display the heap
 */
void fibheap_print(struct fibheap* fh)
{
	struct fibheapnode* mini = fh->mini;
    struct fibheapnode* ptr = mini;

    if (ptr == NULL)
    	printf("The Heap is empty");
    else {
    	printf("The root nodes of Heap are:\n");
        do {
        	fh->printdata(ptr->key);
            ptr = ptr->right;
            if (ptr != mini) {
                printf("-->");
            }
        } while (ptr != mini && ptr->right != NULL);
        printf("\n");
        printf("The heap has %d node(s)\n\n", fh->no_of_nodes);
    }
}

/*
 * Destroys and releases fibonacci heap node resources from memory.
 */
void fibheap_destroynode(struct fibheap* fh, struct fibheapnode* node)
{
	if (fh->freedata != NULL)
	{
		if (node->key)
			fh->freedata(node->key);
	}

	free(node);
}

/*
 * Destroys and releases heap resources from memory.
 */
void fibheap_destroy(struct fibheap* fh)
{
	struct fibheapnode* node;
	while (fh->mini != NULL) {
		node = fibheap_extract_min(fh);
		if (node)
			fibheap_destroynode(fh, node);
	}

	free(fh);
}
