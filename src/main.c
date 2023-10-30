/*
 * main.c
 *
 *  Created on: 23/02/2023
 *      Author: Tiago C. Teixeira
 */

#include <stdio.h>
#include <limits.h>
#include <string.h>
#include "arraylist.h"
#include "binarysearch.h"
#include "circdbllinkedlist.h"
#include "circlinkedlist.h"
#include "linkedlist.h"
#include "dbllinkedlist.h"
#include "linkedlistqueue.h"
#include "linkedliststack.h"
#include "binarytree.h"
#include "binarysearchtree.h"
#include "avltree.h"
#include "redblacktree.h"
#include "heapstruct.h"
#include "minbinaryheap.h"
#include "maxbinaryheap.h"
#include "fibonacciheap.h"
#include "arraydeque.h"
#include "dbllinkedlistdeque.h"
#include "hashtable_lp.h"
#include "hashset.h"
#include "treeset.h"
#include "adjlgraph.h"
#include "indmindaryheap.h"
#include "bfsalg.h"
#include "dijkstrasp.h"
#include "trie.h"
#include "trieext.h"
#include "dfsalg.h"

/*
 * Depth-first search algorithm for adjacency list graph demo.
 * */
void dfsalg_demo()
{
	printf("_________\n");
	printf("DEPH-FIRST SEARCH ALGORITHM FOR ADJACENCY LIST GRAPH\n");
	printf("DEPH-FIRST SEARCH demo ------------\n");
	printf("\n");

	int n = 5;
	struct adjlgraph* g = adjlgraph_creategraph( n, DIRECTED_AGRAPH,
												 NULL, NULL,
												 NULL, NULL );
	// add 5 vertices
	for(int i = 0; i < n; ++i) {
		adjlgraph_addvertex(g, i, NULL);
	}

	adjlgraph_addedge( g, 0, 1, NULL, 4);
	adjlgraph_addedge( g, 0, 2, NULL, 5);
	adjlgraph_addedge( g, 1, 2, NULL, -2);
	adjlgraph_addedge( g, 1, 3, NULL, 6);
	adjlgraph_addedge( g, 2, 3, NULL, 1);
	adjlgraph_addedge( g, 2, 2, NULL, 10);	// Self loop

	/*
	// Create a fully connected graph
	//           (0)
	//           / \
	//        5 /   \ 4
	//         /     \
	// 10     <   -2  >
	//   +->(2)<------(1)      (4)
	//   +--- \       /
	//         \     /
	//        1 \   / 6
	//           > <
	//           (3)
	 */

	printf("\nPrint graph:\n");
	adjlgraph_print(g);
	printf("\n");

	ulong* countp = (ulong*)malloc(sizeof(ulong));
	dfsalg_countvertices(g, 0, countp);	// deph-first search rec algorithm
	printf("Recursive DFS node count starting at node 0: %lu\n", *countp);
	if (*countp != 4) printf("Error with DFS\n\n");

	dfsalg_countvertices_iteractive(g, 0, countp);	// deph-first search iteractive algorithm
	printf("Iteractive DFS node count starting at node 0: %lu\n", *countp);
	if (*countp != 4) printf("Error with DFS\n\n");

	dfsalg_countvertices(g, 4, countp);	// node 4 is disconnected
	printf("Recursive DFS node count starting at node 4: %lu\n", *countp);
	if (*countp != 1) printf("Error with DFS\n");

	dfsalg_countvertices_iteractive(g, 4, countp);	// node 4 is disconnected
	printf("Iteractive DFS node count starting at node 4: %lu\n", *countp);
	if (*countp != 1) printf("Error with DFS\n");

	free(countp);
	printf("\n");
	adjlgraph_destroy(g);
	printf("%s", "Adjaceny list graph destroyed successfully.\n");


	// Test function to find ancestors of each node in the graph
	printf("\nTesting find ancestors function\n");
	printf("\nCreating new graph\n");
	n = 5;
	g = adjlgraph_creategraph( n, DIRECTED_AGRAPH,
							   NULL, NULL,
							   NULL, NULL );
	// add 5 vertices
	for(int i = 0; i < n; ++i) {
		adjlgraph_addvertex(g, i, NULL);
	}

	adjlgraph_addedge( g, 0, 4, NULL, 0);
	adjlgraph_addedge( g, 4, 1, NULL, 0);
	adjlgraph_addedge( g, 4, 3, NULL, 0);
	adjlgraph_addedge( g, 1, 2, NULL, 0);

	printf("Print graph;\n");
	adjlgraph_print(g);

	/*
	// Create a fully connected graph
	//           (0)
	//             \
	//              \
	//               \
	//                >
	//      (2)       (4)----->(3)
	//        <       /
	//         \     /
	//          \   /
	//           \ <
	//           (1)
	 */

	printf("\n");
	printf("Finding ancestors of each vertice\n");
	struct dfsalgancestornode** ancestors = dfsalg_find_ancestors(g);

	// print results
	if (ancestors == NULL) {
		printf("Failed to find ancestors!\n");
	}
	else {
		printf("Print all vertices ancestors:\n");
		dfsalg_print_ancestors(ancestors, n);
	}

	printf("\n");
	dfsalg_destroy_ancestors(ancestors, n);
	printf("%s", "Ancestors list destroyed successfully.\n");
	adjlgraph_destroy(g);
	printf("%s", "Adjaceny list graph destroyed successfully.\n");
}

/*
 * Trie extensions demo.
 * */
void trie_extensions_demo()
{
	printf("_________\n");
	printf("TRIE EXTENSIONS\n");
	printf("Trie EXTENSIONS demo ------------\n");
	printf("\n");
	int numchars = 26;	// 'a'..'z'
	struct trie* t = trie_create_trie(numchars, NULL, NULL);

	// By default the trie only accepts lower case alphabet letters 'a' .. 'z'
	// To change this behavior you must provide your own functions the convert a letter to
	// an index and vice-versa.
	// Otherwise you can get negative array indexes.
	char* strings[9] = {"hello", "dog", "hell", "cat", "a", "hel", "help", "helps", "helping"};
	int n = 9;
	for (int i = 0; i < n; ++i) {
		printf("Insert '%s'\n", strings[i]);
		trie_insert(t, strings[i]);
	}

	printf("\nPrint trie:\n");
	trie_print(t);

	char prefix[] = "hel";
	struct arraylist* slist = NULL;
	// get auto sugestions for 'hel'
	slist = trieext_getwords(t, prefix);

	printf("\nAuto sugestions for prefix '%s':\n", prefix);
	if (slist == NULL)
		printf("NO SUGESTIONS FOUND!\n");
	else {
		for (int i = 0; i < slist->length; ++i) {
			char* sug = (char*)arraylist_get_item_at(slist, i);
			printf("%c%s%c\n", '"', sug, '"');
			free(sug);
		}

		arraylist_destroy(slist);	// free list
	}
//free(prefixp);
	printf("\n");
	trie_destroy(t);
	printf("%s", "Trie destroyed successfully.\n");
}

/*
 * Trie demo.
 * */
void trie_demo()
{
	printf("_________\n");
	printf("TRIE\n");
	printf("Trie demo ------------\n");
	printf("\n");
	int numchars = 26;	// 'a'..'z'
	struct trie* t = trie_create_trie(numchars, NULL, NULL);

	// By default the trie only accepts lower case alphabet letters 'a' .. 'z'
	// To change this behavior you must provide your own functions the convert a letter to
	// an index and vice-versa.
	// Otherwise you can get negative array indexes.
	char* strings[6] = {"kit", "cat", "jit", "cattle", "kin", "happy"};
	int n = 6;
	for (int i = 0; i < n; ++i) {
		printf("Insert '%s'\n", strings[i]);
		trie_insert(t, strings[i]);
	}

	printf("\nPrint trie:\n");
	trie_print(t);

	printf("\nSearch words:\n");
	printf("Search for '%s': %s\n", strings[3], trie_search(t, strings[3]) ? "FOUND" : "NOT FOUND"); // KIN
	printf("Search for '%s': %s\n", strings[1], trie_search(t, strings[1]) ? "FOUND" : "NOT FOUND"); // CAT
	printf("Search for '%s': %s\n", "kitten", trie_search(t, "kitten") ? "FOUND" : "NOT FOUND");	 // KITTEN
	printf("\n");

	if (trie_delete(t, "kin"))
		printf("Deleted word '%s'.\n", "kin");
	else
		printf("Failed to delete word '%s'.\n", "kin");

	if (trie_delete(t, "cat"))
		printf("Deleted word '%s'.\n", "cat");
	else
		printf("Failed to delete word '%s'.\n", "cat");

	printf("\nPrint trie:\n");
	trie_print(t);

	// delete all remaining words
	char* dwords[4] = {"cattle", "kit", "happy", "jit"};
	int n2 = 4;
	printf("\nRemoving all remaining words:\n");
	for (int i = 0; i < n2; ++i) {
		if (trie_delete(t, dwords[i]))
			printf("Deleted word '%s'.\n", dwords[i]);
		else
			printf("Failed to delete word '%s'.\n", dwords[i]);
	}

	printf("\nPrint trie:\n");
	trie_print(t);

	printf("\n\n");
	trie_destroy(t);
	printf("%s", "Trie destroyed successfully.\n");
}

/*
 * Adjacent list graph demo..
 * */
