/*
 * trie.c
 *
 *  Created on: 11/10/2023
 *      Author: Tiago C. Teixeira
 * Description: C implementation of Trie data structure.
 *
 * DEFINITION
 *
 * 	Trie data structure is defined as a Tree based data structure that is used for storing
 * 	some collection of strings and performing efficient search operations on them.
 * 	The word Trie is derived from reTRIEval, which means finding something or obtaining it.
 *
 * 	A trie can be used to sort a collection of strings alphabetically as well as search
 * 	whether a string with a given prefix is present in the trie or not.
 *
 * 	Advantages of Trie Data Structure over a Hash Table:
 *
 *   - We can efficiently do prefix search (or auto-complete) with Trie.
 *   - We can easily print all words in alphabetical order which is not easily possible
 *     with hashing.
 *   - There is no overhead of Hash functions in a Trie data structure.
 *   - Searching for a String even in the large collection of strings in a Trie data structure
 *     can be done in O(L) Time complexity, Where L is the number of words in the query
 *     string. This searching time could be even less than O(L) if the query string does not
 *     exist in the trie.
 *
 * Properties of a Trie Data Structure:
 *
 *   - There is one root node in each Trie.
 *   - Each node of a Trie represents a string and each edge represents a character.
 *   - Every node consists of hashmaps or an array of pointers, with each index representing
 *     a character and a flag to indicate if any string ends at the current node.
 *   - Trie data structure can contain any number of characters including alphabets, numbers,
 *     and special characters.
 *   - Each path from the root to any node represents a word or string.
 *
 *
 * Representation of Trie Node:
 *
 * 	Every Trie node consists of a character pointer array or hashmap and a flag to represent
 * 	if the word is ending at that node or not. But if the words contain only lower-case
 * 	letters (i.e. a-z), then we can define Trie Node with an array instead of a hashmap.
 *
 *
 * Complexity Analysis of Trie Data Structure
 *
 * 		-----------------------------------------------------
 * 		|	Operation 	Time Complexity 	Auxiliary Space	|
 * 	   	|---------------------------------------------------|
 * 		|	Insertion 		O(L) 				O(L*n)		|
 * 		|	Searching 		O(L) 				O(1)		|
 * 		|	Deletion 		O(L) 				O(1)		|
 * 		-----------------------------------------------------
 *
 * 		Note: In the above complexity table ‘L’, ‘n’ represents the size of the string and
 * 			  the number of strings that are stored in the trie.
 *
 *
 * Applications of Trie data structure:
 *
 *		1. Autocomplete Feature: Autocomplete provides suggestions based on what you type in
 *		   the search box.
 *
 * 		2. Spell Checkers: If the word typed does not appear in the dictionary, then it shows
 * 		   suggestions based on what you typed.
 *
 *		   Trie stores the data dictionary and makes it easier to build an algorithm for
 *		   searching the word from the dictionary and provides the list of valid words for
 *		   the suggestion.
 *
 *		3. Longest Prefix Matching Algorithm(Maximum Prefix Length Match): This algorithm is
 *		   used in networking by the routing devices in IP networking. Optimization of
 *		   network routes requires contiguous masking that bound the complexity of lookup a
 *		   time to O(n), where n is the length of the URL address in bits.
 *
 * 		   To speed up the lookup process, Multiple Bit trie schemes were developed that
 * 		   perform the lookups of multiple bits faster.
 *
 *
 * Advantages of Trie data structure:
 *
 *  - Trie allows us to input and finds strings in O(L) time, where L is the length of a
 *    single word. It is faster as compared to both hash tables and binary search trees.
 *
 *  - It provides alphabetical filtering of entries by the key of the node and hence makes
 *    it easier to print all words in alphabetical order.
 *
 *  - Trie takes less space when compared to BST because the keys are not explicitly saved
 *    instead each key requires just an amortized fixed amount of space to be stored.
 *
 *  - Prefix search/Longest prefix matching can be efficiently done with the help of trie
 *    data structure.
 *    Since trie doesn’t need any hash function for its implementation so they are generally
 *    faster than hash tables for small keys like integers and pointers.
 *
 *  - Tries support ordered iteration whereas iteration in a hash table will result in
 *    pseudorandom order given by the hash function which is usually more cumbersome.
 *
 *  - Deletion is also a straightforward algorithm with O(L) as its time complexity, where L
 *    is the length of the word to be deleted.
 *
 *
 * Disadvantages of Trie data structure:
 *
 *  - The main disadvantage of the trie is that it takes a lot of memory to store all the
 *    strings. For each node, we have too many node pointers which are equal to the no of
 *    characters in the worst case.
 *
 *  - An efficiently constructed hash table(i.e. a good hash function and a reasonable load
 *    factor) has O(1) as lookup time which is way faster than O(L) in the case of a trie,
 *    where L is the length of the string.
 *
 *
 * Top Interview problems on Trie data structure:
 *
 * S.no 	Problem
 * ----------------------------------------------------------------------
 * 	1 		Implement Trie (Prefix Tree)
 * 	2 		Word Break Problem
 * 	3 		Boggle
 * 	4 		Longest Common Prefix using Trie
 * 	5 		Find the maximum subarray XOR in a given array
 * 	6 		Count of distinct substrings of a string
 * 	7 		Find shortest unique prefix for every word in a given list
 * 	8 		Count inversions in an array
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "trie.h"

/*
 * Default function to get array index for a given char.
 * Note: Assumes that first allowed char in a word is 'a'.
 * 		 If you need different behavior write your own function
 * 		 and pass it as argument to the trie_create_trie() function.
 */
