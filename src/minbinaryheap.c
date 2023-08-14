/*
 * minbinaryheap.c
 *
 *  Created on: 09/07/2023
 *      Author: Tiago C. Teixeira
 * Description: C implementation of a min binary heap.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "heapstruct.h"

/*
 * Function to get index of parent of node at index i.
 */
int minbinaryheap_parent(int i) { return (i-1)/2; }

/*
 * Function to get index of left child of node at index i.
 */
int minbinaryheap_left(int i) { return (2*i + 1); }

/*
 * Function to get index of right child of node at index i.
 */
int minbinaryheap_right(int i) { return (2*i + 2); }

/*
 * A utility function to swap two elements.
 */
void minbinaryheap_swap(struct heap* h, int i, int j)
{
	void* temp = h->arr[i];
	h->arr[i] = h->arr[j];
	h->arr[j] = temp;
}

//void minbinaryheap_swap(struct heap* h, void* x, void* y)
//{
//	void* temp = malloc(h->calcdatasize(x));
//	h->copydata()
//	*temp = *x;
//	*x = *y;
//	*y = *temp;
//	free(temp);
//}

/*
 * A recursive method to heapify a subtree with the root at given index
 * This method assumes that the subtrees are already heapified.
 */
void minbinaryheap_heapify(struct heap* h, int i)
{
    int l = minbinaryheap_left(i);
    int r = minbinaryheap_right(i);
    int smallest = i;
    if (l < h->size && (h->compare(h->arr[l], h->arr[i]) < 0))
        smallest = l;
    if (r < h->size && (h->compare(h->arr[r], h->arr[smallest]) < 0))
        smallest = r;
    if (smallest != i)
    {
    	minbinaryheap_swap(h, i, smallest);

//    	minbinaryheap_swap(h->arr[i], h->arr[smallest]);
        minbinaryheap_heapify(h, smallest);
    }
}

/*
 * Function to create a min heap.
 */
struct heap* minbinaryheap_createHeap(int capacity, void** datalist, int listsize,
										void* minlimit,
										void* maxlimit,
//										heap_calcdatasize calcdatasizefunc,
										heap_cmp comparefunc,
//										heap_minlimitkey minlimitfunc,
//										heap_maxlimitkey maxlimitfunc,
										heap_printdata printdatafunc,
										heap_freedata freedatafunc)
{
    // Allocating memory to heap h
	int arrsize = capacity * sizeof(void*);
    struct heap* h = (struct heap*)malloc(sizeof(struct heap));

    // Checking if memory is allocated to h or not
    if (h == NULL) {
        printf("Memory error allocating heap structure instance.");
        return NULL;
    }
    // set the values to size and capacity
    h->size = 0;
    h->capacity = capacity;
//    h->calcdatasize = calcdatasizefunc;
    h->compare = comparefunc;
    h->MINVALUE = minlimit;
    h->MAXVALUE = maxlimit;
//    *(h->MAXVALUE) = maxlimit;
//    *(h->MINVALUE) = minlimit;
    h->printdata = printdatafunc;
    h->freedata = freedatafunc;

    // Allocating memory to array
    h->arr = (void*)malloc(arrsize);

    // Checking if memory is allocated to h or not
    if (h->arr == NULL) {
    	free(h);
        printf("Memory error allocating heap array of data.");
        return NULL;
    }

    int i = 0;
    if (datalist) {
    	//int n = sizeof(datalist) / sizeof(datalist[0]);
    	for (i = 0; i < listsize; i++) {
			h->arr[i] = datalist[i];
	    }
    }

    h->size = i;
    i = (h->size - 2) / 2;
    while (i >= 0) {
        minbinaryheap_heapify(h, i);
        i--;
    }
    return h;
}

/*
 * Inserts a new value in the heap.
 * Inserting a new key takes O(log N) time. We add a new key at the end of the tree.
 * If the new key is greater than its parent, then we don’t need to do anything. Otherwise,
 * we need to traverse up to fix the violated heap property.
 */
void minbinaryheap_insert(struct heap* h, void* data)
{
    if (h->size == h->capacity)
    {
        printf("\nOverflow: Could not insert value\n");
        return;
    }

    // First insert the new key at the end
    h->size++;
    int i = h->size - 1;
    h->arr[i] = data;

    // Fix the min heap property if it is violated
    while (i != 0 && (h->compare(h->arr[minbinaryheap_parent(i)], h->arr[i]) > 0))
    {
    	minbinaryheap_swap(h, i, minbinaryheap_parent(i));
    	i = minbinaryheap_parent(i);
    }
}

/*
 * Method to remove priority element (or root) from heap.
 * The time Complexity of this Operation is O(log N) as this operation needs to maintain
 * the heap property (by calling heapify()) after removing the root.
 */
void* minbinaryheap_extract(struct heap* h)
{
    if (h->size <= 0)
        return h->MAXVALUE;
    if (h->size == 1)
    {
        h->size--;
        return h->arr[0];
    }

    // Store the priority value, and remove it from heap
    void* root = h->arr[0];
    h->arr[0] = h->arr[h->size-1];
    h->size--;
    minbinaryheap_heapify(h, 0);

    return root;
}

/*
 * Returns the priority value (at root) from heap but does not remove it.
 * The time Complexity of this operation is O(1).
 */
void* minbinaryheap_peek(struct heap* h) { return h->arr[0]; }

 /*
  * Decreases value of key at index 'i' to new_val. It is assumed that
  * new_val is smaller than h->arr[i].
  * Decreases the value of the key. The time complexity of this operation is O(log N).
  * If the decreased key value of a node is greater than the parent of the node, then
  * we don’t need to do anything. Otherwise, we need to traverse up to fix the violated
  * heap property.
  */
 void minbinaryheap_decreasekey(struct heap* h, int i, void* new_val)
{
	 h->arr[i] = new_val;
	 while (i != 0 && (h->compare(h->arr[minbinaryheap_parent(i)], h->arr[i]) > 0))
	 {
		 minbinaryheap_swap(h, i, minbinaryheap_parent(i));
		 i = minbinaryheap_parent(i);
	 }
}

/*
 * This function deletes key at index i. It first reduced value to minus
 * infinite, then calls extractMin().
 * Deleting a key also takes O(log N) time. We replace the key to be deleted with the
 * minimum infinite by calling decreaseKey(). After decreaseKey(), the minus infinite value
 * must reach root, so we call extract() to remove the key.
 */
void minbinaryheap_delete(struct heap* h, int i)
{
	minbinaryheap_decreasekey(h, i, h->MINVALUE);	// INT_MIN
	minbinaryheap_extract(h);
}

/*
 * Prints the heap elements (equivalent to level order traversal in a binary tree).
 * */
void minbinaryheap_print(struct heap* h)
{
    for (int i = 0; i < h->size; i++) {
        h->printdata(h->arr[i]);
        printf(" ");
    }
    printf("\n");
}

/*
 * Destroys and releases heap resources from memory.
 */
void minbinaryheap_destroy(struct heap* h)
{
	if (h->freedata != NULL)
	{
		void* data = NULL;
		for (int i = 0; i < h->size; ++i) {
			data = h->arr[i];
			if (data != NULL)
				h->freedata(data);
		}

		if (h->MINVALUE) h->freedata(h->MINVALUE);
		if (h->MAXVALUE) h->freedata(h->MAXVALUE);
	}

	free(h->arr);
	free(h);
}

