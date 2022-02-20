#include "adjacency_list.h"
#include "common.h"

CommonDS_v2_Graph CommonDS_v2_Graph_CreateGraph()
{ return (CommonDS_v2_Graph)CommonDS_v2_List_CreateList(); }

void CommonDS_v2_Graph_AddVertex(CommonDS_v2_List_ElementType X, CommonDS_v2_Graph G)
{
	if (CommonDS_v2_Graph_FindVertex(X, G))
		return;
	
	CommonDS_v2_List_Insert(X, G, CommonDS_v2_List_Last(G));
}

void CommonDS_v2_Graph_RemoveVertex(CommonDS_v2_List_ElementType X, CommonDS_v2_Graph G)
{
	CommonDS_v2_Vertex V;	
	for (V = CommonDS_v2_List_First(G); V != NULL; V = CommonDS_v2_List_Advance(V))
		if (V->Param != (CommonDS_v2_AdjacencyList_ExtraDataType)NULL)
			CommonDS_v2_List_Delete(X, (CommonDS_v2_List)V->Param);
	CommonDS_v2_List_Delete(X, G);
}

CommonDS_v2_Vertex CommonDS_v2_Graph_FindVertex(CommonDS_v2_List_ElementType X, CommonDS_v2_Graph G)
{ return (CommonDS_v2_Vertex)CommonDS_v2_List_Find(X, G); }

CommonDS_v2_SizeType CommonDS_v2_Graph_CountVertex(CommonDS_v2_Graph G)
{ return CommonDS_v2_List_Size(G); }

void CommonDS_v2_Graph_ConnectVertex(CommonDS_v2_List_ElementType From, CommonDS_v2_List_ElementType To, CommonDS_v2_AdjacencyList_ExtraDataType N, CommonDS_v2_Graph G, int Directed)
{
	CommonDS_v2_Vertex V1 = CommonDS_v2_Graph_FindVertex(From, G);
	CommonDS_v2_Vertex V2 = CommonDS_v2_Graph_FindVertex(To, G);
	
	if (!V1 || !V2)
		return;
	
	if (!V1->Param)
		V1->Param = (CommonDS_v2_AdjacencyList_ExtraDataType)CommonDS_v2_List_CreateList();
	
	CommonDS_v2_Edge E = CommonDS_v2_List_Find(To, (CommonDS_v2_List)V1->Param);
	if (E == NULL)
		E = CommonDS_v2_List_Insert(To, (CommonDS_v2_List)V1->Param, CommonDS_v2_List_Last((CommonDS_v2_List)V1->Param));
	E->Param = N;
	
	if (!Directed)
	{
		if (!V2->Param)
			V2->Param = (CommonDS_v2_AdjacencyList_ExtraDataType)CommonDS_v2_List_CreateList();
		E = CommonDS_v2_List_Find(From, (CommonDS_v2_List)V2->Param);
		if (E == NULL)
			E = CommonDS_v2_List_Insert(From, (CommonDS_v2_List)V2->Param, CommonDS_v2_List_Last((CommonDS_v2_List)V2->Param));
		E->Param = N;
	}
}

void CommonDS_v2_Graph_DisconnectVertex(CommonDS_v2_List_ElementType From, CommonDS_v2_List_ElementType To, CommonDS_v2_Graph G, int Directed)
{
	CommonDS_v2_Vertex V1 = CommonDS_v2_Graph_FindVertex(From, G);
	CommonDS_v2_Vertex V2 = CommonDS_v2_Graph_FindVertex(To, G);
	
	if (!V1 || !V2)
		return;
	
	if (!V1->Param || !V2->Param)
		return;
	
	CommonDS_v2_List_Delete(To, (CommonDS_v2_List)V1->Param);
	if (!Directed)
		CommonDS_v2_List_Delete(From, (CommonDS_v2_List)V2->Param);
}

CommonDS_v2_Edge CommonDS_v2_Graph_FindEdge(CommonDS_v2_List_ElementType X1, CommonDS_v2_List_ElementType X2, CommonDS_v2_Graph G)
{
	CommonDS_v2_Vertex V = CommonDS_v2_Graph_FindVertex(X1, G);
	if (!V)
		return NULL;
	
	CommonDS_v2_AdjacencyList L = (CommonDS_v2_AdjacencyList)V->Param;
	return CommonDS_v2_List_Find(X2, L);
}

CommonDS_v2_List CommonDS_v2_Graph_FindNeighborTo(CommonDS_v2_List_ElementType X, CommonDS_v2_Graph G)
{
	CommonDS_v2_List L = NULL;
	
	CommonDS_v2_Vertex V = CommonDS_v2_Graph_FindVertex(X, G);
	if (V)
		L = CommonDS_v2_List_CloneList((CommonDS_v2_List)V->Param);
	
	return L;
}

