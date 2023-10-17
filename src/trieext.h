/*
 * trieext.h
 *
 *  Created on: 15/10/2023
 *      Author: Tiago C. Teixeira
 * Description: C headers for extend functions for trie data structure.
 */

#ifndef TRIEEXT_H_
	#define TRIEEXT_H_
	#include "arraylist.h"
	#include "trie.h"

	/*
	 * Gets a list of words that shares a given prefix.
	 * Returns an arraylist with founded words, 'NULL' if no word found.
	 */
	struct arraylist* trieext_getwords(struct trie* t, char* prefix);


#endif /* TRIEEXT_H_ */