void adjlgraph_demo()
{

	printf("_________\n");
	printf("ADJACENCY LIST GRAPH\n");
	printf("Adjacency list graph demo ------------\n");

	printf("\nUses a list of vertices where each vertice stores a list of edges\n\n");
	int numvertices = 13;
	struct adjlgraph* ag = adjlgraph_creategraph( numvertices, UNDIRECTED_AGRAPH,
												  NULL, NULL,
												  NULL, NULL );

	// add vertices
	for (int i = 0; i < numvertices; ++i) {
		adjlgraph_addvertex(ag, i, NULL);
	}

	// add edges
	adjlgraph_addedge(ag, 0, 7, NULL, 1);
	adjlgraph_addedge(ag, 0, 9, NULL, 1);
	adjlgraph_addedge(ag, 0, 11, NULL, 1);
	adjlgraph_addedge(ag, 7, 11, NULL, 1);
	adjlgraph_addedge(ag, 7, 6, NULL, 1);
	adjlgraph_addedge(ag, 7, 3, NULL, 1);
	adjlgraph_addedge(ag, 6, 5, NULL, 1);
	adjlgraph_addedge(ag, 3, 4, NULL, 1);
	adjlgraph_addedge(ag, 2, 3, NULL, 1);
	adjlgraph_addedge(ag, 2, 12, NULL, 1);
	adjlgraph_addedge(ag, 12, 8, NULL, 1);
	adjlgraph_addedge(ag, 8, 1, NULL, 1);
	adjlgraph_addedge(ag, 1, 10, NULL, 1);
	adjlgraph_addedge(ag, 10, 9, NULL, 1);
	adjlgraph_addedge(ag, 9, 8, NULL, 1);


	printf("Print graph:\n");
	adjlgraph_print(ag);
	printf("\n");

	int start = 10, end = 5;
	int* res_size_p = malloc(sizeof(int));
	*res_size_p = -1;
	int* spath = bfsalg_shortest_path(ag, start, end, res_size_p);

	printf("Breadth first search shortest path from vertice %d to %d:\n", start, end);
	if (spath) {
		// print shortest path
		bfsalg_print_path(spath, *res_size_p);
		free(spath);
		printf("\n");
	} else {
		printf("No path found from '%d' to '%d'.\n", start, end);
	}

	free(res_size_p);
	adjlgraph_destroy(ag);
	printf("%s", "BFS adjacency list graph destroyed successfully.\n\n");

	printf("Dijkstra shortest path demo\n\n");
	printf("Create new directional graph:\n");

	numvertices = 5;
	ag = adjlgraph_creategraph( numvertices, DIRECTED_AGRAPH,
											 NULL, NULL,
											 NULL, NULL );

	// add vertices
	for (int i = 0; i < numvertices; ++i) {
		adjlgraph_addvertex(ag, i, NULL);
	}

	// add edges
	adjlgraph_addedge(ag, 0, 1, NULL, 4);	/*		 1				*/
	adjlgraph_addedge(ag, 0, 2, NULL, 1);	/*	  1/ |  \1			*/
	adjlgraph_addedge(ag, 1, 3, NULL, 1);	/*	 /	 |	 \   3     	*/
	adjlgraph_addedge(ag, 2, 1, NULL, 2);	/*	0   2|	  3----4	*/
	adjlgraph_addedge(ag, 2, 3, NULL, 5);	/*	 \	 |	 /			*/
	adjlgraph_addedge(ag, 3, 4, NULL, 3);	/*	 4\	 |	/1			*/
											/*		 2				*/
	printf("Print graph:\n");
	adjlgraph_print(ag);
	printf("\n");

	start = 0; end = 4;
	printf("Dijkstra shortest path from vertice '%d' to '%d':\n", start, end);
	printf("(constraints: non-negative edge weights)\n\n");

	// will store distance of start node to all other nodes
	double* dist = malloc(numvertices * sizeof(double));
	int* res_size2_p = (int*)malloc(sizeof(int));
	int* spathdij = dijkstrasp_adjlist_shortest_path(ag, start, end, dist, res_size2_p);

	if (spathdij) {
		printf("Distance from '%d' to '%d': %.1f\n", start, end, dist[end]);
		printf("Shortest distance from start node '%d' to all other nodes:\n", start);
		for (int i = 0; i < numvertices; ++i) {
			printf("'%d' to '%d' = %.1f\n", start, i, dist[i]);
		}

		printf("Dijkstra shortest path: ");
		// print shortest path
		dijkstrasp_print_path(spathdij, *res_size2_p);
		printf("\n");
	} else {
		printf("No path found from '%d' to '%d'.\n\n", start, end);
	}

	free(res_size2_p);
	free(dist);
	free(spathdij);
	adjlgraph_destroy(ag);
	printf("%s", "Dijkstra adjacency list graph destroyed successfully.\n");
}

/*
 * Treeset (ordered set) demo.
 * */
void treeset_demo()
{
	/*
	 * Compare function for treeset elements.
	 * Returns 0, 1 or -1.
	 */
	int compare(const void* key1, const void* key2) {
		if ((key1 == NULL) && (key2 == NULL)) return 0;
		else if (key1 == NULL) return -1;
		else if (key2 == NULL) return 1;
		else {
			int ikey1 = *((int*)key1);
			int ikey2 = *((int*)key2);

			if (ikey1 == ikey2) return 0;
			else if (ikey1 > ikey2) return 1;
			else return -1;
		}
	}

	/*
	 * Computes size of a set element in bytes.
	 * Note: Used by the reb-black tree.
	 */
	size_t calcelementsize(const void* data) {
		return sizeof(int);
	}

	/*
	 * Needed for red-black tree to perform operations like removing nodes.
	 */
	void copyelement( void* dest, const void* from ) {
		if (from)
			if (dest)
				*((int*)dest) = *((int*)from);
	}

	/*
	 * Prints a set element.
	 */
	void printelement(const void* element) {
		if (element) {
			int ivalue = *((int*)element);
			printf("%d", ivalue);
		}
	}

	printf("_________\n");
	printf("TREESET (ordered set)\n");
	printf("\nTreeset (with red-black tree) demo ------------\n");
	printf("Uses a red-black tree to store elements\n\n");
	struct treeset* set = treeset_create( calcelementsize, copyelement,
										  compare, printelement, NULL );

//	char spaces[] = "    ";
	int values[100];
	int n = 100;

	// insert values in treeset { 99, 98, 97, 96, 95, 94, 93, 92, 91, 90 }
	for (int i = 0; i < 10; ++i) {
		values[i] = (n-1) - i;
		treeset_add( set, &values[i] );
	}

	printf("Print treeset:\n");
	treeset_print( set , 0);

	printf( "\nTreeset size: %zu\n", set->size);

	// check if hashtable contains key '2'
	printf("Does treeset contains element '%d'?\n", values[2]);
	if (treeset_contains(set, &values[2]))
		printf("YES\n\n");
	else
		printf("NO\n\n");

	// remove element with values[2]
	printf("Element with value = '%d' will be removed from treeset.\n", values[2]);
	void* del = treeset_remove(set, &values[2]);
	if (del != NULL) {
		printf("Element '%d') was removed from treeset.\n",	*((int*)del));
	}
	else
		printf("Failed to remove element '%d' from treeset!\n", values[2]);

	// check if set contains element values[2]
	printf("\nDoes treeset contains value '%d'?\n", values[2]);
	if (treeset_contains(set, &values[2]))
		printf("YES\n\n");
	else
		printf("NO\n\n");

	printf("Treeset size: %zu\n", set->size);

	printf("\nPrint treeset:\n");
	treeset_print(set, 0);

	struct rbtree* tree = set->tree;
	printf("Root: %d\n\n", *((int*)tree->root->data));

	printf("\n");
	int test_values[] = { 4, 91, 99, 100 };
	int ntest = 4;

	// test floor
	for (int i = 0; i < ntest; i++) {
		void* floor = treeset_floor(set, set->tree->root, &test_values[i]);
		printf("Floor of '%d': ", test_values[i]);

		if (floor)
			printf("%d\n", *((int*)floor) );
		else
			printf("no value found.\n");
	}

	printf("\n");

	// test ceiling
	for (int i = 0; i < ntest; i++) {
		void* floor = treeset_ceiling(set, set->tree->root, &test_values[i]);
		printf("Ceiling of '%d': ", test_values[i]);

		if (floor)
			printf("%d\n", *((int*)floor) );
		else
			printf("no value found.\n");
	}

	printf("\n");

	if (set->size > 0) {
		void* min = treeset_min(set);
		if (min)
			printf("Min element: %d\n", *((int*)min));

		void* max = treeset_max(set);
		if (max)
			printf("Max element: %d\n", *((int*)max));
	}

	printf("\nPrint treeset in order:\n");
	treeset_print(set, 0);
	printf("Root: %d\n\n", *((int*)set->tree->root->data));

	// remove range of values between 93 and 97 from set
	int rem_range_lower = 93;
	int rem_range_upper = 97;

	printf("Remove range from '%d' to '%d'\n", 93, 97);
	int del_count = treeset_remove_range(set, &rem_range_lower, &rem_range_upper);

	printf("%d elements were removed from set.\n\n", del_count);
	printf("Treeset size: %zu\n", set->size);

	printf("\nPrint treeset descendent order:\n");
	treeset_print(set, 1);

	printf("\n");

	treeset_destroy(set);
	printf("%s", "Treeset (ordered set) destroyed successfully.\n");
}

/*
 * Hash table linked list demo.
 * */
void hashtable_linked_list_demo()
{
	int hashfunc(const void* key) {
		return *((int*)key);
	}

	int isequalfunc(const void* key1, const void* key2) {
		int i1 = *((int*)key1);
		int i2 = *((int*)key2);
		if (i1 == i2)
			return 1;
		else
			return 0;
	}

	void printitemfunc(const struct hashtable_keyvalue_pair* kvp) {
		if (kvp) {
			if (kvp->key) {
				int key = *((int*)kvp->key);
				printf("%d : ", key);
			}
			else
				printf("NULL : ");

			if (kvp->value) {
				int value = *((int*)kvp->value);
				printf("%d", value);
			}
			else
				printf("NULL");
		}
	}

	printf("_________\n");
	printf("HASHTABLE (linked lists version)\n");
	printf("\nHash table with linked lists demo ------------\n");
	printf("Uses linked lists to resolve hash index collisions\n\n");
	struct hashtable* htable = hashtable_create_default( hashfunc, isequalfunc,
														 printitemfunc, NULL );

	int keys[100];
	int values[100];
	int n = 100;

	// large set of key/value pairs to provoque array reallocations
	for (int i = 0; i < 10; ++i) {
		keys[i] = i;
		values[i] = (n-1) - i;
		hashtable_put(htable, &keys[i], &values[i]);
	}

	printf("Print hashtable:\n");
	hashtable_print(htable);

	printf( "\nHashtable size: %zu\n", htable->count );
	printf( "Hashtable capacity: %zu\n\n", htable->capacity );

	// check if hashtable contains key '2'
	printf("Does hashtable contains key '%d'?\n", keys[2]);
	if (hashtable_contains(htable, &keys[2]))
		printf("YES\n\n");
	else
		printf("NO\n\n");

	// remove element with key=2
	printf("Element with key = '%d' will be removed from hashtable.\n", keys[2]);
	void* del = hashtable_remove(htable, &keys[2]);
	if (del != NULL) {
		printf("Element (key = '%d' : value = '%d') removed from hashtable.\n",
							*((int*)((struct hashtable_lp_keyvalue_pair*)del)->key),
							*((int*)((struct hashtable_lp_keyvalue_pair*)del)->value));
		free(del);
	}
	else
		printf("Failed to remove element from hashtable!\n");

	// check if set contains element '2' (keys[2])
	printf("\nDoes hashtable contains key '%d'?\n", keys[2]);
	if (hashtable_contains(htable, &keys[2]))
		printf("YES\n\n");
	else
		printf("NO\n\n");

	printf("Hashtable size: %zu\n", htable->count);

	printf("\nPrint hashtable:\n");
	hashtable_print(htable);

	void* val = hashtable_get(htable, &keys[3]);
	printf("\nGet value with key '%d': %d.\n", keys[3], *((int*)(((struct hashtable_keyvalue_pair*)(val))->value) ) );

	hashtable_destroy(htable);
	printf("%s", "Hash table (linked lists) destroyed successfully.\n\n");
}

