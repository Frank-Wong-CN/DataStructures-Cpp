#ifndef _ADJACENCY_LIST_H
#define _ADJACENCY_LIST_H

#include "node_impl_adjacency_list.h"

//#include "../Ch7/CommonDS_v2/string.h"
//#include "../Ch4/CommonDS_v2/bintree.h"
#include "../Ch3/CommonDS_v2/list.h"

//typedef AVLTree Graph;
typedef List Vertex, Edge, Graph;

void AddVertex(ElementType X, Graph G);
void RemoveVertex(ElementType X, Graph G);
Vertex FindVertex(ElementType X, Graph G);

void Connect(ElementType X1, ElementType X2, WeightType N, Graph G, int Directed);
void DisconnectVertex(ElementType X1, ElementType X2, Graph G, int Directed);

void AttachDataToVertex(ExtraDataSize Data, ElementType V, Graph G);
void AttachDataToEdge(ExtraDataSize Data, ElementType From, ElementType To, Graph G, int Directed);

#endif