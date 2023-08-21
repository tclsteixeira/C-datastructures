/*
 * arraydeque.c
 *
 *  Created on: 15/08/2023
 *      Author: Tiago C. Teixeira
 * Description: Implements a deque data structure using a dynamic circular array.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "arraydeque.h"

/*
 * Create deque instance.
 */
struct arraydeque* arraydeque_create_capacity( size_t capacity,
									  arraydeque_printdata printdatafunc,
									  arraydeque_freedata freedatafunc )
{
	assert(capacity >= ARRAYDEQUE_MIN_CAPACITY);

	size_t arrsize = sizeof(void*) * capacity;
	struct arraydeque* result = (struct arraydeque*)malloc(arrsize + sizeof(*result));

	if (result == NULL)
		printf("Memory error when allocating arraydeque struct!\n");
	else
	{
		void** arrbuf = (void**)malloc(arrsize);

		if (arrbuf == NULL) {
			printf("Memory error when allocating arraydeque array!\n");
			free(result);
			return NULL;
		}
		else
		{
			result->arr = arrbuf;

			// init array elem
			for (int i = 0; i < capacity; i++)
				result->arr[i] = NULL;

			result->frontindex = result->backindex = -1;
			result->capacity = capacity;
			result->size = 0;
			result->printdata = printdatafunc;
			result->freedata = freedatafunc;
			return result;
		}
	}

	return NULL;
}

/*
 * Create deque instance with default capacity.
 */
struct arraydeque* arraydeque_create( arraydeque_printdata printdatafunc,
									  arraydeque_freedata freedatafunc )
{
	return arraydeque_create_capacity(ARRAYDEQUE_DEF_CAPACITY, printdatafunc, freedatafunc);
}

/*
 * Function to check if deque is empty or not
 */
int arraydeque_empty(struct arraydeque* arrdeque)
{
    if (arrdeque->frontindex == -1 && arrdeque->backindex == -1)
        return 1;
    else
        return 0;
}

/*
 * Function to check if deque is full or not
 */
int arraydeque_full(struct arraydeque* arrdeque)
{
    if (arrdeque->size == arrdeque->capacity)
        return 1;
    else
        return 0;
}

/*
 * Function to find the front element of the deque
 */
void* arraydeque_front(struct arraydeque* arrdeque)
{
    // If deque is empty
    if (arraydeque_empty(arrdeque)) {
    	printf("Deque underflow\n");
        abort();
    }

    return arrdeque->arr[arrdeque->frontindex];
}

/*
 * Function to find the last element of the deque
 */
void* arraydeque_back(struct arraydeque* arrdeque)
{
    // If deque is empty
    if (arraydeque_empty(arrdeque)) {
    	printf("Deque underflow\n");
        abort();
    }

    return arrdeque->arr[arrdeque->backindex];
}

/*
 * Function to insert the element
 * to the back of the deque
 *
 * - If the deque is full, then double the size of the current array and copy the elements
 * 		of the previous array into the new array.
 * - If deque is empty(), then assign frontIndex = backIndex = 0 and then assign X to
 * 		both arr[frontIndex] and arr[backIndex] and then increment sizeVar by one.
 *   Else, update backIndex as backIndex = (backIndex+1) %capacityVar and then assign
 *   	X to arr[backIndex] and increment sizeVar by one.
 */
void arraydeque_push_back(struct arraydeque* arrdeque, void* x)
{
    if (arraydeque_full(arrdeque)) {

        // If the deque is full, then
        // double the capacity
    	arrdeque->capacity = arrdeque->capacity * 2;

        // Initialize new array of
        // double size
        void** temp = (void**)malloc(sizeof(void*) * arrdeque->capacity);

        // Copy the elements of the
        // previous array
        int i = arrdeque->frontindex;
        int j = 0;
        while (i != arrdeque->backindex) {
            temp[j] = arrdeque->arr[i];
            i = (i + 1) % arrdeque->size;
            j++;
        }
        temp[j] = arrdeque->arr[i];

        arrdeque->frontindex = 0;
        arrdeque->backindex = arrdeque->size - 1;

        // Deallocate the memory
        // of previous array
        free(arrdeque->arr);
        arrdeque->arr = temp;
    }

    // If size is zero
    if (arraydeque_empty(arrdeque)) {
    	arrdeque->frontindex = arrdeque->backindex = 0;
    	arrdeque->arr[arrdeque->backindex] = x;
    	arrdeque->size++;
        return;
    }

    // Increment back index cyclically
    arrdeque->backindex = (arrdeque->backindex + 1) % arrdeque->capacity;
    arrdeque->arr[arrdeque->backindex] = x;
    arrdeque->size++;
    return;
}