/*
 * Hash table with linear probing demo.
 * */
void hashtable_lp_demo()
{
	int hashfunc(const void* key) {
		return *((int*)key);
	}

	int isequalfunc(const void* key1, const void* key2) {
		int i1 = *((int*)key1);
		int i2 = *((int*)key2);
		if (i1 == i2)
			return 1;
		else
			return 0;
	}

	void printitemfunc(const struct hashtable_lp_keyvalue_pair* kvp) {
		if (kvp) {
			if (kvp->key) {
				int key = *((int*)kvp->key);
				printf("%d : ", key);
			}
			else
				printf("NULL : ");

			if (kvp->value) {
				int value = *((int*)kvp->value);
				printf("%d", value);
			}
			else
				printf("NULL");
		}
	}

	printf("_________\n");
	printf("HASHTABLE (linear probe version)\n");
	printf("\nHash table with linear probe demo ------------\n");
	printf("Uses linear probing technique to resolve hash index collisions\n\n");

	struct hashtable_lp* htable = hashtable_lp_create_default( hashfunc, isequalfunc,
															   printitemfunc, NULL );

	int keys[100];
	int values[100];
	int n = 100;

	// large set of key/value pairs to provoque array reallocations
	for (int i = 0; i < 10; ++i) {
		keys[i] = i;
		values[i] = (n-1) - i;
		hashtable_lp_put(htable, &keys[i], &values[i]);
	}

	printf("Print hashtable:\n");
	hashtable_lp_print(htable);

	printf( "\nHashtable size: %zu\n", htable->count );
	printf( "Hashtable capacity: %zu\n\n", htable->capacity );

	// check if hashtable contains key '2'
	printf("Does hashtable contains key '%d'?\n", keys[2]);
	if (hashtable_lp_contains(htable, &keys[2]))
		printf("YES\n\n");
	else
		printf("NO\n\n");

	// remove element with key=2
	printf("Element with key = '%d' will be removed from hashtable.\n", keys[2]);
	void* del = hashtable_lp_remove(htable, &keys[2]);
	if (del != NULL) {
		printf("Element (key = '%d' : value = '%d') removed from hashtable.\n",
							*((int*)((struct hashtable_lp_keyvalue_pair*)del)->key),
							*((int*)((struct hashtable_lp_keyvalue_pair*)del)->value));
		free(del);
	}
	else
		printf("Failed to remove element from hashtable!\n");

	// check if set contains element '2' (keys[2])
	printf("\nDoes hashtable contains key '%d'?\n", keys[2]);
	if (hashtable_lp_contains(htable, &keys[2]))
		printf("YES\n\n");
	else
		printf("NO\n\n");

	printf("Hashtable size: %zu\n", htable->count);

	printf("\nPrint hashtable:\n");
	hashtable_lp_print(htable);

	void* val = hashtable_lp_get(htable, &keys[3]);
	printf("\nGet value with key '%d': %d.\n", keys[3], *((int*)(val)) );

	hashtable_lp_destroy(htable);
	printf("%s", "Hash table (linear probe) destroyed successfully.\n\n");
}

/*
 * Double linked list deque demo.
 * */
void hashset_demo() {

//	// constant between 0 and 1 (A=(√5-1)/2 suggested by Knuth).
//	const double A = (2.2360679775 - 1) / 2;

	/*
	 * Computes hash value
	 */
	int hashfunc(const void* element)
	{
		int key = *((int*)(element));
		return key;
	}

	/*
	 * Checks for equality
	 * */
	int isequal(const void* a, const void* b) {
		if (*(int*)a == *(int*)b)
			return 1;
		else
			return 0;
	}

	/*
	 * Prints key/value pair data
	 * */
	void printelement(void* element)
	{
		if (element) {
			printf("%d", *((int*)element));
		}
	}

	printf("___________\n");
	printf("HASHSET \n\n");
	printf("HASHSET (unordered set) demo -----------\n\n");

	// Set initialization
	struct hashset* set = hashset_create(hashfunc, isequal, printelement, NULL);

//	int intdata[] = { 10, 5, 15, 5 };
//	int n = sizeof(intdata) / sizeof(int);
//
//	// add elements to the set
//	for (int i = 0; i < n; ++i) {
//		hashset_add(set, &intdata[i]);
//	}

	int intdata[100];

	// add elements to the set
	for (int i = 0; i < 100; ++i) {
		intdata[i] = i;
		hashset_add(set, &intdata[i]);
	}

	printf("Print set:\n");
	hashset_print(set);

	printf("\nSize of set: %zu\n\n", hashset_getsize(set));

	// check if set contains element '2' (intdata[2])
	printf("Does set contains element '%d'?\n", intdata[2]);
	if (hashset_contains(set, &intdata[2]))
		printf("YES\n\n");
	else
		printf("NO\n\n");

	// remove element 2
	printf("Element '%d' will be removed from set.\n", intdata[2]);
	void* del = hashset_remove(set, &intdata[2]);
	if (del != NULL) {
		printf("Element '%d' removed from set.\n", *((int*)del));
	}
	else
		printf("Failed to remove element from set!\n");

	// check if set contains element '2' (intdata[2])
	printf("\nDoes set contains element '%d'?\n", intdata[2]);
	if (hashset_contains(set, &intdata[2]))
		printf("YES\n\n");
	else
		printf("NO\n\n");

	printf("Size of set: %zu\n", hashset_getsize(set));

	printf("\nPrint set:\n");
	hashset_print(set);

	hashset_destroy(set);
	printf("\nHashset destroyed successfully.\n");
}

/*
 * Double linked list deque demo.
 * */
void dbllinkedlistdeque_demo() {

//	/*
//	 * Checks for equality
//	 * */
//	int isequal(const void* a, const void* b) {
//		if (*(int*)a == *(int*)b)
//			return 1;
//		else
//			return 0;
//	}

	/*
	 * Prints node data
	 * */
	void printdata(void* data)
	{
		if (data) {
			printf("%d", *((int*)data));
		}
	}

	printf("___________\n");
	printf("DOUBLE LINKED LIST DEQUE\n\n");
	printf("DOUBLE LINKED LIST DEQUE demo -----------\n\n");

	// Deque initialization
	struct dbllinkedlistdeque* q = dbllinkedlistdeque_create(printdata, NULL);

	int intdata[] = { 5, 10, 15 };

	// insert 5 at front
	printf("Insert element '%d' at rear end\n", intdata[0]);
	dbllinkedlistdeque_push_back(q, &intdata[0]);
	// insert 10 at back
	printf("Insert element '%d' at rear end\n", intdata[1]);
	dbllinkedlistdeque_push_back(q, &intdata[1]);

	printf("Rear end element: ");
	printdata(dbllinkedlistdeque_back(q)); printf("\n");

	dbllinkedlistdeque_pop_back(q);
	printf("After deleting rear element, new rear is: ");
	printdata(dbllinkedlistdeque_back(q)); printf("\n");

	printf("Inserting element '%d' at front end \n", intdata[2]);
	dbllinkedlistdeque_push_front(q, &intdata[2]);

	printf("Front end element: ");
	printdata(dbllinkedlistdeque_front(q)); printf("\n");

	printf("Number of elements in Deque: %ld\n", dbllinkedlistdeque_size(q));

	dbllinkedlistdeque_pop_front(q);
	printf("After deleting front element, new front is: ");
	printdata(dbllinkedlistdeque_front(q)); printf("\n");

	dbllinkedlistdeque_destroy(q);
	printf("Double linked list deque destroyed successfully.\n");
}

/*
 * Array deque demo.
 * */
void arraydeque_demo() {

	/*
	 * Prints node data
	 * */
	void printdata(void* data)
	{
		if (data) {
			printf("%d", *((int*)data));
		}
	}

	printf("___________\n");
	printf("ARRAY DEQUE\n\n");
	printf("ARRAY DEQUE demo -----------\n\n");

	// Deque initialization
	struct arraydeque* q = arraydeque_create(printdata, NULL);

	int n = 19;
	int intdata[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17, 18 };

	// Iterate range [1, 9],
	// push even numbers at the back
	// and push odd numbers at the front
	for (int i = 1; i < n; i++)
		if (i % 2 == 0)
			arraydeque_push_back(q, &intdata[i]);
		else
			arraydeque_push_front(q, &intdata[i]);

	// Print the current capacity
	printf("Current capacity: %ld\n", q->capacity);

	// Print the current size
	printf("Current size: %ld\n", q->size);

	// Print front element of deque
	printf("Front element: ");
	printdata(arraydeque_front(q));
	printf("\n");

	// Print last element of deque
	printf("Rear element: ");
	printdata(arraydeque_back(q));
	printf("\n\n");

	printf("Pop an element from front\n");
	void* popfront = arraydeque_pop_front(q);
	printf("Poped front element: ");
	printdata(popfront);
	printf("\n");

	printf("Pop an element from back\n");
	void* popback = arraydeque_pop_back(q);
	printf("Poped back element: ");
	printdata(popback);
	printf("\n\n");

	// Print the current capacity
	printf("Current capacity: %ld\n", q->capacity);

	// Print the current size
	printf("Current size: %ld\n", q->size);

	// Print front element of deque
	printf("Front element: ");
	printdata(arraydeque_front(q));
	printf("\n");

	// Print last element of deque
	printf("Rear element: ");
	printdata(arraydeque_back(q));
	printf("\n\n");

	arraydeque_destroy(q);
	printf("Array deque destroyed successfully.\n");
}