CommonDS_v2_List CommonDS_v2_Graph_FindNeighborFrom(CommonDS_v2_List_ElementType X, CommonDS_v2_Graph G)
{
	CommonDS_v2_Vertex V = NULL;
	CommonDS_v2_Edge E = NULL;
	
	CommonDS_v2_List L = CommonDS_v2_List_CreateList();
	
	for (V = CommonDS_v2_List_First(G); V != NULL; V = CommonDS_v2_List_Advance(V))
		if (V->Param)
			for (E = CommonDS_v2_List_First((CommonDS_v2_List)V->Param); E != NULL; E = CommonDS_v2_List_Advance(E))
				if (E->Element == X)
					CommonDS_v2_List_Insert((CommonDS_v2_List_ElementType)V, L, L);
	
	return L;
}

int CommonDS_v2_Graph_CountEdge(CommonDS_v2_Graph G)
{
	if (G == NULL)
		return -1;
	
	CommonDS_v2_Vertex V;
	CommonDS_v2_Edge E;
	int C = 0;
	
	for (V = CommonDS_v2_List_First(G); V != NULL; V = CommonDS_v2_List_Advance(V))
		if (V->Param)
			for (E = CommonDS_v2_List_First((CommonDS_v2_List)V->Param); E != NULL; E = CommonDS_v2_List_Advance(E))
				C++;
	
	return C;
}

CommonDS_v2_SizeType CommonDS_v2_Graph_InDegree(CommonDS_v2_List_ElementType X, CommonDS_v2_Graph G)
{
	if (G == NULL || !CommonDS_v2_Graph_FindVertex(X, G))
		return 0;
	
	CommonDS_v2_Vertex V;
	CommonDS_v2_Edge E;
	CommonDS_v2_SizeType D = 0;
	
	for (V = CommonDS_v2_List_First(G); V != NULL; V = CommonDS_v2_List_Advance(V))
		if (V->Param)
			for (E = CommonDS_v2_List_First((CommonDS_v2_List)V->Param); E != NULL; E = CommonDS_v2_List_Advance(E))
				if (E->Element == X)
					D++;
	
	return D;
}

CommonDS_v2_SizeType CommonDS_v2_Graph_OutDegree(CommonDS_v2_List_ElementType X, CommonDS_v2_Graph G)
{
	if (G == NULL)
		return 0;
	
	CommonDS_v2_Vertex V = CommonDS_v2_Graph_FindVertex(X, G);
	if (!V)
		return 0;
	
	if (!V->Param)
		return 0;
	else return CommonDS_v2_List_Size((CommonDS_v2_List)V->Param);
}

void CommonDS_v2_Graph_AttachDataToVertex(CommonDS_v2_AdjacencyList_ExtraDataType Data, CommonDS_v2_List_ElementType X, CommonDS_v2_Graph G)
{
	CommonDS_v2_Vertex V = CommonDS_v2_Graph_FindVertex(X, G);
	if (V)
		V->Data = Data;
}

void CommonDS_v2_Graph_AttachDataToEdge(CommonDS_v2_AdjacencyList_ExtraDataType Data, CommonDS_v2_List_ElementType X1, CommonDS_v2_List_ElementType X2, CommonDS_v2_Graph G, int Directed)
{
	CommonDS_v2_Edge E = CommonDS_v2_Graph_FindEdge(X1, X2, G);
	if (E)
		E->Data = Data;
	
	if (!Directed)
	{
		E = CommonDS_v2_Graph_FindEdge(X2, X1, G);
		if (E)
			E->Data = Data;
	}
}

void CommonDS_v2_Graph_MakeEmpty(CommonDS_v2_Graph G)
{
	CommonDS_v2_Vertex V;
	for (V = CommonDS_v2_List_First(G); V != NULL;)
	{
		if (V->Param)
			CommonDS_v2_List_DeleteList((CommonDS_v2_List *)&(V->Param));
		CommonDS_v2_Vertex tmp = V;
		V = CommonDS_v2_List_Advance(V);
		free(tmp);
	}

	G->Next = NULL;
}

void CommonDS_v2_Graph_DeleteGraph(CommonDS_v2_Graph *G)
{
	CommonDS_v2_Vertex V;
	for (V = CommonDS_v2_List_First(*G); V != NULL; V = CommonDS_v2_List_Advance(V))
		if (V->Param)
			CommonDS_v2_List_DeleteList((CommonDS_v2_List *)&(V->Param));
	CommonDS_v2_List_DeleteList(G);
	*G = NULL;
}
