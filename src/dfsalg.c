/*
 * dfsalg.c
 *
 *  Created on: 24/10/2023
 *      Author: Tiago C. Teixeira
 * Description: C implementation of Depth-first search algorithm.
 *
 *
 * Algorithm:
 *
 * Depth-first search (DFS) algorithm is the most fundamental search algorithm used to explore nodes
 * and edges of a graph. It runs on a time complexity of O(V+E), i.e., directly proportional to the
 * size of your graph, and is often used as a building block in other algorithms.
 * When augmented to perform other tasks such as count connected components, determine connectivity,
 * or find bridges/articulations points then DNF can be really usefull.
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

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "adjlgraph.h"
#include "dfsalg.h"

/*
 * Recursively computes the number of adjacency list graph connected vertices starting at a given vertice,
 * using the Deph-first search algorithm.
 * Returns the number of counted vertices.
 */
void dfsalg_dfs_rec(struct adjlgraph* g, bool* visited, int vertice, ulong* result)
{
	// We have already visited this node
	if (visited[vertice])
		return;

	// mark as visited
	visited[vertice] = true;
	*result +=1;
	struct adjlgvertex* v = g->vertexlist[vertice];
	struct adjlgedge* e = v->edgeslist;

	// visit all neighbor vertices
	while (e != NULL) {
		dfsalg_dfs_rec(g, visited, e->vertexindex, result);
		e = e->next;
	}
}

/*
 * Uses Depth-first search algorithm to compute number of connectd vertices in adjacency list graph
 * starting at a given vertice.
 * Returns result as pointer to unsigned long.
 */
void dfsalg_countvertices(struct adjlgraph* g, int start, ulong* result)
{
	size_t numvert = g->numvertices;
	bool visited[numvert];
	for(int i = 0; i < numvert; ++i)
		visited[i] = false;

	*result = 0;
	dfsalg_dfs_rec(g, visited, start, result);
}


//-----------------------------------------------
/*
 * Integer stack for Deph-first search iteractive algorithm.
 */
struct dfsalgistack {
	uint pos;
	int stack[];
};

struct dfsalgistack* dfsalg_create_istack(uint max_size) {
	struct dfsalgistack* result = (struct dfsalgistack*)malloc(sizeof(struct dfsalgistack) + sizeof(int) * max_size);
	if (result == NULL) {
		printf("Memory error: failed to allocate memory for 'dfsalgistack' struct!\n");
		abort();
	}

	result->pos = 0;	// empty stack
	return result;
}

bool dfsalg_istack_isempty(struct dfsalgistack* s) {
	return s->pos == 0;
}

void dfsalg_istack_push(struct dfsalgistack* s, int value) {
	s->stack[s->pos++] = value;
}

int dfsalg_istack_peek(struct dfsalgistack* s) {
	return s->stack[s->pos - 1];
}

int dfsalg_istack_pop(struct dfsalgistack* s) {
	return s->stack[--(s->pos)];
}
//----------------------------------------------


/*
 * Uses Depth-first search iteractive algorithm to compute number of connectd vertices in an adjacency list
 * graph starting at a given vertice.
 * Returns number of connectd vertices result as a pointer to unsigned long.
 */
void dfsalg_countvertices_iteractive(struct adjlgraph* g, int start, ulong* result)
{
	*result = 0;
	int n = g->numvertices;
	struct dfsalgistack* s = dfsalg_create_istack(n);
	bool visited[n];
	for(int i = 0;i < n; i++) {
		visited[i] = false;
	}

	// get start vertice
	int from = start;
	struct adjlgvertex* fromv = g->vertexlist[from];
	// push start vertice index onto stack
	dfsalg_istack_push(s, from);
	struct adjlgedge* edge = NULL;

	while (!dfsalg_istack_isempty(s)) {
		from = dfsalg_istack_pop(s);

		if (!visited[from]) {
			visited[from] = true;
			*result += 1;
			fromv = g->vertexlist[from];
			edge = fromv->edgeslist;
			while (edge) {
				int to = edge->vertexindex;
				dfsalg_istack_push(s, to);
				edge = edge->next;
			}
		}
	}

	// release stack
	free(s);
}

/*
 * DFS recursive graph traversal.
 */
void dfsagl_dfs_traverse_rec(struct adjlgraph* g, int u, bool* vis)
{
	vis[u] = true;
	struct adjlgedge* edge = g->vertexlist[u]->edgeslist;
	while (edge) {
		if (!vis[edge->vertexindex])
			dfsagl_dfs_traverse_rec(g, edge->vertexindex, vis);
		edge = edge->next;
	}
}

/*
 * Find ancestors of each node in the given adjacency list graph.
 * Returns an array of linked lists. Each array index is the vertice number and each value is a
 * linked list of ancestors for the given vertice.
 *
 * Time Complexity: O(V^2)
 * Auxiliary Space: O(|V| + |E|)
 */
struct dfsalgancestornode** dfsalg_find_ancestors(struct adjlgraph* g)
{
	size_t n = g->numvertices;
	struct dfsalgancestornode** result = calloc(n, sizeof(struct dfsalgancestornode));

	// Create an adjancency list with
	// edges reversed
	struct adjlgraph* rev = adjlgraph_create_copy_from(g, true);
	if (rev == NULL) {
		printf("Memory error: failed to allocate memory for reversed graph!\n");
		abort();
	}

	bool visited[n];

	// Resultant List where for each
    // index i from 0 to n-1 the resultant
    // sorted ancestors list for ith
    // index will be stored
	for (int i = 0; i < n; ++i) {
		// init visited to false
		for (int j = 0; j < n; ++j) {
			visited[j] = false;
		}

		// current vertice has no ancestors by default
		result[i] = NULL;

		// traverse reversed graph to find current vertice neighbors
		dfsagl_dfs_traverse_rec(rev, i, visited);

		// linked lits of ancestor nodes
		struct dfsalgancestornode* first = NULL;
		struct dfsalgancestornode* current = NULL;
		struct dfsalgancestornode* prev = NULL;

		for (int j = 0; j < n; j++) {
			// All the ancestors for node i
			// will be visited after DFS call
			if (visited[j] && (i != j)) {
				current = (struct dfsalgancestornode*)malloc(sizeof(struct dfsalgancestornode));
				current->vertice = j;
				current->next = NULL;
				if (prev) prev->next = current;
				prev = current;
			}

			if (!first) first = current;
		}

		// Store the resultant node list in the
		// corresponding index
		result[i] = first;
	}

	// release reversed graph
	adjlgraph_destroy(rev);

	return result;
}

/*
 * Prints ancestors list.
 */
void dfsalg_print_ancestors(struct dfsalgancestornode** ancestors, uint n)
{
	for (int i = 0; i < n; ++i) {
		printf("[%i] -> ", i);

		struct dfsalgancestornode* path = ancestors[i];
		while (path) {
			printf("[%i] -> ", path->vertice);
			path = path->next;
		}

		printf("NULL\n");
	}
}

/*
 * Releases ancestors array from memory.
 * Note: ancestors is an array of linked lists.
 */
void dfsalg_destroy_ancestors(struct dfsalgancestornode** a, int n) {
	struct dfsalgancestornode* prev;
	struct dfsalgancestornode* cur;
	for (int i = 0; i < n; ++i) {
		cur = a[i];
		while (cur) {
			prev = cur;
			cur = cur->next;
			free(prev);
		}

		a[i] = NULL;
	}

	free(a);
}