/*
 * Function to insert the element
 * to the front of the deque
 *
 * - If the deque is full, then double the size of the current array and copy the
 * 		elements of the previous array into the new array.
 * - If deque is empty(), then assign frontIndex = backIndex = 0 and then assign X
 * 		to both arr[frontIndex] and arr[backIndex] and then increment sizeVar by one.
 *   Else, update frontIndex as frontIndex = (frontIndex-1 + capacityVar)%capacityVar
 *   	and then assign X to arr[frontIndex] and increment sizeVar by one.
 */
void arraydeque_push_front(struct arraydeque* arrdeque, void* x)
{
    if (arraydeque_full(arrdeque)) {

        // If the deque is full, then
        // double the capacity
    	arrdeque->capacity = arrdeque->capacity * 2;

        // Initialize new array of
        // double size
    	void** temp = (void**)malloc(sizeof(void*) * arrdeque->capacity);

        // Copy the elements of the
        // previous array
        int i = arrdeque->frontindex;
        int j = 0;
        while (i != arrdeque->backindex) {
            temp[j] = arrdeque->arr[i];
            i = (i + 1) % arrdeque->size;
            j++;
        }

        temp[j] = arrdeque->arr[i];

        arrdeque->frontindex = 0;
        arrdeque->backindex = arrdeque->size - 1;

        // Deallocate the memory
        // of previous array
        free(arrdeque->arr);
        arrdeque->arr = temp;
    }

    // If size is zero
    if (arraydeque_empty(arrdeque)) {
    	arrdeque->frontindex = arrdeque->backindex = 0;
    	arrdeque->arr[arrdeque->backindex] = x;
    	arrdeque->size++;
        return;
    }

    // Decrement front index cyclically
    arrdeque->frontindex
        = (arrdeque->frontindex - 1 + arrdeque->capacity) % arrdeque->capacity;
    arrdeque->arr[arrdeque->frontindex] = x;
    arrdeque->size++;
    return;
}

/*
 * Function to delete the element from the front of the deque.
 * Returns removed element if succeeded.
 *
 * - If the deque is empty,
 * 		print “Underflow”.
 *   Else if sizeVar is equal to 1 then
 *   	assign -1 to frontIndex and backIndex both and then decrement sizeVar by one.
 *   Else,
 *   	Update frontIndex as frontIndex = (frontIndex+1)%capacityVar and
 *   	decrement sizeVar by one.
 */
void* arraydeque_pop_front(struct arraydeque* arrdeque)
{
	void* result = NULL;

    // If deque is empty
    if (arraydeque_empty(arrdeque)) {
    	printf("Deque underflow\n");
        abort();
    }

    result = arraydeque_front(arrdeque);
    arrdeque->arr[arrdeque->frontindex] = NULL;

    // If there is only one character
    if (arrdeque->frontindex == arrdeque->backindex) {

        // Mark deque as empty
        // and decrement sizeVar
    	arrdeque->frontindex = arrdeque->backindex = -1;
    	arrdeque->size--;
        return result;
    }

    // Increment frontIndex cyclically
    arrdeque->frontindex = (arrdeque->frontindex + 1) % arrdeque->capacity;
    arrdeque->size--;
    return result;
}

/*
 * Function to remove the element from the back of the deque.
 * Returns removed element if succeeded.
 *
 * - If the deque is empty,
 * 		print “Underflow”.
 *   Else if sizeVar is equal to 1 then
 *   	assign -1 to frontIndex and backIndex both and then decrement sizeVar by one.
 *   Else,
 *   	Update backIndex as backIndex = (backndex-1 + capacityVar) % capacityVar and
 *   	decrement sizeVar by one.
 */
void* arraydeque_pop_back(struct arraydeque* arrdeque)
{
	void* result = NULL;

    // If deque is empty
    if (arraydeque_empty(arrdeque)) {
    	printf("Deque underflow\n");
        abort();
    }

    result = arraydeque_back(arrdeque);
    arrdeque->arr[arrdeque->backindex] = NULL;

    // If there is only one character
    if (arrdeque->frontindex == arrdeque->backindex) {

        // Mark deque as empty
        // and decrement sizeVar
    	arrdeque->frontindex = arrdeque->backindex = -1;
    	arrdeque->size--;
        return result;
    }

    // Decrement backIndex cyclically
    arrdeque->backindex = (arrdeque->backindex - 1 + arrdeque->capacity) % arrdeque->capacity;
    arrdeque->size--;
    return result;
}

/*
 * Release array deque instance from memory.
 * */
void arraydeque_destroy(struct arraydeque* arrdeque)
{
	if (arrdeque->freedata != NULL)
		for (int i = 0; i < arrdeque->capacity; ++i) {
			if (arrdeque->arr[i] != NULL)
				arrdeque->freedata(arrdeque->arr[i]);
	}
	free(arrdeque->arr);
	free(arrdeque);
}


