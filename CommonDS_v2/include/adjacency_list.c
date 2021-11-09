#include "adjacency_list.h"
#include "common.h"

Graph CreateGraph()
{ return (Graph)CreateList(); }

void AddVertex(ElementType X, Graph G)
{
	if (FindVertex(X, G))
		return;
	
	Insert(X, G, Last(G));
}

void RemoveVertex(ElementType X, Graph G)
{
	Vertex V;	
	for (V = First(G); V != NULL; V = Advance(V))
		if (V->Param != NULL)
			Delete(X, (List)V->Param);
	Delete(X, G);
}

Vertex FindVertex(ElementType X, Graph G)
{ return (Vertex)Find(X, G); }

int CountVertex(Graph G)
{ return Size(G); }

void Connect(ElementType From, ElementType To, WeightType N, Graph G, int Directed)
{
	Vertex V1 = FindVertex(From, G);
	Vertex V2 = FindVertex(To, G);
	
	if (!V1 || !V2)
		return;
	
	if (!V1->Param)
		V1->Param = (ExtraDataSize)CreateList();
	
	Edge E = Find(To, (List)V1->Param);
	if (E == NULL)
		E = Insert(To, (List)V1->Param, Last((List)V1->Param));
	E->Param = N;
	
	if (!Directed)
	{
		if (!V2->Param)
			V2->Param = (ExtraDataSize)CreateList();
		E = Find(From, (List)V2->Param);
		if (E == NULL)
			E = Insert(From, (List)V2->Param, Last((List)V2->Param));
		E->Param = N;
	}
}

void DisconnectVertex(ElementType From, ElementType To, Graph G, int Directed)
{
	Vertex V1 = FindVertex(From, G);
	Vertex V2 = FindVertex(To, G);
	
	if (!V1 || !V2)
		return;
	
	if (!V1->Param || !V2->Param)
		return;
	
	Delete(To, (List)V1->Param);
	if (!Directed)
		Delete(From, (List)V2->Param);
}

Edge FindEdge(ElementType X1, ElementType X2, Graph G)
{
	Vertex V = FindVertex(X1, G);
	if (!V)
		return NULL;
	
	AdjacencyList L = (AdjacencyList)V->Param;
	return Find(X2, L);
}

int CountEdge(Graph G)
{
	if (G == NULL)
		return -1;
	
	Vertex V;
	Edge E;
	int C = 0;
	
	for (V = First(G); V != NULL; V = Advance(V))
		if (V->Param)
			for (E = First((List)V->Param); E != NULL; E = Advance(E))
				C++;
	
	return C;
}

void AttachDataToVertex(ExtraDataSize Data, ElementType X, Graph G)
{
	Vertex V = FindVertex(X, G);
	if (V)
		V->Data = Data;
}

void AttachDataToEdge(ExtraDataSize Data, ElementType X1, ElementType X2, Graph G, int Directed)
{
	Edge E = FindEdge(X1, X2, G);
	if (E)
		E->Data = Data;
	
	if (!Directed)
	{
		E = FindEdge(X2, X1, G);
		if (E)
			E->Data = Data;
	}
}

void PrintAdjacencyList(Graph G)
{
	Vertex V;
	Edge E;
	for (V = First(G); V != NULL; V = Advance(V))
	{
		__StrClingOutput("\"%d\": [ ", "\"{}\": [ ", V->Element);
		if (V->Param)
			for (E = First((AdjacencyList)V->Param); E != NULL; E = Advance(E))
				__StrClingOutput("\"%d\"%c", "\"{}\"{}", E->Element, (E->Next == NULL ? ' ' : ','));
		__StrClingOutput("]\n", "]\n", 0);
	}
}

void DestroyGraph(Graph *G)
{
	Vertex V;
	for (V = First(*G); V != NULL; V = Advance(V))
		if (V->Param)
			DeleteList((List *)&(V->Param));
	DeleteList(G);
	*G = NULL;
}