/*
 * Fibonacci heap demo.
 * */
void fibonacciheap_demo() {

	/*
	 * Function to compare key with given data.
	 * Returns 1 if key1 > key2, -1 if key1 < key2, 0 if is equal.
	 * */
	int compare(const void* key1, const void* key2) {

		if ((key1 == NULL) && (key2 == NULL))
			return 0;
		else if (key1 == NULL)
			return -1;
		else if (key2 == NULL)
			return 1;
		else {
			int ikey1 = *((int*)(key1));
			int ikey2 = *((int*)(key2));

			if (ikey1 == ikey2)
				return 0;
			else if (ikey1 > ikey2)
				return 1;
			else
				return -1;
		}
	}

	/*
	 * Prints node data
	 * */
	void printdata(void* data)
	{
		if (data) {
			printf("%d", *((int*)data));
		}
	}

	printf("___________\n");
	printf("FIBONACCI HEAP\n");
	printf("\nFIBONACCI HEAP demo -----------\n\n");

	int minval = INT_MIN;
	int intdata[] = {5, 2, 8};
	int eight = intdata[2];
	int n = 3;	//sizeof(intdata) / sizeof(intdata[0]);
	printf("Creating an initial empty heap\n");
	struct fibheap* fh = fibheap_create((void*)(&minval), compare, printdata, NULL);

	printf("Load heap with elements in the following order:\n");
	for (int i = 0; i < n; ++i) {
		printf("%d ", intdata[i]);
		fibheap_insert(fh, &intdata[i]);
	}

	printf("\n\n");
	fibheap_print(fh);
	/*
	 * Root nodes: 2-->5-->8
	 *
	 * */

	// Now we will extract the minimum value node from the heap
	printf("Extracting min\n");
	struct fibheapnode* mini1 = fibheap_extract_min(fh);
	printf("Min = %d\n\n", *((int*)(mini1->key)));

	fibheap_print(fh);
	/*
	 * Root nodes: 5
	 **/

	// Now we will decrease the value of node '8' to '7'
	int seven = 7;
	printf("Decrease value of 8 to 7\n");
	fibheap_find_and_decrease(fh, fh->mini, &eight, &seven);
	fibheap_print(fh);
	/*
	 * Root nodes: 5
	 **/

	// Now we will delete the node '7'
	printf("Delete the node 7\n");
	struct fibheapnode* delnode = fibheap_delete(fh, &seven);
	printf("Node '%d' deleted from heap.\n", *((int*)(delnode->key)));

	fibheap_print(fh);
	/*
	 * Root nodes: 5
	 **/

	struct fibheap* fh1 = fibheap_create(&minval, compare, printdata, NULL);
	struct fibheap* fh2 = fibheap_create(&minval, compare, printdata, NULL);
	int intdata1[] = {3, 11}; int n1 = 2;
	int intdata2[] = {7, 19}; int n2 = 2;

	printf("Load heap 1 with elements in the following order:\n");
	for (int i = 0; i < n1; ++i) {
		printf("%d ", intdata1[i]);
		fibheap_insert(fh1, &intdata1[i]);
	}

	printf("\n\n");
	fibheap_print(fh1);
	/*
	 * Root nodes: 3-->11
	 * */

	printf("Load heap 2 with elements in the following order:\n");
	for (int i = 0; i < n2; ++i) {
		printf("%d ", intdata2[i]);
		fibheap_insert(fh2, &intdata2[i]);
	}

	printf("\n\n");
	fibheap_print(fh2);
	/*
	 * Root nodes: 7-->19
	 * */

	printf("Union of heap 1 with heap 2 (heap 1 is the result union)\n");
	printf("Heap 2 instance have now zero nodes and still is available.\n\n");

	fh1 = fibheap_union(fh1, fh2);	// merge heap 1 with heap 2

	printf("Print heap 1:\n");
	fibheap_print(fh1);
	/*
	 * Root nodes: 3-->11-->7-->19
	 * */

	printf("Print heap 2:\n");
	fibheap_print(fh2);
	printf("\n\n");
	/*
	 * Root nodes: The heap is empty
	 * */

	fibheap_destroynode(fh, mini1);
	fibheap_destroynode(fh, delnode);

	fibheap_destroy(fh);
	printf("Fibonacci heap destroyed successfully.\n");

	fibheap_destroy(fh1);
	printf("Fibonacci heap 1 destroyed successfully.\n");

	fibheap_destroy(fh2);
	printf("Fibonacci heap 2 destroyed successfully.\n\n");
}

/*
 * Binary heap array demo.
 * */
void binaryheaparray_demo() {

	/*
	 * Function to compare key with given data.
	 * Returns 1 if data > key, -1 if data < key, 0 if is equal.
	 * */
	int compare(const void* data, const void* key) {

		if ((data == NULL) && (key == NULL))
			return 0;
		else if (data == NULL)
			return -1;
		else if (key == NULL)
			return 1;
		else {
			//struct binarytreenode* datanode = (struct binarytreenode*)data;
			int idata = *((int*)(data));
			int ikey = *((int*)key);

			if (idata == ikey)
				return 0;
			else if (idata > ikey)
				return 1;
			else
				return -1;
		}
	}

	/*
	 * Prints node data
	 * */
	void printdata(void* data)
	{
		if (data) {
			printf("%d", *((int*)data));
		}
	}

	printf("___________\n");
	printf("BINARY HEAP ARRAY\n");
	printf("\nBINARY HEAP ARRAY demo -----------\n\n");

	int intdata[] = {3,2,15,5,4,45};
	int n = 6;	//sizeof(intdata) / sizeof(intdata[0]);

	void* datalist[] = { &intdata[0], &intdata[1], &intdata[2], &intdata[3],
						  &intdata[4], &intdata[5] };

	int capacity = 11;

	int* max = (int*)malloc(sizeof(int));
	*max = INT_MAX;
	int* min = (int*)malloc(sizeof(int));
	*min = INT_MIN;

	printf("\nMIN BINARY HEAP -----------\n\n");

	// create empty min heap
	struct heap* minbinaryheap = minbinaryheap_createHeap(capacity, NULL, 0,
														(void*)min, (void*)max,
														compare, printdata, NULL);

	printf("Min binary heap created successfully (empty)\n");
	printf("Heap size: %d\n\n", minbinaryheap->size);
	printf("Load heap with elements in the following order:\n");

	for (int i = 0; i < n; ++i) {
		printf("%d ", intdata[i]);
	}

	printf("\n\n");

	for (int i = 0; i < n; ++i) {
		minbinaryheap_insert(minbinaryheap, datalist[i]);
	}

	printf("Heap size: %d\n\n", minbinaryheap->size);
	printf("Print heap (level ordered):\n");
	minbinaryheap_print(minbinaryheap);
	printf("\n");
	/*
	 *  Level order: 2 3 15 5 4 45
	 *
	 *           	   2
	 *	       3              15
	 * 	   5      4        45
	 *
	 * */

	printf("Heap size: %d\n", minbinaryheap->size);
	printf("Extract min value: %d\n\n", *((int*)(minbinaryheap_extract(minbinaryheap))));

	printf("Print heap (level ordered):\n");
	minbinaryheap_print(minbinaryheap);
	printf("\n");
	/*
	 *  Level order: 3 4 15 5 45
	 *
	 *              3
	 *	       4         15
	 * 	    5	 45
	 *
	 * */

	printf("Peek current min value: %d\n", *((int*)(minbinaryheap_peek(minbinaryheap))));
	printf("Decrease key at index 2 = '%d' to value '1'\n", *((int*)(minbinaryheap->arr[2])));
	int* p1 = malloc(sizeof(int));
	*p1 = 1;
	minbinaryheap_decreasekey(minbinaryheap, 2, p1);

	printf("Print heap (level ordered):\n");
	minbinaryheap_print(minbinaryheap);
	printf("\n");
	/*
	 *  Level order: 1 4 3 5 45
	 *
	 *              1
	 *	       4         3
	 * 	    5	 45
	 *
	 * */

	printf("Delete value at index 1 from heap:\n");
	minbinaryheap_delete(minbinaryheap, 1);
	printf("Print heap (level ordered):\n");
	minbinaryheap_print(minbinaryheap);
	printf("\n");
	/*
	 *  Level order: 1 5 3 45
	 *
	 *              1
	 *	       5         3
	 * 	    45
	 *
	 * */

	printf("Peek current min value: %d\n", *((int*)minbinaryheap_peek(minbinaryheap)));
	minbinaryheap_destroy(minbinaryheap);

	printf("Min binary heap destroyed successfully.\n\n");

	printf("--------------------------------------------------\n");
	printf("--------------------------------------------------\n");

	printf("\nMAX BINARY HEAP -----------\n\n");

	// create empty max heap
	struct heap* maxbinaryheap = maxbinaryheap_createHeap(capacity, NULL, 0,
														(void*)min, (void*)max,
														compare, printdata, NULL);

	printf("Max binary heap created successfully (empty)\n");
	printf("Heap size: %d\n\n", maxbinaryheap->size);
	printf("Load heap with elements in the following order:\n");

	for (int i = 0; i < n; ++i) {
		printf("%d ", intdata[i]);
	}

	printf("\n\n");

	for (int i = 0; i < n; ++i) {
		maxbinaryheap_insert(maxbinaryheap, datalist[i]);
	}

	printf("Heap size: %d\n\n", maxbinaryheap->size);
	printf("Print heap (level ordered):\n");
	maxbinaryheap_print(maxbinaryheap);
	printf("\n");
	/*
	 *  Level order: 45 5 15 2 4 3
	 *
	 *           	  45
	 *	       5              15
	 * 	   2      4        3
	 *
	 * */

	printf("Heap size: %d\n", maxbinaryheap->size);
	printf("Extract max value: %d\n\n", *((int*)(maxbinaryheap_extract(maxbinaryheap))));

	printf("Print heap (level ordered):\n");
	maxbinaryheap_print(maxbinaryheap);
	printf("\n");
	/*
	 *  Level order: 15 5 3 2 4
	 *
	 *              15
	 *	       5         3
	 * 	    2	 4
	 *
	 * */

	*p1 = 100;
	printf("Peek current max value: %d\n", *((int*)(maxbinaryheap_peek(maxbinaryheap))));
	printf("Increase key at index 2 = '%d' to value '%d'\n", *((int*)(maxbinaryheap->arr[2])), *p1);

	maxbinaryheap_increasekey(maxbinaryheap, 2, p1);

	printf("Print heap (level ordered):\n");
	maxbinaryheap_print(maxbinaryheap);
	printf("\n");
	/*
	 *  Level order: 100 5 15 2 4
	 *
	 *              100
	 *	       5         15
	 * 	    2	 4
	 *
	 * */

	printf("Delete value '5' at index 1 from heap:\n");
	maxbinaryheap_delete(maxbinaryheap, 1);
	printf("Print heap (level ordered):\n");
	maxbinaryheap_print(maxbinaryheap);
	printf("\n");
	/*
	 *  Level order: 100 4 15 2
	 *
	 *             100
	 *	       4         15
	 * 	    2
	 *
	 * */

	printf("Peek current max value: %d\n", *((int*)maxbinaryheap_peek(maxbinaryheap)));
	maxbinaryheap_destroy(maxbinaryheap);
	printf("Max binary heap destroyed successfully.\n\n");

	free(p1);
	free(max);
	free(min);
}

