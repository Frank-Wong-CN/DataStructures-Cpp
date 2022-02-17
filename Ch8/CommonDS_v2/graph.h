#ifndef _GRAPH_H
#define _GRAPH_H

#ifndef _GRAPH_DS_INTERFACE_H
#error Include a Graph implementation before including "graph.h"!
#endif

#include "../Ch3/CommonDS_v2/stack.h"
#include "../Ch3/CommonDS_v2/queue.h"

#include "../Ch4/CommonDS_v2/tnode_impl_basic.h"
#include "../Ch4/CommonDS_v2/tree.h"

List __Graph_CurrentYieldingGraph = NULL;
List __Graph_CurrentYieldedNodeSet = NULL;
Stack __Graph_SavedYieldState = NULL;

Vertex DepthFirstYield(ElementType X, Graph G);
Vertex BreadthFirstYield(ElementType X, Graph G);
void PushGraphYieldState();
void PopGraphYieldState();

List DepthFirstTraverse(ElementType X, Graph G);
List BreadthFirstTraverse(ElementType X, Graph G);
List SpanningForestFromGraph(Graph G);
Graph MST_Prim(ElementType X, Graph G);
Graph MST_Kruskal(ElementType X, Graph G);
List PathFinding_Dijkstra(ElementType X1, ElementType X2, Graph G);
List PathFinding_Floyd(ElementType X1, ElementType X2, Graph G);

int IsSimpleGraph(Graph G);
int IsDirectedGraph(Graph G);
int IsCyclicGraph(Graph G);
int IsCompleteGraph(Graph G);
int IsPathSimple(List L);
int IsPathCircuit(List L);

// Undirected
int IsConnectedGraph(Graph G);
List GetAllConnectedComponents(Graph G);

// Directed
int IsStronglyConnectedGraph(Graph G);
List GetAllStronglyConnectedComponents(Graph G);

#endif