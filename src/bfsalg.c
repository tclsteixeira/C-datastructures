/*
 * bfsalg.c
 *
 *  Created on: 03/10/2023
 *      Author: Tiago C. Teixeira
 * Description: C implementation of the breadth-first-search algorithm.
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
 * Sources: Based on William Fiset Java implementation in
 * 			https://www.youtube.com/watch?v=oDqjPvD54Ss
 * 			https://github.com/williamfiset/Algorithms/blob/master/src/main/java/com/williamfiset/algorithms/graphtheory/BreadthFirstSearchAdjacencyListIterative.java
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "bfsalg.h"
#define BFSALG_EMPTY -1

/*
 * Reverses an array of integers (original array will be changed).
 */
void bfsalg_reverse_array(int arr[], int end) {
	int temp = 0;
	for (int i = 0; i < end; ++i, --end) {
		temp = arr[i];
		arr[i] = arr[end];
		arr[end] = temp;
	}
}

/*
 * Fills an array of integers with a given value.
 */
void bfsalg_fillintarray(int arr[], int n, int value) {
	for (int i = 0; i < n; ++i) {
		arr[i] = value;
	}
}

/*
 * Fills an array of booleans with a given value.
 */
void bfsalg_fillboolarray(bool arr[], int n, bool value) {
	for (int i = 0; i < n; ++i) {
		arr[i] = value;
	}
}

// TODO WILL NOT WORK. WE NEVER KNOW THE CORRECT SIZE OF QUEUE IN ADVANCE
//--------------------- intqueue ------------------

// A custom implementation of a circular integer only queue which is
// extremely quick and lightweight.
// However, the downside is you need to know an upper bound on the number of elements
// that will be inside the queue at any given time for this queue to work.
struct bfsalg_intqueue {
	int* ar;
	size_t front, end, sz;
};

/*
 * Creates a new queue instance.
 */
struct bfsalg_intqueue* bfsalg_intqueue_create(size_t max_size) {
	struct bfsalg_intqueue* result = malloc(sizeof(*result));
	if (!result) {
		printf("Memory error: failed to allocate memory for BFS queue!");
		abort();
	}
	else {
		result->sz = max_size + 1;
		result->ar = calloc( result->sz, sizeof(int) );
		if (!(result->ar)) {
			printf("Memory error: failed to allocate memory for BFS queue array!");
			free(result);
			abort();
		}

		result->front = result->end = 0;
		return result;
	}
}

/*
 * Checks if queue is empty.
 */
bool bfsalg_intqueue_isempty(struct bfsalg_intqueue* q) {
	return (q->front == q->end);
}

int bfsalg_intqueue_peek(struct bfsalg_intqueue* q) {
	return q->ar[q->front];	// no checks for more speed
}

/*
 * Add an element to the queue.
 */
void bfsalg_intqueue_enqueue( struct bfsalg_intqueue* q, int el ) {
	q->ar[q->end++] = el;	// add at end and incremenet end pos
	if (q->end == q->sz) q->end = 0;
	if (q->end == q->front) {
		printf("Error: exceeded maximum queue size!");
		abort();
	}
}

/*
 * Pops and returns the element at front of the queue.
 * Note: Make sure you check if the queue is not empty before calling dequeue!
 */
int bfsalg_intqueue_dequeue( struct bfsalg_intqueue* q ) {
	// no check here if queue is empty for speed reasons
    int result = q->ar[q->front++];
    if (q->front == q->sz) q->front = 0;
    return result;
}
//--------------------- intqueue ------------------



/*
 * Reconstructs the graph path computed by BFS algorithm to return the shortest path
 * from start to end nodes.
 * If 'start' and 'end' are not connected then returns 'NULL'.
 * Note: You must release result array from memory later.
 */
int* bfsalg_reconstruct_path(int start, int end, int prev[], int num_nodes, int* res_size)
{
	int* result = (int*)malloc( num_nodes * sizeof(int) );
	if (!result) {
		printf( "Memory error: failed to allocate memory for result array of "
			    "shortest path BFS algorithm!" );
		abort();
	}
	else {
		int i = 0;
		for (int at = end; at != BFSALG_EMPTY; at = prev[at])
			result[i++] = at;

		// need to reverse result
		bfsalg_reverse_array( result, i - 1 );

		if (result[0] == start) {
			*res_size = i;
			if (i < num_nodes) {
				// copy result path to new buffer excludind trash bytes at tail
				int* fin_result = (int*)malloc(i * sizeof(int));
				memcpy( fin_result, result, i * sizeof(int));
				free(result);
				return fin_result;
			} else {
				return result;
			}
		}

		free(result);
		*res_size = 0;
		return NULL;
	}
}

/*
 * Perform a breadth first search on an unweighted graph at starting node 'start'.
 *
 * The BFS algorithm uses a queue data structure to track which node to visit next.
 * Upon reaching a new node the algorithm adds it to the queue to visit it later.
 *
 * Returns the computed shortest path if succeded, NULL if no path was found.
 * Also returns result path size in 'res_size'.
 * Note: return path must be released later from memory.
 *
 */
int* bfsalg_shortest_path( struct adjlgraph* g, int start, int end, int* res_size )
{
	*res_size = -1;
	size_t nv = g->numvertices;				// total number of vertices (nodes)
	size_t ne = adjlgraph_getnumedges( g );	// total number of edges

	int* prev = malloc(nv * sizeof(int));	// to store the traversal path nodes

	if (!prev) {
		printf("Memory error: failed to allocate BFS shortest path array!");
		abort();
	}
	else {
		bool* visited = (bool*)malloc(nv * sizeof(bool));

		if (!visited) {
			printf("Memory error: failed to allocate BFS shortest path visited array!");
			abort();
		}

		// initialize arrays with default values
		bfsalg_fillintarray(prev, nv, BFSALG_EMPTY);
		bfsalg_fillboolarray(visited, nv, false);

		// create queue with enough size
		struct bfsalg_intqueue* q = bfsalg_intqueue_create( (nv > ne) ? nv : ne );

		// Start by visiting the 'start' node and add it to the queue.
		bfsalg_intqueue_enqueue(q, start);
		visited[start] = true;
		int to = -1; int count = 0;

		// Continue until the BFS is done.
		while (!bfsalg_intqueue_isempty(q)) {
			int node = bfsalg_intqueue_dequeue(q);
			struct adjlgedge* edge = g->vertexlist[node]->edgeslist;

			// Loop through all edges attached to this node. Mark nodes as visited once
			// they're in the queue. This will prevent having duplicate nodes in the queue
			// and speedup the BFS.
			while (edge) {
				to = edge->vertexindex;
				if (!visited[to]) {
					visited[to] = true;
					prev[to] = node; count++;
					bfsalg_intqueue_enqueue(q, to);
				}

				edge = edge->next;
			}
		}

		// reconstruct path
		int* result = bfsalg_reconstruct_path(start, end, prev, count, res_size);

		// free memory
		free(prev);
		free(visited);
		free(q->ar);
		free(q);
		return result;
	}

	return NULL;
}

/*
 * Prints the path. ex:'[4->7->3->2]'
 */
void bfsalg_print_path( int* path, int n) {
	printf("[");
	if (n > 0)
	{
		for (int i = 0; i < n-1; ++i) {
			printf("%d->", path[i]);
		}

		printf("%d", path[n-1]);
	}
	printf("]\n");
}
