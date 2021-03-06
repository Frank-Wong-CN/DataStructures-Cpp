#ifndef _ADJACENCY_LIST_H
#define _ADJACENCY_LIST_H

#include "node_impl_adjacency_list.h"

//#include "../Ch7/CommonDS_v2/string.h"
//#include "../Ch4/CommonDS_v2/bintree.h"
#include "../Ch3/CommonDS_v2/list.h"

//typedef AVLTree Graph;
typedef List AdjacencyList, Vertex, Edge, Graph;

#include "graph_ds_interface.h"

void PrintAdjacencyList(Graph G);

#endif