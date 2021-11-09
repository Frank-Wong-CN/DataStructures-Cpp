#ifndef _GRAPH_H
#define _GRAPH_H

#ifndef _GRAPH_DS_INTERFACE_H
#error Include a Graph implementation before including "graph.h"!
#endif

#include "stack.h"
#include "queue.h"

#include "tnode_impl_basic.h"
#include "tree.h"

List __Graph_CurrentYieldingGraph = NULL;
Stack __Graph_SavedYieldState = NULL;

Vertex DepthFirstYield(ElementType X, Graph G);
Vertex BreadthFirstYield(ElementType X, Graph G);
void PushGraphYieldState();
void PopGraphYieldState();

List DepthFirstSearch(ElementType X, Graph G);
List BreadthFirstSearch(ElementType X, Graph G);
void SpanningForestFromGraph(Graph G, Tree *Out, size_t *Size);
Graph MST_Prim(Graph G);
Graph MST_Kruskal(Graph G);
List PathFinding_Dijkstra(Graph G);
List PathFinding_Floyd(Graph G);

int IsSimpleGraph(Graph G);
int IsDirectedGraph(Graph G);
int IsCyclicGraph(Graph G);
int IsCompleteGraph(Graph G);
int IsPathSimple(List L);
int IsPathCircuit(List L);

// Undirected
int IsConnectedGraph(Graph G);
void GetAllConnectedComponents(Graph G, Graph *Out, size_t *Size);

// Directed
int IsStronglyConnectedGraph(Graph G);
void GetAllStronglyConnectedComponents(Graph G, Graph *Out, size_t *Size);

int InDegree(ElementType X, Graph G);
int OutDegree(ElementType X, Graph G);

#endif