/*
 * adjlgraph.c
 *
 *  Created on: 26/08/2023
 *      Author: Tiago C. Teixeira
 * Description: C implementation for adjacency list graph data structure.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
struct adjlgedge* adjlgraph_createedge( int vindex, void* edgedata, double weight )
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
		result->weight = weight;
	}

	return result;
}

/*
 * Create a new graph.
 */
struct adjlgraph* adjlgraph_creategraph(int numvertices, adjlgraph_edgetype etype,
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

			result->etype = etype;
			result->freeedgedata = freeedgedatafunc;
			result->freevertexdata = freevertexdatafunc;
			result->printedge = printedgefunc;
			result->printvertex = printvertexfunc;
			result->numvertices = numvertices;
			result->_total_edges = 0;
		}
	}

	return result;
}

/*
 * Gets the number of edges in the graph.
 */
size_t adjlgraph_getnumedges(struct adjlgraph* graph) {
	if (graph->etype == UNDIRECTED_AGRAPH) return (size_t)(graph->_total_edges / 2);
	else return graph->_total_edges;
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
void adjlgraph_addedge_helper( struct adjlgraph* graph, int from, int to,
							   void* edgedata, double weight )
{
	struct adjlgedge* newedge = adjlgraph_createedge( to, edgedata, weight );
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

/*
 * Add edge to graph.
 */
void adjlgraph_addedge( struct adjlgraph* graph, int from, int to, void* edgedata,
						double weight )
{
	adjlgraph_addedge_helper( graph, from, to, edgedata, weight );

	if ( graph->etype == UNDIRECTED_AGRAPH )
		adjlgraph_addedge_helper(graph, to, from, edgedata, weight);
}

/*
 * Print the graph
 */
void adjlgraph_print(struct adjlgraph* graph)
{
	int v;
	for (v = 0; v < graph->numvertices; v++) {
		struct adjlgedge* temp = graph->vertexlist[v]->edgeslist;
		printf("Vertex [%d] ", v);

		if (graph->printvertex) {
			printf("<");
			graph->printvertex(graph->vertexlist[v]->vertexdata);
			printf(">");
		}

		printf("|");


//		else {
//			printf("graph->printvertex is undefined. Can not print graph.");
//			abort();
//		}

//		printf("\n");

		// print vertex edges
		while (temp) {
			if (graph->etype == DIRECTED_AGRAPH) {
				printf("-(%f)", temp->weight);
			}
			printf("->");
			printf("%d", temp->vertexindex);

			if (graph->printedge) {
				graph->printedge(temp->edgedata);
			}
//			else {
//				printf("graph->printedge function is undefined. Can not print graph.");
//				abort();
//			}

			temp = temp->next;


//			if (temp)
//				printf("->");
//			else
//				printf("->NULL");
		}

		printf("->NULL");

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

		// release verte struct
		free(graph->vertexlist[v]);
//		free(graph->vertexlist[v]);
	}

	free(graph->vertexlist);	// free vertex array
	free(graph);				// free graph struct
}

/*
 * Create a new graph that is a copy from a given existent graph. If 'reverse' arg is true, the direction
 * of the edges of the result copy will be resersed.
 */
struct adjlgraph* adjlgraph_create_copy_from(struct adjlgraph* s, bool reverse)
{
	int nv = s->numvertices;
	struct adjlgraph* result = adjlgraph_creategraph(
									nv, s->etype, s->freevertexdata,
									s->freeedgedata, s->printvertex, s->printedge );
	if (result == NULL) {
		printf("Memory error: failed to allocate adjacency list graph struct!");
		abort();
	}
	else {
		struct adjlgvertex* vertex;

		// create vertices
		for(int v = 0; v < nv; ++v) {
			vertex = s->vertexlist[v];
			adjlgraph_addvertex(result, v, vertex->vertexdata);
		}

		for(int v = 0; v < nv; ++v) {
			struct adjlgedge* edge = s->vertexlist[v]->edgeslist;

			if (reverse) {
				while (edge) {		// copy edges with direction reversed
					adjlgraph_addedge(result, edge->vertexindex, v, edge->edgedata, edge->weight);
					edge = edge->next;
				}
			}
			else {
				while (edge) {		// copy edges
					adjlgraph_addedge(result, v, edge->vertexindex, edge->edgedata, edge->weight);
					edge = edge->next;
				}
			}
		}
	}

	return result;
}