/*
 * Red-black tree demo.
 * */
void rbtree_demo() {

	/*
	 * Calculates size of data in bytes
	 * Note: You can't do sizeof(*data) because returns always 1.
	 * */
	size_t calcdatasize(const void* data) {
		return sizeof(*((int *)data));
	}

	/*
	 * Function to compare key with given data.
	 * Returns 1 if data > key, -1 if data < key, 0 if is equal.
	 * */
	int compare(const void* data, const void* key) {

		if ((data == NULL) && (key == NULL))
			return 0;
		else if (data == NULL)
			return -1;
		else if (key == NULL)
			return 1;
		else {
			//struct binarytreenode* datanode = (struct binarytreenode*)data;
			int idata = *((int*)(data));
			int ikey = *((int*)key);

			if (idata == ikey)
				return 0;
			else if (idata > ikey)
				return 1;
			else
				return -1;
		}
	}

	/*
	 * Prints node data
	 * */
	void printdata( const void* data ) {
		if (data) {
			printf("%d", *((int*)data));
		}
	}

	/*
	 * (hard) copy data from source to dest
	 * */
	void copydata(void* dest, const void* from) {
		if (dest) {
			if (from) {
				*((int*)dest) = *((int*)from);
			}
		}
	}

	printf("___________\n");
	printf("RED-BLACK TREE\n");
	printf("\nRED-BLACK TREE demo -----------\n\n");

	int intdata[] = {7,3,18,10,22,8,11,26,2,6,13};
	int n = sizeof(intdata) / sizeof(intdata[0]);

	// create empty tree (no root)
	struct rbtree* tree = rbtree_create( NULL, calcdatasize, compare, NULL,
										 printdata, copydata );

	printf("Red-black tree created successfully (empty).\n");
	printf("Tree size: %d\n\n", rbtree_getSizeIt(tree));
//	printf("Build red-black tree with elements in the following order:\n");

//	for (int i = 0; i < n; ++i) {
//		printf("%d ", intdata[i]);
//	}

//	printf("\n\n");

	printf("Inserting elements in the red-black tree:\n");
	for (int i = 0; i < n; ++i) {
		if (rbtree_insert(tree, &intdata[i]))
			printf("Value '%d' inserted successfully.\n", intdata[i]);
		else
			printf("Error: Value '%d' could not be inserted.\n", intdata[i]);
	}

	printf("\nPrint tree:\n\n");
	rbtree_print(tree, "  ");
	printf("\n");
	/*
	 *  Level order: 10 7 18 3 8 11 22 2 6 13 26
	 *
	 *           	   10
	 *	       7              18
	 * 	   3      8       11      22
	 *   2   6 	            13      26
	 *
	 * */

	printf("Tree size (iterative alg): %d\n", rbtree_getSizeIt(tree));

	// search '1'
	int* intp = &intdata[10];
	printf("Search value '%d': ", *intp);
	struct rbtreenode* n0 = rbtree_search(tree, tree->root, intp);
	if (n0 != NULL)
		printf("Found value '%d'.\n", *((int*)(n0->data)));
	else
		printf("Not found :(?\n");

	// printf("Tree deep using rec alg (max number of edges from root to deepest leaf node): %d\n", bst_findNode(tree->root));
	printf("Height of tree (max number of edges from deepest leaf node to root node): ");
	printf("%d\n\n", rbtree_treeHeightLevelOrder(tree));

	// root has depth 0
	printf("Node '%d' depth: %d\n", *((int*)(tree->root->data)),
			rbtree_findNodeDepth(tree, tree->root, tree->root->data));
	// '5' node has depth 1
	printf("Node '%d' depth: %d\n", intdata[4], rbtree_findNodeDepth(tree, tree->root, (void*)(&intdata[4])));
	// '6' node has depth 2
	printf("Node '%d' depth: %d\n", intdata[5], rbtree_findNodeDepth(tree, tree->root, (void*)(&intdata[5])));
	// root has height 2
	printf("Node '%d' height: %d\n", *((int*)(tree->root->data)),
			rbtree_findNodeHeight(tree, tree->root->data));
	// '5' node has height 1
	printf("Node '%d' height: %d\n", intdata[4],
			rbtree_findNodeHeight(tree, (void*)(&intdata[4])));
	// '6' node has height 0
	printf("Node '%d' height: %d\n\n", intdata[5],
			rbtree_findNodeHeight(tree, (void*)(&intdata[5])));


	// delete nodes test
	int dellist[] = {18, 11, 3, 10, 22};
	printf("Delete values: ");
	for (int i = 0; i < 5; ++i) {
		printf("%d ", dellist[i]);
	}

	printf("\n\n");
//	int* success = malloc(sizeof(int));

	// delete nodes with values in delete list
	for (int i = 0; i < 5; ++i) {
//		*success = 1;
		void* del = rbtree_delete(tree, (void*)(&dellist[i]));//, success);

//		if (!(*success))
		if (!del)
			printf("Failed to delete '%d' from tree.\n\n", dellist[i]);
		else
		{
			printf("'%d' deleted successfully from tree.\n", *((int*)del) );
			printf("Print tree:\n\n");
			rbtree_print(tree, "  ");
//			printf("\n");
		}

		printf("-----------------\n");
	}

//	free(success);
	printf("\n");

	// Bug in Morris alg (wrong results in unbalanced trees)
    //	printf("Morris alg, height= %d\n\n", binarytree_findHeightMorrisTrav(tree->root));// findHeightMorrisTrav(tree->root));

	printf("Tree size (iterative alg): %d\n", rbtree_getSizeIt(tree));

	rbtree_destroy(tree);
	printf("Red-black tree destroyed successfully.\n");
}

/*
 * AVL tree demo.
 * */
