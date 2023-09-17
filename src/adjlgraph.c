/*
 * adjlgraph.c
 *
 *  Created on: 26/08/2023
 *      Author: Tiago C. Teixeira
 * Description: C implementation for adjacency list graph data structure.
 */

#include <stdio.h>
#include <stdlib.h>
#include "adjlgraph.h"


/*
 * Create a new graph vertex.
 */
struct adjlgvertex* adjlgraph_createvertex(void* vertexdata)
{
	struct adjlgvertex* result = (struct adjlgvertex*)malloc(sizeof(*result));
	if (!result) {
		printf("Memory error when allocating graph vertex!");
		abort();
	}
	else {
		result->vertexdata = vertexdata;
		result->edgeslist = NULL;
	}

	return result;
}

/*
 * Create a new graph edge node.
 */
struct adjlgedge* adjlgraph_createedge(int vindex, void* edgedata)
{
	struct adjlgedge* result = (struct adjlgedge*)malloc(sizeof(*result));
	if (!result) {
		printf("Memory error when allocating graph edge node!");
		abort();
	}
	else {
		result->next = NULL;
		result->vertexindex = vindex;
		result->edgedata = edgedata;
	}

	return result;
}

/*
 * Create a new graph.
 */
struct adjlgraph* adjlgraph_creategraph(int numvertices,
		adjlgraph_freedata freevertexdatafunc,
		adjlgraph_freedata freeedgedatafunc,
		adjlgraph_printdata printvertexfunc,
		adjlgraph_printdata printedgefunc)
{
	struct adjlgraph* result = (struct adjlgraph*)malloc(sizeof(struct adjlgraph));

	if (result == NULL) {
		printf("Memory error when allocating graph struct!");
		abort();
	}
	else {
		result->vertexlist =
				(struct adjlgvertex**)malloc(numvertices * sizeof(struct adjlgvertex*));

		if (result->vertexlist == NULL) {
			printf("Memory error when allocating graph vertex list!");
			free(result);
			abort();
		}
		else {
			// initiaize list elements to NULL
			for (int i = 0; i < numvertices; i++)
				result->vertexlist[i] = NULL;

			result->freeedgedata = freeedgedatafunc;
			result->freevertexdata = freevertexdatafunc;
			result->printedge = printedgefunc;
			result->printvertex = printvertexfunc;
			result->numvertices = numvertices;
		}
	}

	return result;
}

/*
 * Add vertex to graph.
 */
void adjlgraph_addvertex(struct adjlgraph* graph, int vindex, void* vdata)
{
	if (vindex < graph->numvertices) {
		struct adjlgvertex* newvertex = adjlgraph_createvertex(vdata);
		graph->vertexlist[vindex] = newvertex;
	}
	else {
		printf("Out of range error: Vertex index must be less than vertex array size.");
		abort();
	}
}

/*
 * Add edge to graph.
 */
void adjlgraph_addedge(struct adjlgraph* graph, int from, int to, void* edgedata)
{
	struct adjlgedge* newedge = adjlgraph_createedge(to, edgedata);
	struct adjlgedge* edge = graph->vertexlist[from]->edgeslist;

	if (edge)
	{
		// insert at end of edges list
		while (edge->next != NULL)
			edge = edge->next;

		edge->next = newedge;
	}
	else {
		graph->vertexlist[from]->edgeslist = newedge;
	}
}

// Print the graph
void adjlgraph_print(struct adjlgraph* graph)
{
	int v;
	for (v = 0; v < graph->numvertices; v++) {
		struct adjlgedge* temp = graph->vertexlist[v]->edgeslist;
		printf("\n Vertex %d: \n", v);

		if (graph->printvertex) {
			graph->printvertex(graph->vertexlist[v]->vertexdata);
		}

		printf("\n");

		// print vertex edges
		while (temp) {
			printf("%d ", temp->vertexindex);

			if (graph->printedge) {
				graph->printedge(temp->edgedata);
			}

			temp = temp->next;
			if (temp)
				printf(" -> ");
		}

		printf("\n");
	}
}

/*
 * Releases graph resources from memory.
 */
void adjlgraph_destroy(struct adjlgraph* graph)
{
	int numvertices = graph->numvertices;
	for (int v = 0; v < numvertices; ++v) {
		struct adjlgedge* e = graph->vertexlist[v]->edgeslist;
		struct adjlgedge* prev = NULL;
		while (e != NULL) {
			if (graph->freeedgedata != NULL)
				if (e->edgedata != NULL)
					graph->freeedgedata(e->edgedata);

			prev = e;
			e = e->next;
			free(prev);
		}

		if (graph->vertexlist[v] != NULL)
			if (graph->freevertexdata != NULL)
				if (graph->vertexlist[v]->vertexdata != NULL)
					graph->freevertexdata(graph->vertexlist[v]->vertexdata);

//		free(graph->vertexlist[v]);
	}

	free(graph->vertexlist);
	free(graph);
}



