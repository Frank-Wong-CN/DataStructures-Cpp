#ifndef DSV2_GRAPH_H
#define DSV2_GRAPH_H

#ifndef DSV2_GRAPH_DS_INTERFACE_H
#include "adjacency_list.h"
#ifndef _MSC_VER
#warning Graph implementation not found, basic implementation included.
#endif
#endif

#include "stack.h"
#include "queue.h"

#include "tnode_impl_basic.h"
#include "tree.h"

CommonDS_v2_List CommonDS_v2_Graph_CurrentYieldingGraph = NULL;
CommonDS_v2_List CommonDS_v2_Graph_CurrentYieldedNodeSet = NULL;
CommonDS_v2_Stack CommonDS_v2_Graph_SavedYieldState = NULL;

CommonDS_v2_Vertex CommonDS_v2_Graph_DepthFirstYield(CommonDS_v2_List_ElementType X, CommonDS_v2_Graph G);
CommonDS_v2_Vertex CommonDS_v2_Graph_BreadthFirstYield(CommonDS_v2_List_ElementType X, CommonDS_v2_Graph G);
void CommonDS_v2_Graph_PushYieldState();
void CommonDS_v2_Graph_PopYieldState();

CommonDS_v2_List CommonDS_v2_Graph_DepthFirstTraverse(CommonDS_v2_List_ElementType X, CommonDS_v2_Graph G);
CommonDS_v2_List CommonDS_v2_Graph_BreadthFirstTraverse(CommonDS_v2_List_ElementType X, CommonDS_v2_Graph G);
void CommonDS_v2_Graph_SpanningForestFromGraph(CommonDS_v2_Graph G, CommonDS_v2_Tree *Out, CommonDS_v2_SizeType *Size);
CommonDS_v2_Graph CommonDS_v2_Graph_MST_Prim(CommonDS_v2_Graph G);
CommonDS_v2_Graph CommonDS_v2_Graph_MST_Kruskal(CommonDS_v2_Graph G);
CommonDS_v2_List CommonDS_v2_Graph_PathFinding_Dijkstra(CommonDS_v2_Graph G);
CommonDS_v2_List CommonDS_v2_Graph_PathFinding_Floyd(CommonDS_v2_Graph G);

int CommonDS_v2_Graph_IsSimpleGraph(CommonDS_v2_Graph G);
int CommonDS_v2_Graph_IsDirectedGraph(CommonDS_v2_Graph G);
int CommonDS_v2_Graph_IsCyclicGraph(CommonDS_v2_Graph G);
int CommonDS_v2_Graph_IsCompleteGraph(CommonDS_v2_Graph G);
int CommonDS_v2_Graph_IsPathSimple(CommonDS_v2_List L);
int CommonDS_v2_Graph_IsPathCircuit(CommonDS_v2_List L);

// Undirected
int CommonDS_v2_Graph_IsConnectedGraph(CommonDS_v2_Graph G);
void CommonDS_v2_Graph_GetAllConnectedComponents(CommonDS_v2_Graph G, CommonDS_v2_Graph *Out, CommonDS_v2_SizeType *Size);

// Directed
int CommonDS_v2_Graph_IsStronglyConnectedGraph(CommonDS_v2_Graph G);
void CommonDS_v2_Graph_GetAllStronglyConnectedComponents(CommonDS_v2_Graph G, CommonDS_v2_Graph *Out, CommonDS_v2_SizeType *Size);

#endif