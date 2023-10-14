/*
 * dijkstrasp.c
 *
 *  Created on: 29/09/2023
 *      Author: Tiago C. Teixeira
 * Description: C implementation of Dijkstra shortest path algorithm.
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <float.h>
#include <string.h>
#include "adjlgraph.h"
#include "indminbinaryheap.h"

#define DIJKSTRA_EPS 1e-6	// handle very small differences with double values
#define DIJKSTRA_EMPTY -1	// empty slot
// Utility functions --------------

/*
 * Reverses an array of integers (original array will be changed).
 */
void dijkstrasp_reverse_array(int arr[], int end) {
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
void dijkstrasp_fillintarray(int* arr, int n, int value) {
	for (int i = 0; i < n; ++i) {
		arr[i] = value;
	}
}

/*
 * Fills an array of doubles with a given value.
 */
void dijkstrasp_filldblarray(double* arr, int n, double value) {
	for (int i = 0; i < n; ++i) {
		arr[i] = value;
	}
}

/*
 * Gets the absolute value of a double.
 */
double dijkstrasp_abs(double value) {
	if (value < 0) return -1.0 * value;
	else return value;
}

// Utility functions --------------

/*
 * Declare vertice/distance pair struct to be stored in priority queue.
 */
struct dijkstra_vert_dist_pair {
	int vid;
	double dist;
};

/*
 * Checks if double value is too small.
 */
int dijkstra_too_small(double value) {
	return (dijkstrasp_abs( value ) < DIJKSTRA_EPS);
}

/*
 * Compare function for distance comparison.
 */
int dijkstrasp_compare(const double a, const double b) {
	if ( dijkstra_too_small( a - b ) ) return 0;
	else if (a > b) return 1;
	else if (a < b) return -1;
	else return 0;
}

/*
 * Compare function for priority queue.
 */
int dijkstrasp_compare_pq( const void* a, const void* b ) {

	double da = *((double*)a);
	double db = *((double*)b);

	if ( dijkstra_too_small( da - db ) ) return 0;
	else if (da > db) return 1;
	else if (da < db) return -1;
	else return 0;
}

/*
 * Free data function for priority queue.
 */
void dijkstrasp_freedata_pq( void* data ) {
	free(data);
}

/**
* Reconstructs the shortest path (of nodes) from 'start' to 'end' inclusive.
*
* Return An array of node indexes of the shortest path from 'start' to 'end'. If 'start' and
*     'end' are not connected then NULL is returned.
*/
int* dijkstrasp_adjlist_reconstructPath(int start, int end, int* prev, int n,
										int* spath_size_p)
{
	*spath_size_p = 0;
	int* result = malloc(n * sizeof(int));
	if (!result) {
		printf( "Memory error: failed to allocate memory for result array of "
				"shortest path Dijkstra algorithm!" );
		abort();
	}
	else {
		int i = 0;

		for (int at = end; at != DIJKSTRA_EMPTY; at = prev[at])
			result[i++] = at;

		dijkstrasp_reverse_array(result, i - 1);
		if (result[0] == start) {
			*spath_size_p = i;
			if (i < n) {
				// copy result path to new buffer excludind trash bytes at tail
				int* fin_result = (int*)malloc(i * sizeof(int));
				memcpy( fin_result, result, i * sizeof(int));
				free(result);
				return fin_result;
			} else {
				return result;
			}
		}
		else
			free(result);
	}

	return NULL;
}

/*
 * Computes the shortest path and distance from a start vertice to destination vertice
 * using the Dijkstra shortest path algorithm.
 *
 * Returns shortest path from start vertice to end vertice or 'NULL' if end vertice
 * is unreachable. Also distance to vertices is filled and returned in 'dist' array.
 * 'spath_size_p' returns the size of shortest path array.
 * Note: 'dist' argument must have size equal to number of vertices in graph.
 */
int* dijkstrasp_adjlist_shortest_path(struct adjlgraph* g, int start, int end,
		double* dist, int* spath_size_p)
{
//	int result = -1;
	double init_val = 0.0;
	double* dblp = malloc(sizeof(double));
	*dblp = init_val;
	int ki = start;	// key index for priority queue
	int n = g->numvertices;
	int* prev = (int*)malloc(n * sizeof(int));

	// initialize prev with empty slot value
	dijkstrasp_fillintarray(prev, n, DIJKSTRA_EMPTY);

//	double* dist = (double*)(malloc( n * sizeof(double) ));
	_Bool* visited = (calloc( n, sizeof(_Bool) ));	// initializes to zeros (false)

	// initialize dist to max possible value (+oo)
	dijkstrasp_filldblarray(dist, n, DBL_MAX);
	dist[start] = 0.0;	// dist to start vertice is zero

	// create empty indexed priority queue
	struct iminbinarypq* ipq = iminbinpq_create (2 * n,
									dijkstrasp_compare_pq, NULL, dijkstrasp_freedata_pq );

	// create ipq node
	//struct dijkstra_vert_dist_pair* node = dijkstra_createnode(start, dist[start]);
	iminbinpq_insert(ipq, ki, dblp);	// inserts (start, 0) pair in priority queue
	int from_vert = -1;
	int to_vert = -1;

	while (!iminbinpq_isempty( ipq ))
	{
		//node = iminbinpq_extractkey( ipq );
		from_vert = iminbinpq_peekkeyindex(ipq);
		visited[from_vert] = true;
		double* min_value_p = (double*)iminbinpq_extractkey( ipq );

		// We already found a better path before we got to
		// processing this node so we can ignore it.
		if (dijkstrasp_compare(dist[from_vert], *min_value_p) < 0) {
			free(min_value_p);
			continue;
		} else
			free(min_value_p);// release double pointer (not needed anymore)

		struct adjlgedge* edge = g->vertexlist[from_vert]->edgeslist;
		while (edge) {
			to_vert = edge->vertexindex;
			// You cannot get a shorter path by revisiting
			// a node you have already visited before.
			if (!(visited[to_vert])) {
				// Relax edge by updating minimum cost if applicable.
				double* new_dist_p = (double*)malloc(sizeof(double));
				*new_dist_p = dist[from_vert] + edge->weight;

				if (dijkstrasp_compare(*new_dist_p, dist[to_vert]) < 0) {
					// found short distance
					prev[to_vert] = from_vert;		// save vertice on path
					dist[to_vert] = *new_dist_p;	// update dist with minimum distance
					ki = to_vert;
//					node = dijkstra_createnode(to_vert, dist[to_vert]);
					if (!iminbinpq_contains( ipq, ki))
						iminbinpq_insert( ipq, ki, new_dist_p);	// insert in priority queue
					else
						iminbinpq_decrease(ipq, ki, new_dist_p);
				} else
					free(new_dist_p);
			}

			edge = edge->next;
		}

		// Once we've visited all the nodes spanning from the end
		// node we know we can return the minimum distance value to
		// the end node because it cannot get any better after this point.
		if (from_vert == end) {
//			result = dist[end];
			break;
		}
	}

	// free resources
	free(visited);
	iminbinpq_destroy(ipq);

	// reconstruct output path
	int* shortest_path = dijkstrasp_adjlist_reconstructPath(start, end, prev, n, spath_size_p);

	free(prev);
	return shortest_path;
}

/*
 * Prints the path. ex:'[4->7->3->2]'
 */
void dijkstrasp_print_path( int* path, int n) {
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





