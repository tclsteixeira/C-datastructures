/*
 * dijkstrasp.h
 *
 *  Created on: 29/09/2023
 *      Author: Tiago C. Teixeira
 * Description: C Headers for Dijkstra shortest path algorithm.
 *
 * Dijkstra algorithm is a single source shortest path (SSSP) algorithm for grapths
 * with non-negative edge weights.
 *
 * Depending on how the algorithm is implemented and what data structures are used,
 * the time complexity is typically O(E*log(V)) which is competitive against other
 * shortest path algorithms.
 *
 *
 * Complexity Analysis:
 *
 * 		Time Complexity: O(ELogV), where V is the number of vertices and E is the
 * 						 number of edges.
 *  	Auxiliary Space: O(V2)
 *
 *
 * Overall, Dijkstra’s algorithm is a simple and efficient way to find the shortest
 * path in a graph with non-negative edge weights. However, it may not work well with
 * graphs that have negative edge weights or cycles. In such cases, more advanced
 * algorithms such as the Bellman-Ford algorithm or the Floyd-Warshall algorithm may
 * be used.
 *
 * Sources: Adapted from William Fiset Java implementation
 * 			https://github.com/williamfiset/Algorithms/blob/master/src/main/java/com/williamfiset/algorithms/graphtheory/DijkstrasShortestPathAdjacencyListWithDHeap.java
 *
 * https://www.youtube.com/watch?v=pSqmAO-m7Lk
 *
 */

#ifndef DIJKSTRASP_H_
	#define DIJKSTRASP_H_

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
			double* dist, int* spath_size_p);

	/*
	 * Prints the path. ex:'[4->7->3->2]'
	 */
	void dijkstrasp_print_path( int* path, int n );

#endif /* DIJKSTRASP_H_ */
