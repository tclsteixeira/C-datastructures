/*
 * dfsalg.h
 *
 *  Created on: 25/10/2023
 *      Author: Tiago C. Teixeira
  * Description: C implementation of Depth-first search algorithm.
 *
 *
 * Algorithm:
 *
 * Depth-first search is an algorithm for traversing or searching tree or graph data structures.
 * The algorithm starts at the root node (selecting some arbitrary node as the root node in the
 * case of a graph) and explores as far as possible along each branch before backtracking.
 *
 *
 * Advantages of Depth First Search:
 *
 *	Iteractive approach
 *
 *    Memory requirement is only linear with respect to the search graph. This is in contrast with
 *    breadth-first search which requires more space. The reason is that the algorithm only needs to
 *    store a stack of nodes on the path from the root to the current node.
 *    The time complexity of a depth-first Search to depth d and branching factor b (the number of
 *    children at each node, the outdegree) is O(bd) since it generates the same set of nodes as
 *    breadth-first search, but simply in a different order. Thus practically depth-first search is
 *    time-limited rather than space-limited.
 *    If depth-first search finds solution without exploring much in a path then the time and space
 *    it takes will be very less.
 *    DFS requires less memory since only the nodes on the current path are stored. By chance DFS may
 *    find a solution without examining much of the search space at all.
 *
 *
 * Disadvantages of Depth First Search:
 *
 *    The disadvantage of Depth-First Search is that there is a possibility that it may down the
 *    left-most path forever. Even a finite graph can generate an infinite tre One solution to this
 *    problem is to impose a cutoff depth on the search. Although ideal cutoff is the solution
 *    depth d and this value is rarely known in advance of actually solving the problem. If the chosen
 *    cutoff depth is less than d, the algorithm will fail to find a solution, whereas if the cutoff
 *    depth is greater than d, a large price is paid in execution time, and the first solution found
 *    may not be an optimal one.
 *    Depth-First Search is not guaranteed to find the solution.
 *    And there is no guarantee to find a minimal solution, if more than one solution.
 *
 *
 * Applications of Depth First Search:
 *
 * 		1. Detecting cycle in a graph: A graph has a cycle if and only if we see a back edge during DFS.
 * 		   So we can run DFS for the graph and check for back edges.
 *
 * 		2. Path Finding: We can specialize the DFS algorithm to find a path between two given vertices u
 * 		   and z.
 *
 *    	   Call DFS(G, u) with u as the start vertex.
 *         Use a stack S to keep track of the path between the start vertex and the current vertex.
 *         As soon as destination vertex z is encountered, return the path as the contents of the stack.
 *
 * 		3. Topological Sorting: Topological Sorting is mainly used for scheduling jobs from the given
 * 		   dependencies among jobs. In computer science, applications of this type arise in instruction
 * 		   scheduling, ordering of formula cell evaluation when recomputing formula values in spreadsheets,
 * 		   logic synthesis, determining the order of compilation tasks to perform in makefiles, data
 * 		   serialization, and resolving symbol dependencies in linkers.
 *
 * 		4. To test if a graph is bipartite: We can augment either BFS or DFS when we first discover a new
 * 		   vertex, color it opposite its parents, and for each other edge, check it doesn’t link two
 * 		   vertices of the same color. The first vertex in any connected component can be red or black.
 *
 * 		5. Finding Strongly Connected Components of a graph: A directed graph is called strongly connected
 * 		   if there is a path from each vertex in the graph to every other vertex. (See this for DFS-based
 * 		   algo for finding Strongly Connected Components)
 *
 * 		6. Solving puzzles with only one solution: such as mazes. (DFS can be adapted to find all
 * 		   solutions to a maze by only including nodes on the current path in the visited set.).
 *
 * 		7. Web crawlers: Depth-first search can be used in the implementation of web crawlers to explore
 * 		   the links on a website.
 *
 * 		8. Maze generation: Depth-first search can be used to generate random mazes.
 *
 * 		9. Model checking: Depth-first search can be used in model checking, which is the process of
 * 		   checking that a model of a system meets a certain set of properties.
 *
 * 		10. Backtracking: Depth-first search can be used in backtracking algorithms.
 *
 */

#ifndef DFSALG_H_
	#define DFSALG_H_
	#include "adjlgraph.h"

	/*
	 * Declares the ancestor node struct for find ancestors function
	 */
	struct dfsalgancestornode {
		int vertice;
		struct dfsalgancestornode* next;
	};

	/*
	 * Uses Depth-first search algorithm to compute number of connectd vertices in adjacency list graph
	 * starting at a given vertice.
	 */
	void dfsalg_countvertices(struct adjlgraph* g, int start, ulong* result);

	/*
	 * Uses Depth-first search iteractive algorithm to compute number of connectd vertices in an adjacency list
	 * graph starting at a given vertice.
	 * Returns number of connectd vertices result as a pointer to unsigned long.
	 */
	void dfsalg_countvertices_iteractive(struct adjlgraph* g, int start, ulong* result);

	/*
	 * Find ancestors of each node in the given adjacency list graph.
	 * Returns an array of linked lists. Each array index is the vertice number and each value is a
	 * linked list of ancestors for the given vertice.
	 *
	 * Time Complexity: O(V2)
	 * Auxiliary Space: O(|V| + |E|)
	 */
	struct dfsalgancestornode** dfsalg_find_ancestors(struct adjlgraph* g);

	/*
	 * Releases ancestors array from memory.
	 * Note: ancestors is an array of linked lists.
	 */
	void dfsalg_destroy_ancestors(struct dfsalgancestornode** a, int n);

	/*
	 * Prints ancestors list.
	 */
	void dfsalg_print_ancestors(struct dfsalgancestornode** ancestors, uint n);

#endif /* DFSALG_H_ */

