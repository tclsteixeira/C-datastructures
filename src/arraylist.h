/*
 * arrlist.h
 *
 *  Created on: 14/02/2023
 *      Author: Tiago C. Teixeira
 *
 * 	Implementation of a generic array list in C.
 *
 */

#ifndef ARRAYLIST_H_
	#define ARRAYLIST_H_

	/*
	 * Declares arraylist structure
	 * Sintax prefered by linux gays way to declare struct types in C
	 * */
	struct arraylist {
		//unsigned int el_size;
		void** buffer;
		unsigned int capacity;
		unsigned int length;
	};

	/*
	 * Creates and initializes an arraylist structure with a given capacity.
	 * */
	struct arraylist* arraylist_create_capacity(unsigned int capacity);

	/*
	 * Creates and initializes an arraylist structure.
	 * */
	struct arraylist* arraylist_create();

	/*
	 * Gets the pointer to element located at index position in the
	 * arraylist buffer array.
	 * */
	void* arraylist_get_item_at(const struct arraylist* a, unsigned int index);

	/*
	 * Appends an element to the end of the list.
	 * param a: pointer to arraylist
	 * param x: pointer to element.
	 * */
	int arraylist_add(struct arraylist* a, void* x);

	/*
	 * Inserts an elements in the arraylist at given position.
	 * Returns 1 if succeeded, 0 otherwise.
	 * */
	int arraylist_insert(struct arraylist* a, unsigned int index, void* x);

	/*
	 * Removes a given element from the list.
	 * Returns the removed element if succeeded, NULL otherwise.
	 * */
	void* arraylist_remove(struct arraylist* a, void* el);

	/*
	 * Removes a given element at given position.
	 * Returns the removed element if succeeded, NULL otherwise.
	 * */
	void* arraylist_remove_at(struct arraylist* a, unsigned int index);

	/*
	 * Reduces size of list and releases memory to fit only current data.
	 * Returns 1 if succeeded, 0 otherwise.
	 * */
	int arraylist_shrink_to_fit(struct arraylist* a);

	/*
	 * Reduces size of list and releases memory to fit only current data.
	 * Returns 1 if succeeded, 0 otherwise.
	 * */
	void arraylist_destroy(struct arraylist* a);


#endif /* ARRAYLIST_H_ */


