/*************************************************************************
 * linkliststack.c
 *
 *  Created on: 12/04/2023
 *      Author: Tiago C. Teixeira
 * Description: Implements a generic stack in C using a linked list.
 *
 *
 * Definition:
 *
 * 		A stack is a linear data structure in which the insertion of a
 * 		new element and removal of an existing element takes place at the
 * 		same end represented as the top of the stack.
 *		We can access the elements only on the top of the stack.
 *		In conclusion, a Stack is a linear data structure that operates on
 *		the LIFO principle and can be implemented using an array or a linked list.
 *      This strategy states that the element that is inserted last will
 *      come out first (LIFO - last in, first out data structure).
 *
 *
 * Advantages of Linked List implementation:
 *
 *     The linked list implementation of a stack can grow and shrink
 *     according to the needs at runtime.
 *     It is used in many virtual machines like JVM.
 *
 * Disadvantages of Linked List implementation:
 *
 *    Requires extra memory due to the involvement of pointers.
 *    Random accessing is not possible in stack.
 *
 *
 * Complexity Analysis:
 *
 *    Time Complexity
 *
 *		Operations  	Complexity
 *		push() 			O(1)
 *		pop()   		O(1)
 *		isEmpty() 		O(1)
 *		size()			O(1)
 *
 *
 * Applications of the stack:
 *
 *    Infix to Postfix /Prefix conversion
 *    Redo-undo features at many places like editors, photoshop.
 *    Forward and backward features in web browsers
 *    Used in many algorithms like Tower of Hanoi, tree traversals,
 *    stock span problems, and histogram problems.
 *    Backtracking is one of the algorithm designing techniques. Some
 *    examples of backtracking are the Knight-Tour problem, N-Queen
 *    problem, find your way through a maze, and game-like chess or
 *    checkers in all these problems we dive into someway if that way
 *    is not efficient we come back to the previous state and go into
 *    some another path. To get back from a current state we need to
 *    store the previous state for that purpose we need a stack.
 *    In Graph Algorithms like Topological Sorting and Strongly Connected
 *    Components.
 *    In Memory management, any modern computer uses a stack as the primary
 *    management for a running purpose. Each program that is running in a
 *    computer system has its own memory allocations.
 *    String reversal is also another application of stack. Here one by
 *    one each character gets inserted into the stack. So the first
 *    character of the string is on the bottom of the stack and the last
 *    element of a string is on the top of the stack. After Performing
 *    the pop operations on the stack we get a string in reverse order.
 *    Stack also helps in implementing function call in computers.
 *    The last called function is always completed first.
 *    Stacks are also used to implement the undo/redo operation in text editor.
 *
 *
 *	Source: https://www.geeksforgeeks.org/introduction-to-stack-data-structure-and-algorithm-tutorials/
 *
 ************************************************************************/

#ifndef LINKLISTSTACK_C_
#define LINKLISTSTACK_C_



#endif /* LINKLISTSTACK_C_ */

#include <stdlib.h>
#include "linkedliststack.h"

/*
 * Creates a new stack instance.
 * */
struct linkedliststack* linkedliststack_create( )
{
	struct linkedliststack* result = linkedliststack_create_freedata( NULL );
	return result;
}

/*
 * Creates a new stack instance.
 * */
struct linkedliststack* linkedliststack_create_freedata(linkedlist_freedata freedata ) {
	struct linkedliststack* result = NULL;

	struct linkedlist* list = linkedlist_create( NULL, freedata );
	if (list == NULL)
		return NULL;
	else
	{
		result = malloc(sizeof(*result));
		if (result == NULL) {
			linkedlist_destroy(list);
			return NULL;
		}
		else
		{
			result->list = list;
			result->top = NULL;
		}
	}

	return result;
}

/*
 * Checks if stack is empty.
 * Returns 1 if is empty, 0 otherwise.
 * */
int linkedliststack_isempty(struct linkedliststack* st) {
	int result = (st->top == NULL);
	return result;
}

/*
 * Gets the number of elements in the stack.
 * */
uint linkedliststack_size(struct linkedliststack* st) {
	return st->list->size;
}

/*
 * Inserts a new element on top of stack.
 * Returns 1 if succeeded, 0 otherwise.
 * */
int linkedliststack_push(struct linkedliststack* st, void* data) {
	int result = linkedlist_push(st->list, data);
	st->top = linkedlist_getfirst(st->list);
	return result;
}

/*
 * Retrieves the top element of the stack and removes top node.
 * Returns top element if succeeded, NULL otherwise.
 * */
void* linkedliststack_pop(struct linkedliststack* st) {
	void* result = NULL;
	if (linkedliststack_isempty(st))
		return NULL;
	else
	{
		struct linkedlistnode* node = linkedlist_remove_first(st->list);
		if (node != NULL) {
			st->top = linkedlist_getfirst(st->list);
			result = node->data;
			// release node
			free(node);
		}
		else {
			// fail to remove first node
		}
	}

	return result;
}

/*
 * Retrieves the top data element of the stack (but doesn't remove top node).
 * Returns data element at top of stack if succeeded, NULL otherwise.
 * */
void* linkedliststack_peek(struct linkedliststack* st) {
	void* result = NULL;
	if (linkedliststack_isempty(st))
		return NULL;
	else
		result = st->top->data;

	return result;
}

/*
 * Releases stack structure from memory.
 * */
void linkedliststack_destroy(struct linkedliststack* st) {
	st->top = NULL;
	linkedlist_destroy(st->list);
	free(st);
}