void avltree_demo() {

	/*
	 * Function to compare key with given data.
	 * Returns 1 if data > key, -1 if data < key, 0 if is equal.
	 * */
	int compare(void* data, const void* key) {

		if ((data == NULL) && (key == NULL))
			return 0;
		else if (data == NULL)
			return -1;
		else if (key == NULL)
			return 1;
		else {
			//struct binarytreenode* datanode = (struct binarytreenode*)data;
			int idata = *((int*)(data));
			int ikey = *((int*)key);

			if (idata == ikey)
				return 0;
			else if (idata > ikey)
				return 1;
			else
				return -1;
		}
	}

	/*
	 * Prints node data
	 * */
	void printnode(struct avltreenode* node) {
		if (node) {
			void* data = node->data;
			if (data) {
				printf("%d", *((int*)data));
			}
		}
	}

	/*
	 * (hard) copy data from source to dest
	 * */
	void copydata(void* dest, const void* from) {
		if (dest) {
			if (from) {
				*((int*)dest) = *((int*)from);
			}
		}
	}

	printf("___________\n");
	printf("AVL TREE\n");
	printf("\nAVL TREE demo -----------\n\n");

	int intdata[] = {1,2,3,4,5,6,7};
	int n = sizeof(intdata) / sizeof(intdata[0]);

	// put '3' as root
	struct avltree* tree = avltree_create(&intdata[0], compare, NULL,
			printnode, copydata);

	printf("AVL tree created successfully with root = '%d'\n", *((int*)(tree->root->data)));
	printf("Tree size: %d\n\n", avltree_getSizeIt(tree));
	printf("Build avl tree with elements in the following order:\n");

	for (int i = 0; i < n-1; ++i) {
		printf("'%d' ", intdata[i]);
	}

	printf("\n\n");

	tree->root = avltree_insert(tree, tree->root, &intdata[1]);	// 2
	tree->root = avltree_insert(tree, tree->root, &intdata[2]);	// 3
	tree->root = avltree_insert(tree, tree->root, &intdata[3]);	// 4
	tree->root = avltree_insert(tree, tree->root, &intdata[4]);	// 5
	tree->root = avltree_insert(tree, tree->root, &intdata[5]);	// 6

	printf("Print tree:\n\n");
	avltree_print(tree, "  ");
	printf("\n");
	/*
	 *           4
	 *		  2     5
	 * 	    1   3     6
	 *
	 * */

	printf("Tree size (iterative alg): %d\n", avltree_getSizeIt(tree));

	// search '1'
	int* intp = &intdata[0];
	printf("Search value '%d': ", *intp);
	struct avltreenode* n0 = avltree_search(tree, tree->root, intp);
	if (n0 != NULL)
		printf("Found value '%d'.\n", *((int*)(n0->data)));
	else
		printf("Not found :(?\n");

	// printf("Tree deep using rec alg (max number of edges from root to deepest leaf node): %d\n", bst_findNode(tree->root));
	printf("Height of tree (max number of edges from deepest leaf node to root node): ");
	printf("%d\n\n", avltree_treeHeightLevelOrder(tree));

	// root has depth 0
	printf("Node '%d' depth: %d\n", *((int*)(tree->root->data)),
			avltree_findNodeDepth(tree, tree->root->data));
	// '5' node has depth 1
	printf("Node '%d' depth: %d\n", intdata[4], avltree_findNodeDepth(tree, (void*)(&intdata[4])));
	// '6' node has depth 2
	printf("Node '%d' depth: %d\n", intdata[5], avltree_findNodeDepth(tree, (void*)(&intdata[5])));
	// root has height 2
	printf("Node '%d' height: %d\n", *((int*)(tree->root->data)),
			avltree_findNodeHeight(tree, tree->root->data));
	// '5' node has height 1
	printf("Node '%d' height: %d\n", intdata[4],
			avltree_findNodeHeight(tree, (void*)(&intdata[4])));
	// '6' node has height 0
	printf("Node '%d' height: %d\n\n", intdata[5],
			avltree_findNodeHeight(tree, (void*)(&intdata[5])));


	// delete '4' node
	int n3 = intdata[3];
	printf("Delete node '%d'\n", n3);
	tree->root = avltree_delete(tree, tree->root, (void*)(&intdata[3]));
	printf("Print tree:\n\n");
	avltree_print(tree, "  ");
	printf("\n");
	/*
	 *           5
	 *		  2     6
	 * 	    1   3
	 *
	 * */

	// delete '5' node
	printf("Delete node '%d'\n", *((int*)(&intdata[4])));
	tree->root = avltree_delete(tree, tree->root, (void*)(&intdata[4]));
	printf("Print tree:\n\n");
	avltree_print(tree, "  ");
	printf("\n");
	/*
	 *           3
	 *		  2     6
	 * 	    1
	 *
	 * */

	// Bug in Morris alg (wrong results in unbalanced trees)
    //	printf("Morris alg, height= %d\n\n", binarytree_findHeightMorrisTrav(tree->root));// findHeightMorrisTrav(tree->root));

	printf("Tree size (iterative alg): %d\n", avltree_getSizeIt(tree));

	avltree_destroy(tree);
	printf("AVL tree destroyed successfully.\n\n");
}

/*
 * Binary search tree demo.
 * */
void bst_demo() {

	/*
	 * Function to compare key with given data.
	 * Returns 1 if data > key, -1 if data < key, 0 if is equal.
	 * */
	int compare(void* data, const void* key) {

		if ((data == NULL) && (key == NULL))
			return 0;
		else if (data == NULL)
			return -1;
		else if (key == NULL)
			return 1;
		else {
			//struct binarytreenode* datanode = (struct binarytreenode*)data;
			int idata = *((int*)(data));
			int ikey = *((int*)key);

			if (idata == ikey)
				return 0;
			else if (idata > ikey)
				return 1;
			else
				return -1;
		}
	}

	/*
	 * Prints node data
	 * */
	void printnode(struct binarytreenode* node) {
		if (node) {
			void* data = node->data;
			if (data) {
				printf("%d", *((int*)data));
			}
		}
	}

	/*
	 * (hard) copy data from source to dest
	 * */
	void copydata(void* dest, const void* from) {
		if (dest) {
			if (from) {
				*((int*)dest) = *((int*)from);
			}
		}
	}

	printf("___________\n");
	printf("BINARY SEARCH TREE\n");
	printf("\nBINARY SEARCH TREE demo -----------\n\n");

	int intdata[] = {1,2,3,4,5,6,7};
	int n = sizeof(intdata) / sizeof(intdata[0]);

	// put '3' as root
	struct binarytree* tree = bst_create(&intdata[2], compare, NULL,
			printnode, copydata);

	printf("Binary search tree created successfully with root = '%d'\n", *((int*)(tree->root->data)));
	printf("Tree size: %d\n\n", bst_getSizeIt(tree));
	printf("Build search tree with elements:\n");

	for (int i = 0; i < n-1; ++i) {
		if (i == 2) continue;
		printf("'%d' ", intdata[i]);
	}

	printf("\n\n");

	//bst_insert(tree, tree->root, &intdata[2]);		// 3
	bst_insert(tree, tree->root, &intdata[1]);	// 2
	bst_insert(tree, tree->root, &intdata[0]);	// 1
	bst_insert(tree, tree->root, &intdata[4]);	// 5
	bst_insert(tree, tree->root, &intdata[3]);	// 4
	bst_insert(tree, tree->root, &intdata[5]);	// 6

	printf("Print tree:\n\n");
	bst_print(tree, "  ");
	printf("\n");
	/*
	 *           3
	 *		  2     5
	 * 	    1     4   6
	 *
	 * */

	printf("Tree size (iterative alg): %d\n", bst_getSizeIt(tree));

	// search '1'
	int* intp = &intdata[0];
	printf("Search value '%d': ", *intp);
	struct binarytreenode* n0 = bst_search(tree, tree->root, intp);
	if (n0 != NULL)
		printf("Found value '%d'.\n", *((int*)(n0->data)));
	else
		printf("Not found :(?\n");

	// printf("Tree deep using rec alg (max number of edges from root to deepest leaf node): %d\n", bst_findNode(tree->root));
	printf("Height of tree (max number of edges from deepest leaf node to root node): ");
	printf("%d\n\n", bst_treeHeightLevelOrder(tree));// findHeightMorrisTrav(tree->root));

	// root has depth 0
	printf("Node '%d' depth: %d\n", *((int*)(tree->root->data)), bst_findNodeDepth(tree, tree->root, tree->root->data));
	// '4' node has depth 2
	printf("Node '%d' depth: %d\n", intdata[3], bst_findNodeDepth(tree, tree->root, (void*)(&intdata[3])));
	// root has height 2
	printf("Node '%d' height: %d\n", *((int*)(tree->root->data)), bst_findNodeHeight(tree, tree->root, tree->root->data));
	// '5' node has height 0
	printf("Node '%d' height: %d\n\n", intdata[4], bst_findNodeHeight(tree, tree->root, (void*)(&intdata[4])));

	// delete '4' node
	int n3 = intdata[3];
	printf("Delete node '%d'\n", n3);

	// important: delete returns root node because if root were deleted, a new root must be set
	tree->root = bst_delete(tree, tree->root, (void*)(&intdata[3]));

	printf("Print tree:\n\n");
	bst_print(tree, "  ");
	printf("\n");
	/*
	 *           3
	 *		  2     5
	 * 	    1         6
	 *
	 * */

	// delete '5' node
	printf("Delete node '%d'\n", *((int*)(&intdata[4])));

	// important: delete returns root node because if root were deleted, a new root must be set
	tree->root = bst_delete(tree, tree->root, (void*)(&intdata[4]));
	printf("Print tree:\n\n");
	bst_print(tree, "  ");
	printf("\n");
	/*
	 *           3
	 *		  2     6
	 * 	    1
	 *
	 * */

	// Bug in Morris alg (wrong results in unbalanced trees)
    //	printf("Morris alg, height= %d\n\n", binarytree_findHeightMorrisTrav(tree->root));// findHeightMorrisTrav(tree->root));

	printf("Tree size (iterative alg): %d\n", bst_getSizeIt(tree));

	bst_destroy(tree);
	printf("Binary search tree destroyed successfully.\n\n");
}

/*
 * Binary tree demo.
 * */
