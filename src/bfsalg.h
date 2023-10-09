/*
 * bfsalg.h
 *
 *  Created on: 01/10/2023
 *      Author: Tiago C. Teixeira
 * Description: C Headers for the breadth-first-search algorithm.
 *
 * The Breadth First Search (BFS) is a fundamental search algorithm used to explore
 * nodes and edges of a graph. It runs with a time complexity of O(V+E) and is often
 * used as a building block in other algorithms.
 *
 * ----------------------------------------
 * The BFS algorithm is particular useful for one thing: finding the shortest path
 * in unweighted graphs.
 *----------------------------------------
 *
 * A BFS starts at some arbitrary node of a graph and explores neighbour nodes first,
 * before moving to the next level neighbours.
 *
 * Algorithm:
 *
 * 	The BFS algorithm uses a queue data structure to track which node to visit next.
 * 	Upon reaching a new node the algorithm adds it to the queue to visit it later.
 * 	The queue data structure works just like a real world queue.
 *
 */

#ifndef BFSALG_H_
	#define BFSALG_H_
	#include "adjlgraph.h"

//	/*
//	 * Reconstructs the graph path computed by BFS algorithm to return the shortest path
//	 * from start to end nodes.
//	 * If 'start' and 'end' are not connected then returns 'NULL'.
//	 * Note: You must release result array from memory later.
//	 */
//	int* bfsalg_reconstruct_path(int start, int end, int prev[], int num_nodes);

	/*
	 * Perform a breadth first search on an unweighted graph at starting node 'start'.
	 *
	 * The BFS algorithm uses a queue data structure to track which node to visit next.
	 * Upon reaching a new node the algorithm adds it to the queue to visit it later.
	 *
	 * Returns the computed shortest path if succeded, NULL if no path was found.
	 * Note: return path must be released later from memory.
	 *
	 */
	int* bfsalg_shortest_path( struct adjlgraph* g, int start, int end, int* res_size );

	/*
	 * Prints the path. ex:'[4->7->3->2]'
	 */
	void bfsalg_print_path( int* path, int n);

#endif /* BFSALG_H_ */
