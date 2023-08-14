/*
 * maxbinaryheap.c
 *
 *  Created on: 13/07/2023
 *      Author: Tiago C. Teixeira
* Description: C implementation of a max binary heap.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "heapstruct.h"

/*
 * Function to get index of parent of node at index i.
 */
int maxbinaryheap_parent(int i) { return (i-1)/2; }

/*
 * Function to get index of left child of node at index i.
 */
int maxbinaryheap_left(int i) { return (2*i + 1); }

/*
 * Function to get index of right child of node at index i.
 */
int maxbinaryheap_right(int i) { return (2*i + 2); }

/*
 * A utility function to swap two elements.
 */
void maxbinaryheap_swap(struct heap* h, int i, int j)
{
	void* temp = h->arr[i];
	h->arr[i] = h->arr[j];
	h->arr[j] = temp;
}

/*
 * A recursive method to heapify a subtree with the root at given index
 * This method assumes that the subtrees are already heapified.
 */
void maxbinaryheap_heapify(struct heap* h, int i)
{
    int l = maxbinaryheap_left(i);
    int r = maxbinaryheap_right(i);
    int bigger = i;
    if (l < h->size && (h->compare(h->arr[l], h->arr[i]) > 0))
        bigger = l;
    if (r < h->size && (h->compare(h->arr[r], h->arr[bigger]) > 0))
        bigger = r;
    if (bigger != i)
    {
    	maxbinaryheap_swap(h, i, bigger);
        maxbinaryheap_heapify(h, bigger);
    }
}

/*
 * Function to create a max heap.
 */
struct heap* maxbinaryheap_createHeap(int capacity, void** datalist, int listsize,
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
    h->printdata = printdatafunc;
    h->freedata = freedatafunc;

    // Allocating memory to array
    h->arr = (void*)malloc(capacity * sizeof(void*));

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
        maxbinaryheap_heapify(h, i);
        i--;
    }
    return h;
}

/*
 * Inserts a new value in the heap.
 * Inserting a new key takes O(log N) time. We add a new key at the end of the tree.
 * If the new key is smaller than its parent, then we don’t need to do anything. Otherwise,
 * we need to traverse up to fix the violated heap property.
 */
void maxbinaryheap_insert(struct heap* h, void* data)
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

    // Fix the max heap property if it is violated
    while (i != 0 && (h->compare(h->arr[maxbinaryheap_parent(i)], h->arr[i]) < 0))
    {
    	maxbinaryheap_swap(h, i, maxbinaryheap_parent(i));
    	i = maxbinaryheap_parent(i);
    }
}

/*
 * Method to remove priority element (or root) from heap.
 * The time Complexity of this Operation is O(log N) as this operation needs to maintain
 * the heap property (by calling heapify()) after removing the root.
 */
void* maxbinaryheap_extract(struct heap* h)
{
    if (h->size <= 0)
        return h->MINVALUE;
    if (h->size == 1)
    {
        h->size--;
        return h->arr[0];
    }

    // Store the priority value, and remove it from heap
    void* root = h->arr[0];
    h->arr[0] = h->arr[h->size-1];
    h->size--;
    maxbinaryheap_heapify(h, 0);

    return root;
}

/*
 * Returns the priority value (at root) from heap but does not remove it.
 * The time Complexity of this operation is O(1).
 */
void* maxbinaryheap_peek(struct heap* h) { return h->arr[0]; }

 /*
  * Increases value of key at index 'i' to new_val. It is assumed that
  * new_val is bigger than h->arr[i].
  * Increases the value of the key. The time complexity of this operation is O(log N).
  * If the increased key value of a node is lesser than the parent of the node, then
  * we don’t need to do anything. Otherwise, we need to traverse up to fix the violated
  * heap property.
  */
 void maxbinaryheap_increasekey(struct heap* h, int i, void* new_val)
{
	 h->arr[i] = new_val;
	 while (i != 0 && (h->compare(h->arr[maxbinaryheap_parent(i)], h->arr[i]) < 0))
	 {
		 maxbinaryheap_swap(h, i, maxbinaryheap_parent(i));
		 i = maxbinaryheap_parent(i);
	 }
}

/*
 * This function deletes key at index i. It first increased value to plus
 * infinite, then calls extract().
 * Deleting a key also takes O(log N) time. We replace the key to be deleted with the
 * maximum infinite by calling increaseKey(). After increaseKey(), the maximum infinite value
 * must reach root, so we call extract() to remove the key.
 */
void maxbinaryheap_delete(struct heap* h, int i)
{
	maxbinaryheap_increasekey(h, i, h->MAXVALUE);
	maxbinaryheap_extract(h);
}

/*
 * Prints the heap elements (equivalent to level order traversal in a binary tree).
 * */
void maxbinaryheap_print(struct heap* h)
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
void maxbinaryheap_destroy(struct heap* h)
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