unsigned int trie_getindex_default(unsigned char c) {
	return c -'a';
}

/*
* Default inverse function to get char for a given array index.
* Note: Assumes that first allowed char in a word is 'a'.
* 		If you need different behavior write your own function
* 		and pass it as argument to the trie_create_trie() function.
*/
unsigned char trie_getchar_default(unsigned int index) {
	return (unsigned char)('a' + index);
}

 /*
  * Creates a new trienode instance.
  */
 struct trienode* trie_create_node(struct trie* t)
 {
	 // must reserve space to flexible array
 	 struct trienode* result = (struct trienode*)malloc(sizeof(*result) + t->array_size * sizeof(struct trienode));
 	 if (!result) {
 		 printf("Memory error: failed to allocate memory for trienode structure!");
 		 abort();
 	 }
 	 else {
		// initialize children to NULL
		for (int i = 0; i < t->array_size; ++i) {
			result->children[i] = NULL;
		}
		result->terminal = false;	// no word terminates here by now
 	 }

 	 return result;
 }

/*
 * Creates a trie instance.
 */
struct trie* trie_create_trie( size_t num_chars, trie_getindex getindexfunc,
							   trie_getchar getcharfunc )
{
	 struct trie* result = (struct trie*)malloc(sizeof(*result));
	 if (!result) {
		 printf("Memory error: failed to allocate memory for trienode structure!");
		 abort();
	 }
	 else {
		 result->array_size = num_chars;	// important: set before create root node

		 // create trie root node
		 struct trienode* rootnode = trie_create_node(result);
		 if (!rootnode) {
			 printf("Memory error: failed to allocate memory for trienode structure!");
			 free(result);
			 abort();
		 }
		 else {
			 result->root = (void*)malloc(sizeof(void*));
			 *(result->root) = rootnode;
			 result->getindex = getindexfunc ? getindexfunc : trie_getindex_default;
			 result->getchar = getcharfunc ? getcharfunc : trie_getchar_default;
		 }
	 }

	 return result;
}

/*
 * Inserts new text in the trie.
 * Returns 'true' if succeeded, 'false' otherwise.
 * Note: Duplicated words are not allowed.
 */
bool trie_insert(struct trie* t, char* signedtext)
{
	bool result = false;

	// trie empty?
	if (*(t->root) == NULL) {
		*(t->root) = trie_create_node(t);
	}

	// forces all characters to be unsigned rather than signed and
	// this prevents issues on some machines where we end up getting negative indexes
	// onto the lookup table.
	unsigned char* text = (unsigned char*)signedtext;

	struct trienode* current = *(t->root);
	struct trienode* newnode = NULL;
	int len = strlen(signedtext);

	for (int i = 0; i < len; ++i) {
		int index = t->getindex(text[i]);

		// exist prefix?
		if (current->children[index] == NULL) {
			newnode = trie_create_node(t);
			current->children[index] = newnode;
		}

		current = current->children[index];
	}

	// not duplicated text?
	if (!(current->terminal) && (current != *(t->root))) {
		current->terminal = true;	// mark has end of text
		result = true;
	}

	return result;
}

/*
 * Searches for a word in the trie.
 * Return 'true' if succeeded,'false' otherwise.
 */
bool trie_search(struct trie* t, char* signedtext)
{
	// forces all characters to be unsigned rather than signed and
	// this prevents issues on some machines where we end up getting negative indexes
	// onto the lookup table.
	unsigned char* text = (unsigned char*)signedtext;
	struct trienode* current = *(t->root);
	if (current == NULL)
		return false;

	int len = strlen(signedtext);
	for (int i = 0; i < len; ++i) {
		int index = t->getindex(text[i]);
		if (current->children[index] == NULL)
			return false;

		current = current->children[index];
	}

	return (current->terminal);
}

/*
 * Checks if a given node has less than X children trie nodes.
 */
bool trie_has_less_than_x_children(struct trienode* node, uint limit, size_t children_array_size) {
	if (node == NULL) return true;
	int count = 0;
	for (int i = 0; i < children_array_size; ++i) {
		if (node->children[i] != NULL) {
			if (++count == limit)
				return false;
		}
	}

	return true;
}

