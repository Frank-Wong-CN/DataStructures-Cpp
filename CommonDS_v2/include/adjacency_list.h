#ifndef _ADJACENCY_LIST_H
#define _ADJACENCY_LIST_H

#include "node_impl_adjacency_list.h"

//#include "string.h"
//#include "bintree.h"
#include "list.h"

//typedef AVLTree Graph;
typedef List AdjacencyList, Vertex, Edge, Graph;

#include "graph_ds_interface.h"

void PrintAdjacencyList(Graph G);

#endif