void binarytree_demo() {

	/*
	 * Function to compare key with given data.
	 * Returns 1 if data > key, -1 if data < key, 0 if is equal.
	 * */
	int compare(void* data, const void* key) {

		if ((data == NULL) && (key == NULL))
			return 0;
		else if (data == NULL)
			return -1;
		else if (key == NULL)
			return 1;
		else {
			//struct binarytreenode* datanode = (struct binarytreenode*)data;
			int idata = *((int*)(data));
			int ikey = *((int*)key);

			if (idata == ikey)
				return 0;
			else if (idata > ikey)
				return 1;
			else
				return -1;
		}
	}

	/*
	 * Prints node data
	 * */
	void printnode(struct binarytreenode* node) {
		if (node) {
			void* data = node->data;
			if (data) {
				printf("%d", *((int*)data));
			}
		}
	}

	/*
	 * (hard) copy data from source to dest
	 * */
	void copydata(void* dest, const void* from) {
		if (dest) {
			if (from) {
				*((int*)dest) = *((int*)from);
			}
		}
	}

	printf("___________\n");
	printf("BINARY TREE\n");
	printf("\nBINARY TREE demo -----------\n\n");

	int intdata[] = {1,2,3,4,5,6,7};
	int n = sizeof(intdata) / sizeof(intdata[0]);

	struct binarytree* tree = binarytree_create(&intdata[0], compare, NULL,
			printnode, copydata);

	printf("Binary tree created successfully with root = '%d'\n", *((int*)(tree->root->data)));

	printf("Tree size: %d\n\n", binarytree_getSize(tree->root));

	printf("Build tree with elements:\n");

	for (int i = 0; i < n-2; ++i) {
		printf("'%d' ", intdata[i]);
	}

	printf("\n\n");

	// build tree
	struct binarytreenode* root = tree->root;
	struct binarytreenode* node1 = binarytree_createnode(&intdata[1]);
	struct binarytreenode* node2 = binarytree_createnode(&intdata[2]);
	struct binarytreenode* node3 = binarytree_createnode(&intdata[3]);
	struct binarytreenode* node4 = binarytree_createnode(&intdata[4]);
//	struct binarytreenode* node5 = binarytree_createnode(&intdata[5]);
//	struct binarytreenode* node6 = binarytree_createnode(&intdata[6]);

	struct binarytreenode* delnode3 = binarytree_createnode(&intdata[3]);
	struct binarytreenode* delnode4 = binarytree_createnode(&intdata[4]);

	root->left = node1;
	root->right = node2;

	node1->left = node3;
	node1->right = node4;

//	node2->left = node5;
//	node2->right = node6;

	printf("Print tree:\n\n");
	binarytree_print(tree, "  ");
	printf("\n");
	/*
	 *           1
	 *		  2     3
	 * 	    4   5 6   7
	 *
	 * */

	printf("Tree size (iterative alg): %d\n", binarytree_getSizeIt(tree));

	int* intp = &intdata[4];
	printf("Search value '%d': ", *intp);
	struct binarytreenode* n5 = binarytree_search(tree, tree->root, intp);
	if (n5 != NULL)
		printf("Found value '%d'.\n", *((int*)(n5->data)));
	else
		printf("Not found :(?\n");

	printf("Tree deep using rec alg (max number of edges from root to deepest leaf node): %d\n", binarytree_treeDepth(tree->root));
	printf("Height of tree (max number of edges from deepest leaf node to root node): ");
	printf("%d\n\n", binarytree_treeHeightLevelOrder(tree));// findHeightMorrisTrav(tree->root));

	printf("Node '%d' depth: %d\n", 1, binarytree_findNodeDepth(tree, tree->root, tree->root->data));
	printf("Node '%d' depth: %d\n", 5, binarytree_findNodeDepth(tree, tree->root, node4->data));
	printf("Node '%d' height: %d\n", 1, binarytree_findNodeHeight(tree, tree->root, tree->root->data));
	printf("Node '%d' height: %d\n\n", 5, binarytree_findNodeHeight(tree, tree->root, node4->data));


	int n3 = *((int*)(delnode3->data));
	printf("Delete node '%d'\n", n3);

	// important: delete returns root node because if root were deleted, a new root must be set
	tree->root = binarytree_delete(tree, delnode3->data);
	printf("Print tree:\n\n");
	binarytree_print(tree, "  ");
	printf("\n");
	/*
	 *           1
	 *		  2     6
	 * 	    4   5     7
	 *
	 * */

	printf("Delete node '%d'\n", *((int*)(delnode4->data)));

	// important: delete returns root node because if root were deleted, a new root must be set
	tree->root = binarytree_delete(tree, delnode4->data);
	printf("Print tree:\n\n");
	binarytree_print(tree, "  ");
	printf("\n");
	/*
	 *           1
	 *		  2     6
	 * 	        5     7
	 *
	 * */

	// Bug in Morris alg (wrong results in unbalanced trees)
    //	printf("Morris alg, height= %d\n\n", binarytree_findHeightMorrisTrav(tree->root));// findHeightMorrisTrav(tree->root));

	printf("Tree size (iterative alg): %d\n", binarytree_getSizeIt(tree));

	binarytree_destroy(tree);
	printf("Binary tree destroyed successfully.\n\n");

	// clean up
	free(delnode3);
	free(delnode4);
}

/*
 * Linked list queue demo.
 * */
void linkedlistqueue_demo() {
	printf("___________\n");
	printf("LINKED LIST QUEUE\n");
	printf("\nLINKED LIST QUEUE demo -----------\n\n");

	int intdata[] = {1,2,3,4,5,6,7};
	int n = sizeof(intdata) / sizeof(intdata[0]);

	struct linkedlistqueue* queue = linkedlistqueue_create(7);

	printf("Size: %d\n\n", linkedlistqueue_getsize(queue));

	for (int i = 0; i < n; ++i) {
		linkedlistqueue_enqueue(queue, &intdata[i]);
	    printf("Enqueue value at rear '%d':\n", intdata[i]);
	}

	printf("Size: %d\n\n", linkedlistqueue_getsize(queue));

	//peek queue front
	printf("Queue front: %d\n", *((int*)linkedlistqueue_peekfront(queue)));

	//peek queue rear
	printf("Queue rear: %d\n", *((int*)linkedlistqueue_peekrear(queue)));
	printf("\n");

	//Dequeue
	printf("Dequeue: %d\n", *((int*)linkedlistqueue_dequeue(queue)));

	//Dequeue
	printf("Dequeue: %d\n", *((int*)linkedlistqueue_dequeue(queue)));
	printf("\n");

	//peek queue front
	printf("Queue front: %d\n", *((int*)linkedlistqueue_peekfront(queue)));


	int x = 50;
	int* new_data = &x;

	//Enqueue 50
	if (linkedlistqueue_enqueue(queue, new_data))
		printf("Enqueue value '%d'\n", *((int*)linkedlistqueue_peekrear(queue)));
	else
		printf("Fail enqueue!\n");

	printf("\n");

	printf("Size: %d\n\n", linkedlistqueue_getsize(queue));

	//peek queue front
	printf("Queue front: %d\n", *((int*)linkedlistqueue_peekfront(queue)));

	//peek queue rear
	printf("Queue rear: %d\n", *((int*)linkedlistqueue_peekrear(queue)));
	printf("\n");

	linkedlistqueue_destroy(queue);
	printf("Linked list queue destroyed successfully.\n");
}

/*
 * Linked list stack demo.
 * */
void linkedliststack_demo() {
	printf("___________\n");
	printf("LINKED LIST STACK\n");
	printf("\nLINKED LIST STACK demo -----------\n\n");

	int intdata[] = {1,2,3,4,5,6,7};
	int n = sizeof(intdata) / sizeof(intdata[0]);

	struct linkedliststack* stack = linkedliststack_create( NULL );

	printf("Size: %d\n\n", linkedliststack_size(stack));

	for (int i = 0; i < n; ++i) {
		linkedliststack_push(stack, &intdata[i]);
	    printf("Inserted value at top '%d':\n", intdata[i]);
	}

	printf("Size: %d\n\n", linkedliststack_size(stack));

	// print array
	printf("Stack top: %d\n", *((int*)linkedliststack_peek(stack)));
	printf("\n");

	// Pop top element
	printf("Pop stack:\n");
	void* el = linkedliststack_pop(stack);
	if (el != NULL) {
		printf("Pop element '%d' successfully!\n", *((int*)el));
		printf("Size: %d\n\n", linkedliststack_size(stack));
	}
	else {
		printf("Fail to pop from stack!\n\n");
	}

	// Pop all elements
	while (el != NULL) {
		el = linkedliststack_pop(stack);
	}

	printf("All elements popped from stack.\n");
	printf("Size: %d\n", linkedliststack_size(stack));

	linkedliststack_destroy(stack);
	printf("\nLinked list stack destroyed successfully.\n");
}

/*
 * Arraylist demo.
 * */
void arraylist_demo() {

	/*
	 * Prints array of ints
	 * */
	void print_arraylist(struct arraylist* a) {
		for (int i = 0; i < a->length; ++i) {
			printf("%d ", *((int*)arraylist_get_item_at(a, i)));
		}
	}

	printf("___________\n");
	printf("ARRAYLIST\n");
	printf("\nARRAYLIST demo -----------\n\n");


	int intdata[] = {1,2,3,4,5,6,7};
	int n = sizeof(intdata) / sizeof(intdata[0]);

	struct arraylist* alist = arraylist_create_capacity(6);

	printf("Capacity: %d\n", alist->capacity);
	printf("Length: %d\n\n", alist->length);

	for (int i = 0; i < n; ++i) {
	    arraylist_add(alist, &intdata[i]);
	    printf("Inserted value at end '%d':\n", intdata[i]);
	}

	printf("\nCapacity: %d\n", alist->capacity);
	printf("Length: %d\n\n", alist->length);

	// print array
	printf("Print arraylist:\n");
	print_arraylist(alist);
	printf("\n\n");

	printf("Remove first item:\n");
	void* el = arraylist_remove_at(alist, 0);
	if (el != NULL) printf("Item '%d' removed successfully!\n", *((int*)el));

	printf("\nRemove last item:\n");
	el = arraylist_remove_at(alist, alist->length-1);
	if (el != NULL) printf("Item '%d' removed successfully!\n", *((int*)el));

	printf("\nCapacity: %d\n", alist->capacity);
	printf("Length: %d\n\n", alist->length);

	printf("Shrink to fit.\n");
	if (!arraylist_shrink_to_fit(alist))
		printf("Failed to shrink array list!\n");
	else
	{
		printf("Capacity: %d\n", alist->capacity);
		printf("Length: %d\n", alist->length);
	}

	// print array
	printf("\nPrint arraylist:\n");
	print_arraylist(alist);
	printf("\n");

	arraylist_destroy(alist);
	printf("\nArraylist destroyed successfully.\n");
}

/*
 * Binary search demo.
 * */
void binarysearch_demo() {

	/*
	 * Prints array of ints
	 * */
	void print_array(void* arr[], int n) {
		for (int i = 0; i < n; ++i) {
			printf("%d ", *((int*)arr[i]));
		}
	}

	/*
	 * Compares to elements.
	 * Returns 1 if a > b, -1 if a < b, 0 if a = b.
	 * */
	int compare(void* a, void* b) {
		int v1 = *((int*)a);
		int v2 = *((int*)b);
		if (v1 > v2) return 1;
		else if (v1 < v2) return -1;
		else return 0;
	}

	printf("___________\n");
	printf("BINARY SEARCH\n");
	printf("\nBinary search demo -----------\n\n");

	int sortarr[8] = {0,10,20,30,40,50,60,70};
	int n = sizeof(sortarr) / sizeof(sortarr[0]);
	void* data[n];// = malloc(n * sizeof(void*));
	for (int i = 0; i < n; ++i) {
		data[i] = &sortarr[i];
	}

	printf("Print sorted data:\n");
	print_array(data, n);
	printf("\n");

	// search values list
	int svalues[] = {0, 10, 20, 34, 70};
	int nvals = sizeof(svalues) / sizeof(svalues[0]);

	for (int i = 0; i < nvals; ++i) {
		printf("\nSearch position of '%d':", svalues[i]);
		int pos = binarySearch(data, 0, n, &svalues[i], compare);

		if (pos < 0)
			printf(" Element not found!");
		else
			printf(" Position %d", pos);
	}

	printf("\n\n----------------\n");
}

/*
 * Circular double linked list demo.
 * */
