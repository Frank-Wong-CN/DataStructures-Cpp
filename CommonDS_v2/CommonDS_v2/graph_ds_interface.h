#ifndef DSV2_GRAPH_DS_INTERFACE_H
#define DSV2_GRAPH_DS_INTERFACE_H

#include "common.h"

#ifndef CommonDS_v2_List_ElementType
#define CommonDS_v2_AdjacencyList_ExtraDataType CommonDS_v2_PointerSize
#endif

#ifndef CommonDS_v2_AdjacencyList_WeightType
#define CommonDS_v2_AdjacencyList_WeightType CommonDS_v2_PointerSize
#endif

// TODO: Seperate graph DS and graph algorithm completely, such as:
//CommonDS_v2_AdjacencyList_WeightType CommonDS_v2_Graph_EdgeWeight(CommonDS_v2_Edge E);
// In order to hide the implementation detail of the underlying DS from the graph

CommonDS_v2_Graph CommonDS_v2_Graph_CreateGraph();
void CommonDS_v2_Graph_AddVertex(CommonDS_v2_List_ElementType X, CommonDS_v2_Graph G);
void CommonDS_v2_Graph_RemoveVertex(CommonDS_v2_List_ElementType X, CommonDS_v2_Graph G);
CommonDS_v2_Vertex CommonDS_v2_Graph_FindVertex(CommonDS_v2_List_ElementType X, CommonDS_v2_Graph G);
CommonDS_v2_SizeType CommonDS_v2_Graph_CountVertex(CommonDS_v2_Graph G);

void CommonDS_v2_Graph_ConnectVertex(CommonDS_v2_List_ElementType X1, CommonDS_v2_List_ElementType X2, CommonDS_v2_AdjacencyList_WeightType N, CommonDS_v2_Graph G, int Directed);
void CommonDS_v2_Graph_DisconnectVertex(CommonDS_v2_List_ElementType X1, CommonDS_v2_List_ElementType X2, CommonDS_v2_Graph G, int Directed);
CommonDS_v2_Edge CommonDS_v2_Graph_FindEdge(CommonDS_v2_List_ElementType X1, CommonDS_v2_List_ElementType X2, CommonDS_v2_Graph G);
CommonDS_v2_List CommonDS_v2_Graph_FindNeighborTo(CommonDS_v2_List_ElementType X, CommonDS_v2_Graph G);
CommonDS_v2_List CommonDS_v2_Graph_FindNeighborFrom(CommonDS_v2_List_ElementType X, CommonDS_v2_Graph G);
int CommonDS_v2_Graph_CountEdge(CommonDS_v2_Graph G);
CommonDS_v2_SizeType CommonDS_v2_Graph_InDegree(CommonDS_v2_List_ElementType X, CommonDS_v2_Graph G);
CommonDS_v2_SizeType CommonDS_v2_Graph_OutDegree(CommonDS_v2_List_ElementType X, CommonDS_v2_Graph G);

void CommonDS_v2_Graph_AttachDataToVertex(CommonDS_v2_AdjacencyList_ExtraDataType Data, CommonDS_v2_List_ElementType V, CommonDS_v2_Graph G);
void CommonDS_v2_Graph_AttachDataToEdge(CommonDS_v2_AdjacencyList_ExtraDataType Data, CommonDS_v2_List_ElementType X1, CommonDS_v2_List_ElementType X2, CommonDS_v2_Graph G, int Directed);

void CommonDS_v2_Graph_MakeEmpty(CommonDS_v2_Graph G);
void CommonDS_v2_Graph_DeleteGraph(CommonDS_v2_Graph *G);

#endif