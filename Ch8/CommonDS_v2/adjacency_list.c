#include "adjacency_list.h"

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

void AttachDataToVertex(ExtraDataSize Data, ElementType V, Graph G)
{}

void AttachDataToEdge(ExtraDataSize Data, ElementType From, ElementType To, Graph G, int Directed)
{}