/*
 * arrlist.c
 *
 *  Created on: 10/02/2023
 *      Author: tiago
 *
 *  Implementation of a generic array list in C.
 */

#include "arraylist.h"

#include <stdlib.h>
#include <math.h>

#define DEFAULT_CAPACITY  20
#define DEFAULT_CHUNK_FRAC  1.0/3.0

/*
 * Creates and initializes an arraylist structure.
 * */
struct arraylist* arraylist_create_capacity(uint capacity) {
	uint bufsize = capacity;
	struct arraylist* result = malloc(sizeof(struct arraylist));

	if (result == NULL)
		return NULL;

	void** buffer = malloc(sizeof(void*) * bufsize);

	if (buffer == NULL) {
		free(result);
		return NULL;
	}

	result->buffer = buffer;
	result->capacity = bufsize;
	result->length = 0;
	return result;
}

/*
 * Creates and initializes an arraylist structure.
 * */
struct arraylist* arraylist_create() {
	struct arraylist* result = arraylist_create_capacity(DEFAULT_CAPACITY);
	return result;
}

/*
 * Gets the pointer to element located at index position in the
 * arraylist buffer array.
 * */
void* arraylist_get_item_at(const struct arraylist* a, unsigned int index) {
	if (index < 0 || index >= a->length)
		return NULL;

	return *(index + a->buffer);
}

/*
 * Allocates buffer memory if necessary to insert one element.
 * Note: Private function.
 * */
int arraylist_allocate_mem_if_needed_for_insertion(struct arraylist* a) {
	if (a->capacity == a->length) {
		float frac = DEFAULT_CHUNK_FRAC;
		unsigned int numel = trunc((1.0 + frac) * a->capacity);
		unsigned int numbytes = numel * sizeof(void*);
		void* newBuffer = realloc(a->buffer, numbytes);
		if (newBuffer == NULL)
		{
			// fail to reallocate memory
			return 0;
		}

		a->buffer = newBuffer;
		a->capacity = numel;
	}

	return 1;
}

/*
 * Appends an element to the end of the list.
 * param a: pointer to arraylist
 * param x: pointer to element.
 * */
int arraylist_add(struct arraylist* a, void* x) {
	if (arraylist_allocate_mem_if_needed_for_insertion(a)) {
		// add element at end
		a->buffer[a->length++] = x;
		return 1;
	}

	return 0;
}

/*
 * Inserts an elements in the arraylist at given position.
 * Returns 1 if succeeded, 0 otherwise.
 * */
int arraylist_insert(struct arraylist* a, unsigned int index, void* x) {
	int result = 0;
	unsigned int len = a->length;
	if (index < 0 || index > len)
		return 0;

	if (index == len) {
		result = arraylist_add(a, x);	// insert at end
	}
	else {
		if (arraylist_allocate_mem_if_needed_for_insertion(a)) {
			void** buffer = a->buffer;

			// move after index elements one position forward
			for(int i = len; i == index; --i) {
				buffer[i] = buffer[i-1];
			}

			// insert x at index
			*(index + buffer) = x;
			a->length++;
			result = 1;
		}
		else {
			// failed to allocate memory in buffer
		}
	}

	return result;
}

/*
 * Removes a given element from the list.
 * Returns the removed element if succeeded, NULL otherwise.
 * */
void* arraylist_remove(struct arraylist* a, void* el) {
	void* result = NULL;
	unsigned int len = a->length;
	void** buffer = a->buffer;
	for(int i = 0; i < len; ++i) {
		if (*(i + buffer) == el) {
			result = el;
			// move elements after current position one position
			// back
			for (int j = i+1; j < len; ++j)
				*((j-1) + buffer) = *(j + buffer);

			// decrement length
			a->length--;
			return result;
		}
	}

	return result;
}

/*
 * Removes a given element at given position.
 * Returns the removed element if succeeded, NULL otherwise.
 * */
void* arraylist_remove_at(struct arraylist* a, uint index) {
	void* result = NULL;
	uint len = a->length;
	if (index >= len)
		return NULL;
	else {
		void** buffer = a->buffer;
		result = arraylist_get_item_at(a, index);
		// move elements after current position one position
		// back
		for (int j = index+1; j < len; ++j)
			*((j-1) + buffer) = *(j + buffer);

		// decrement length
		a->length--;
	}

	return result;
}

/*
 * Reduces size of list and releases memory to fit only current data.
 * Returns 1 if succeeded, 0 otherwise.
 * */
int arraylist_shrink_to_fit(struct arraylist* a) {
	int result = 1;
	void** buffer = a->buffer;
	if (a->length < a->capacity)
	{
		void** newbuffer = realloc(buffer, sizeof(void*) * a->length);
		if (newbuffer != NULL) {
			a->buffer = newbuffer;
			a->capacity = a->length;
		}
		else
			result = 0;
	}

	return result;
}

/*
 * Releases all memory from an arraylist (includes buffer)
 * */
void arraylist_destroy(struct arraylist* a) {
	void** buffer = a->buffer;
	// free memory from buffer pointers
	free(buffer);
	// free arraylist struct
	free(a);
}


