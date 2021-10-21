#ifndef _ADJACENCY_LIST_H
#define _ADJACENCY_LIST_H

#include "node_impl_adjacency_list.h"

//#include "../Ch7/CommonDS_v2/string.h"
//#include "../Ch4/CommonDS_v2/bintree.h"
#include "../Ch3/CommonDS_v2/list.h"

#ifdef __CLING__
	#define __StrClingOutput(PrintfVer, FmtVer, ...) fmt::print(FmtVer, __VA_ARGS__)
	#ifdef __STR_OUTPUT__
		#define D(...) fmt::print(__VA_ARGS__)
	#else
		#define D(...)
	#endif
#else
	#define __StrClingOutput(PrintfVer, FmtVer, ...) printf(PrintfVer, __VA_ARGS__)
	#define D(...)
#endif

//typedef AVLTree Graph;
typedef List AdjacencyList, Vertex, Edge, Graph;

#include "graph_ds_interface.h"

void PrintAdjacencyList(Graph G);

#endif