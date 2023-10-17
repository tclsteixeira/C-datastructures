/*
 * trieext.c
 *
 *  Created on: 15/10/2023
 *      Author: Tiago C. Teixeira
 * Description: Trie data structure extension functions implemented in C.
 */

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "trie.h"
#include "arraylist.h"

/*
 * Recursively extract words from trie.
 */
void trieext_getwords_rec( struct trie* t, struct trienode* node,
						   char* text, int length, struct arraylist* a )
{
	if (node->terminal) {
		unsigned char* new_text = (unsigned char*)malloc(sizeof(char) * length + 1);
		memcpy(new_text, text, length);
		new_text[length] = 0;
		arraylist_add(a, new_text);
	}

	for (int i = 0; i < t->array_size; ++i)
		if (node->children[i]) {
			// extra space for new char plus null terminal char (0)
			char new_prefix[length + 2];
			memcpy(new_prefix, text, length);
			new_prefix[length] = t->getchar(i);
			trieext_getwords_rec(t, node->children[i], new_prefix, length+1, a);
		}
}

/*
 * Gets a list of words that shares a given prefix.
 * Returns an arraylist with founded words, 'NULL' if no word found.
 */
struct arraylist* trieext_getwords(struct trie* t, char* prefix)
{
	struct arraylist* result = NULL;
	struct trienode* currentnode = *(t->root);
	if (currentnode == NULL)
		return result;

	bool match = true;
	int len = strlen(prefix);
	for(int i = 0; i < len; ++i) {
		int index = t->getindex(prefix[i]);
		if (currentnode->children[index] == NULL) {
			match = false;
			break;
		}

		currentnode = currentnode->children[index];
	}

	if (match) {
		result = arraylist_create_capacity(20);

//		// create copy of prefix
//		char* cprefix = malloc(sizeof(char) * strlen(prefix));
		trieext_getwords_rec(t, currentnode, prefix, len, result);
	}

	return result;
}