void circdoublelinklist_demo() {

	/*
	 * Print list data.
	 * Note: Assumes data stores pointer to integer value.
	 * */
	void print_list(struct circdbllinkedlist* list, uint num_nodes) {
		struct circdbllinkedlistnode* node = circdbllinkedlist_getstart(list);
		if (node == NULL)
		{
			printf("Can not print empty list!\n");
			return;
		}

		// print forward
		for (int i = 0; i < num_nodes; ++i) {
			if (node->data == NULL)
				printf("-- ");
			else
				printf("%d ", *((int*)(node->data)));

			node = node->next;
		}

		node = node->prev;

		// print backward
		for (int i = num_nodes; i > 0; --i) {
			if (node->data == NULL)
				printf("-- ");
			else
				printf("%d ", *((int*)(node->data)));

			node = node->prev;
		}

		printf("\n");
	}

	/*
	 * Checks for equality
	 * */
	int isequal(const void* a, const void* b) {
		if (*(int*)a == *(int*)b)
			return 1;
		else
			return 0;
	}

	struct circdbllinkedlist* list = circdbllinkedlist_create(isequal, NULL, NULL);

	int data[] = {1,2,3,4};
	int n = sizeof(data) / sizeof(data[0]);

	printf("___________\n");
	printf("CIRCULAR DOUBLE LINKED LIST\n");

	printf("\nCircular double linked list demo -----------\n\n");

	for(int i = 0; i != n; ++i) {
		circdbllinkedlist_insert_at_begin(list, &data[i]);
		printf("Insert at start value '%d'.\n", data[i]);
	}

	int num_nodes = 8;

	printf("\nPrint list %d nodes (forward and reserve):\n", num_nodes);
	print_list(list, num_nodes);


/*
	printf("\nGet data at position %d: ", 0);
	int* vp0 = (int*)(dbllinkedlist_getdata_at(list, 0));
	printf("%d", *vp0);

	printf("\nGet data at position %d: ", 3);
	int v3 = *((int*)(dbllinkedlist_getdata_at(list, 3)));
	printf("%d\n", v3);

*/

	printf("\nRemove first node\n");
	struct circdbllinkedlistnode* rnode = circdbllinkedlist_remove_first(list);

	if (rnode != NULL) {
		printf("Node removed successfully\n");
		free(rnode);
	}

	printf("\nPrint list %d nodes (forward and reverse):\n", num_nodes);
	print_list(list, num_nodes);

	// free resources
	circdbllinkedlist_destroy(list);
	printf("\nCircular double linked list destroyed successfully.\n");
}

/*
 * Double linked list demo.
 * */
void doublelinklist_demo() {

	/*
	 * Print list data
	 * */
	void print_list(struct dbllinkedlist* list) {
		struct dbllinkedlistnode* node = dbllinkedlist_getfirst(list);

		// print forward
		while (node != NULL) {
			if (node->data == NULL)
				printf("-- ");
			else
				printf("%d ", *((int*)(node->data)));

			node = node->next;
		}

		node = dbllinkedlist_getlast(list);

		// print reverse
		while (node != NULL) {
			if (node->data == NULL)
				printf("-- ");
			else
				printf("%d ", *((int*)(node->data)));

			node = node->prev;
		}

		printf("\n");
	}

	/*
	 * Checks for equality
	 * */
	int isequal(const void* a, const void* b) {
		if (*(int*)a == *(int*)b)
			return 1;
		else
			return 0;
	}

	struct dbllinkedlist* list = dbllinkedlist_create(isequal, NULL, NULL);

	int data[] = {1,2,3,4};
	int n = sizeof(data) / sizeof(data[0]);

	printf("___________\n");
	printf("DOUBLE LINKED LIST\n");

	printf("\nDouble linked list demo -----------\n\n");

	for(int i = 0; i != n; ++i) {
		dbllinkedlist_insert_at_begin(list, &data[i]);
		printf("Insert at start value '%d'.\n", data[i]);
	}

	printf("\nPrint list (forward aand reserve):\n");
	print_list(list);

	printf("\nGet data at position %d: ", 0);
	int* vp0 = (int*)(dbllinkedlist_getdata_at(list, 0));
	printf("%d", *vp0);

	printf("\nGet data at position %d: ", 3);
	int v3 = *((int*)(dbllinkedlist_getdata_at(list, 3)));
	printf("%d\n", v3);

	printf("\nRemove first node\n");
	struct dbllinkedlistnode* rnode = dbllinkedlist_remove(list, (void*)vp0);

	if (rnode != NULL) {
		printf("Node removed successfully\n");
		free(rnode);
	}

	printf("\nPrint list (forward and reverse):\n");
	print_list(list);

	// free resources
	dbllinkedlist_destroy(list);
	printf("\nDouble linked list destroyed successfully.\n");
}

/*
 * Linked list demo.
 * */
void singlelinklist_demo() {

	/*
	 * Print list data
	 * */
	void print_list(struct linkedlist* list) {
		struct linkedlistnode* node = linkedlist_getfirst(list);

		while (node != NULL) {
			if (node->data == NULL)
				printf("-- ");
			else
				printf("%d ", *((int*)(node->data)));

			node = node->next;
		}

		printf("\n");
	}

	/*
	 * Checks for equality
	 * */
	int isequal(const void* a, const void* b) {
		if (*(int*)a == *(int*)b)
			return 1;
		else
			return 0;
	}

	struct linkedlist* list = linkedlist_create(isequal, NULL);

	int data[] = {1,2,3,4};
	int n = sizeof(data) / sizeof(data[0]);

	printf("___________\n");
	printf("LINKED LIST\n");

	printf("\nSingle linked list demo -----------\n\n");

	for(int i = 0; i != n; ++i) {
		linkedlist_push(list, &data[i]);
		printf("Insert at start value '%d'.\n", data[i]);
	}

	printf("\nPrint list:\n");
	print_list(list);

	printf("\nReverse linked list:\n");
	linkedlist_reverse(list);
	print_list(list);

	printf("\nReverse linked list again:\n");
	linkedlist_reverse(list);
	print_list(list);

	printf("\nGet data at position %d: ", 0);
	int* vp0 = (int*)(linkedlist_getdata_at(list, 0));
	printf("%d", *vp0);

	printf("\nGet data at position %d: ", 3);
	int v3 = *((int*)(linkedlist_getdata_at(list, 3)));
	printf("%d\n", v3);

	printf("\nRemove first node\n");
	struct linkedlistnode* rnode = linkedlist_remove(list, (void*)vp0);

	if (rnode != NULL) {
		printf("Node removed successfully\n");
		free(rnode);
	}

	printf("\nPrint list:\n");
	print_list(list);

	/*
	 printf("\nGet data at position %d: ", 0);
	int v0 = *((int*)(linkedlist_getdata_at(list, 0)));
	printf("%d\n", v0);
	*/

	// free resources
	linkedlist_destroy(list);
	printf("\nLinked list destroyed successfully.\n");
}

/*
 * Linked list demo.
 * */
void circsinglelinklist_demo() {

	/*
	 * Print list data
	 * */
	void print_list(struct circlinkedlist* list, int num_nodes) {
		struct circlinkedlistnode* node = circlinkedlist_getstart(list);

		for (int i = 0; i < num_nodes; ++i) {
			if (node->data == NULL)
				printf("-- ");
			else
				printf("%d ", *((int*)(node->data)));

			node = node->next;
		}

		printf("\n");
	}

	/*
	 * Checks for equality
	 * */
	int isequal(const void* a, const void* b) {
		if (*(int*)a == *(int*)b)
			return 1;
		else
			return 0;
	}

	struct circlinkedlist* list = circlinkedlist_create(isequal, NULL, NULL);

	int data[] = {1,2,3,4};
	int n = sizeof(data) / sizeof(data[0]);

	printf("____________________\n");
	printf("CIRCULAR LINKED LIST\n");

	printf("\nCircular single linked list demo -----------\n\n");

	for(int i = 0; i != n; ++i) {
		circlinkedlist_insert_at_end(list, &data[i]);
		printf("Insert at end value '%d'.\n", data[i]);
	}

	int num_nodes = 10;
	printf("\nPrint list (%d nodes):\n", num_nodes);
	print_list(list, 10);

	int startval = 1000;

	printf("\nInsert at start value '%d'.\n", startval);
	circlinkedlist_insert_at_begin(list, &startval);

	printf("\nPrint list (%d nodes):\n", num_nodes);
	print_list(list, num_nodes);

	printf("\nRemove first node\n");
	struct circlinkedlistnode* rnode = circlinkedlist_remove(list, (void*)(&startval));

	if (rnode != NULL) {
		printf("Node removed successfully\n");
		free(rnode);
	}

	printf("\nPrint list:\n");
	print_list(list, num_nodes);

	// free resources
	circlinkedlist_destroy(list);
	printf("\nCircular linked list destroyed successfully.\n");
}

int main() {
	printf("\n");
	arraylist_demo();
	printf("\n\n");
	singlelinklist_demo();
	printf("\n\n");
	circsinglelinklist_demo();
	printf("\n\n");
	doublelinklist_demo();
	printf("\n\n");
	circdoublelinklist_demo();
	printf("\n\n");
	hashtable_lp_demo();
	printf("\n\n");
	hashtable_linked_list_demo();
	printf("\n\n");
	binarysearch_demo();
	printf("\n\n");
	linkedliststack_demo();
	printf("\n\n");
	linkedlistqueue_demo();
	printf("\n\n");
	binarytree_demo();
	printf("\n\n");
	bst_demo();
	printf("\n\n");
	avltree_demo();
	printf("\n\n");
	binaryheaparray_demo();
	printf("\n\n");
	fibonacciheap_demo();
	printf("\n\n");
	arraydeque_demo();
	printf("\n\n");
	dbllinkedlistdeque_demo();
	printf("\n\n");
	hashset_demo();
	printf("\n\n");
	rbtree_demo();
	printf("\n\n");
	treeset_demo();
	printf("\n\n");
	adjlgraph_demo();
	printf("\n\n");
	trie_demo();
	printf("\n\n");
	trie_extensions_demo();
	printf("\n\n");
	dfsalg_demo();
	printf("\n");
	return EXIT_SUCCESS;
}

