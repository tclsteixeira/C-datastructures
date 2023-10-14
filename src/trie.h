/*
 * trie.h
 *
 *  Created on: 11/10/2023
 *      Author: Tiago C. Teixeira
 * Description: C headers for Trie data structure.
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

#ifndef TRIE_H_
	#define TRIE_H_
	#include <stdbool.h>

	#define TRIE_DEFAULT_NUM_CHARS 26	// by default only chars from 'a' to 'z' (26 chars)

	// define function prototype to compute index associated to a given char
	typedef unsigned int (*trie_getindex)(const unsigned char c);

	// define inverse function prototype to compute char associated to a given index
 	typedef unsigned char (*trie_getchar)(const unsigned int index);

	// declares a trie node
	struct trienode {
		bool terminal;
		struct trienode* children[];
	};

	// declares trie structure
	struct trie {
		size_t array_size;
		struct trienode** root;
		trie_getindex getindex;		// if undefined, default method 'c' - 'a' will be used as index
		trie_getchar getchar;		// if undefined, default method 'a' + i will be used as index
	};

	/*
	 * Creates a trie instance.
	 */
	struct trie* trie_create_trie( size_t num_chars, trie_getindex getindexfunc,
								   trie_getchar getcharfunc );

	/*
	 * Inserts new text in the trie.
	 * Returns 'true' if succeeded, 'false' otherwise.
	 * Note: Duplicated words are not allowed.
	 */
	bool trie_insert(struct trie* t, char* signedtext);

	/*
	 * Searches for a word in the trie.
	 * Return 'true' if succeeded,'false' otherwise.
	 */
	bool trie_search(struct trie* t, char* signedtext);

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
	bool trie_delete(struct trie* t, char* signedtext);

	/*
	 * Prints words of trie in ascending order.
	 */
	void trie_print(const struct trie* t);

	/*
	 * Release trie from memory.
	 */
	void trie_destroy(struct trie* t);

#endif /* TRIE_H_ */