/*
 * Checks if a given node has more than one children trie nodes.
 */
bool trie_has_more_than_one_children(struct trienode* node, size_t children_array_size) {
	return !trie_has_less_than_x_children(node, 2, children_array_size);
}

/*
 * Deletes a word from the trie.
 * Returns 'true' if succeeded,'false' otherwise.
 *
 * 2 cases must be considered:
 * 	Case 1- The word is a prefix of other words in the trie.
 * 	Case 2- The word has a prefix that is shared by other words in the trie
 * 			or has no common prefix.
 *
 * 	In case 1, just set last word char node terminal flag to 'false'.
 * 	In case 2, remove all trie nodes after last common prefix and
 *			   if trie is empty remove root node and set pointer to NULL.
 */
bool trie_delete(struct trie* t, char* signedtext)
{
	struct trienode* currentnode = *(t->root);
	struct trienode* branchnode = *(t->root);

	if (currentnode == NULL)
		return false;

	// forces all characters to be unsigned rather than signed and
	// this prevents issues on some machines where we end up getting negative indexes
	// onto the lookup table.
	unsigned char* text = (unsigned char*)signedtext;
	int len = strlen(signedtext);
	struct trienode* removallist[255];	// should be max size of a word
	int count = 0;						// count number of nodes after last shared node
	int pos = 0;
	int index = 0;

	// traverse trie until end of word
	for (int i = 0; i < len; ++i) {
		index = t->getindex(text[i]);
		if (currentnode->children[index] == NULL)
			return false;	// word not exist in the trie

		// if is not a shared node add to removal list
		if (trie_has_more_than_one_children(currentnode, t->array_size)) {
			pos = i;
			branchnode = currentnode;
		}

		currentnode = currentnode->children[index];
	}


	if (!currentnode->terminal)
		return false;	// word no found in the trie
	else {
		// check case 1: word is a prefix of other words
		if (!trie_has_less_than_x_children(currentnode, 1, t->array_size)) {
			// case 1: word is a prefix of other words
			currentnode->terminal = false;	// to remove just turn flag to false
		}
		else {
			currentnode = branchnode;
			struct trienode* delnode = NULL;
			for (int i = pos; i < len; ++i) {
				index = t->getindex(text[i]);
				delnode = currentnode->children[index];
				removallist[count++] = delnode;
				currentnode->children[index] = NULL;	// clean index
				currentnode = delnode;
			}

			// remove all trie nodes after last shared node
			// remove nodes from list
			for (int i = count - 1; i > -1; --i)
				free(removallist[i]);

			// check if trie is empty
			currentnode = *(t->root);
			if (trie_has_less_than_x_children(currentnode, 1, t->array_size)) {
				free(currentnode);
				*(t->root) = NULL;
			}
		}

		return true;
	}

	return false;
}

/*
 * Helper recursive function to print trie in ascending order.
 */
void trie_print_rec( const struct trie* t, const struct trienode* node,
					 const size_t num_children, const unsigned char* prefix,
					 const int length )
{
	// extra space for new char plus null terminal char (0)
	unsigned char new_prefix[length + 2];
	memcpy(new_prefix, prefix, length);
	new_prefix[length + 1] = 0;

	// if terminal, a word is complete.
	if (node->terminal)
		printf("Word: '%s'\n", prefix);

	// even if a word is complete, there can be more words with current prefix,
	// so continue to see if there are any childrens
	for (int i = 0; i < num_children; ++i) {
		if (node->children[i] != NULL) {
			new_prefix[length] = t->getchar(i);	// append current char to prefix
			// recur
			trie_print_rec(t, node->children[i], (size_t)num_children, new_prefix, length + 1);
		}
	}
}

/*
 * Prints words of trie in ascending order.
 */
void trie_print(const struct trie* t)
{
	if (*(t->root) == NULL) {
		printf("TRIE EMPTY!");
		return;
	}

	trie_print_rec(t, *(t->root), t->array_size, NULL, 0);
}

/*
 * Releases trie nodes recursively.
 */
bool trie_destroy_children_rec(struct trie* t, struct trienode* node) {//, struct trienode* child) {
	if (node != NULL) {
		for (int i = 0; i < t->array_size; ++i)
			if (node->children[i] != NULL)
				if (trie_destroy_children_rec(t, node->children[i])) {
					struct trienode* delnode = node->children[i];
					node->children[i] = NULL;
					free(delnode);
				}

		return (trie_has_less_than_x_children(node, 1, t->array_size));
	}

	return false;
}

/*
 * Release trie from memory.
 */
void trie_destroy(struct trie* t) {
	if (*(t->root))
		if (trie_destroy_children_rec(t, *(t->root)))
			free(*(t->root));	// free parent node
	free(t->root);	// free pointer to root trienode**
	free(t);
}
