#include "graph.h"

Vertex DepthFirstYield(ElementType X, Graph G)
{
	if (G == NULL)
	{
		if (!__Graph_CurrentYieldingGraph)
			return NULL;
		
		Graph G;
		Vertex V;
		Edge E;
		
		G = (Vertex)Pop(__Graph_CurrentYieldingGraph);
		if (!Size(__Graph_CurrentYieldingGraph))
			return NULL;
		
		V = (Vertex)Pop(__Graph_CurrentYieldingGraph);
		if (!Find((ElementType)V, __Graph_CurrentYieldedNodeSet))
		{
			Enqueue((ElementType)V, __Graph_CurrentYieldedNodeSet);
			if (V->Param)
				for (E = First((List)V->Param); E != NULL; E = Advance(E))
					Push((ElementType)FindVertex(E->Element, G), __Graph_CurrentYieldingGraph);
		}
		else V = NULL;
		
		Push((ElementType)G, __Graph_CurrentYieldingGraph);
		
		if (V) return V;
		else return DepthFirstYield(X, NULL);
	}
	else
	{
		if (__Graph_CurrentYieldingGraph)
			DisposeStack(&__Graph_CurrentYieldingGraph);
		
		if (__Graph_CurrentYieldedNodeSet)
			DeleteList(&__Graph_CurrentYieldedNodeSet);
		
		__Graph_CurrentYieldingGraph = CreateStack();
		__Graph_CurrentYieldedNodeSet = CreateList();
		Push((ElementType)FindVertex(X, G), __Graph_CurrentYieldingGraph);
		Push((ElementType)G, __Graph_CurrentYieldingGraph);
		return DepthFirstYield(X, NULL);
	}
}

Vertex BreadthFirstYield(ElementType X, Graph G)
{
	if (G == NULL)
	{
		if (!__Graph_CurrentYieldingGraph)
			return NULL;
		
		Graph G;
		Vertex V;
		Edge E;
		
		G = (Vertex)Pop(__Graph_CurrentYieldingGraph);
		if (!Size(__Graph_CurrentYieldingGraph))
			return NULL;
		
		V = (Vertex)Dequeue(__Graph_CurrentYieldingGraph);
		if (!Find((ElementType)V, __Graph_CurrentYieldedNodeSet))
		{
			Enqueue((ElementType)V, __Graph_CurrentYieldedNodeSet);
			if (V->Param)
				for (E = First((List)V->Param); E != NULL; E = Advance(E))
					Enqueue((ElementType)FindVertex(E->Element, G), __Graph_CurrentYieldingGraph);
		}
		else V = NULL;
		
		Push((ElementType)G, __Graph_CurrentYieldingGraph);
		
		if (V) return V;
		else return BreadthFirstYield(X, NULL);
	}
	else
	{
		if (__Graph_CurrentYieldingGraph)
			DisposeQueue(&__Graph_CurrentYieldingGraph);
		
		if (__Graph_CurrentYieldedNodeSet)
			DeleteList(&__Graph_CurrentYieldedNodeSet);
		
		__Graph_CurrentYieldingGraph = CreateQueue();
		__Graph_CurrentYieldedNodeSet = CreateList();
		Enqueue((ElementType)FindVertex(X, G), __Graph_CurrentYieldingGraph);
		Push((ElementType)G, __Graph_CurrentYieldingGraph);
		return BreadthFirstYield(X, NULL);
	}
}

void PushGraphYieldState()
{
	if (!__Graph_CurrentYieldingGraph || !__Graph_CurrentYieldedNodeSet)
		return;
	
	if (__Graph_SavedYieldState == NULL)
		__Graph_SavedYieldState = CreateStack();
	
	List Tmp = (List)CloneList(__Graph_CurrentYieldingGraph);
	Push((ElementType)Tmp, __Graph_SavedYieldState);
	
	Tmp = (List)CloneList(__Graph_CurrentYieldedNodeSet);
	Push((ElementType)Tmp, __Graph_SavedYieldState);
}

void PopGraphYieldState()
{
	if (__Graph_SavedYieldState == NULL)
		return;
	
	if (Size(__Graph_SavedYieldState) == 0)
		return;
	
	DeleteList(&__Graph_CurrentYieldedNodeSet);
	__Graph_CurrentYieldedNodeSet = (List)Pop(__Graph_SavedYieldState);
	
	DeleteList(&__Graph_CurrentYieldingGraph);
	__Graph_CurrentYieldingGraph = (Stack)Pop(__Graph_SavedYieldState);
}

List DepthFirstSearch(ElementType X, Graph G)
{
	if (G == NULL || !FindVertex(X, G))
		return NULL;
	
	List L = CreateList();
	Stack S = CreateStack();
	Vertex V;
	Edge E;
	
	Push(X, S);
	while (Size(S) > 0)
	{
		V = Find(Pop(S), G);
		if (Find((ElementType)V, L))
			continue;
		
		Insert((ElementType)V, L, Last(L));
		if (V->Param)
			for (E = First((List)V->Param); E != NULL; E = Advance(E))
				Push(E->Element, S);
	}
	
	DisposeStack(&S);
	return L;
}

List BreadthFirstSearch(ElementType X, Graph G)
{
	if (G == NULL || !FindVertex(X, G))
		return NULL;
	
	List L = CreateList();
	Queue S = CreateQueue();
	Vertex V;
	Edge E;
	
	Enqueue(X, S);
	while (Size(S) > 0)
	{
		V = Find(Dequeue(S), G);
		if (Find((ElementType)V, L))
			continue;
		
		Insert((ElementType)V, L, Last(L));
		if (V->Param)
			for (E = First((List)V->Param); E != NULL; E = Advance(E))
				Enqueue(E->Element, S);
	}
	
	DisposeQueue(&S);
	return L;
}

List SpanningForestFromGraph(Graph G);

Graph MST_Prim(ElementType X, Graph G)
{
	Vertex V = Find(X, G);
	if (!V)
		return NULL;
	
	Graph MST = CreateList();
	AddVertex(V, MST);
	
	//?
}

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
int IsConnectedGraph(Graph G)
{
	List L = GetAllConnectedComponents(G);
	size_t R = Size(L);
	DeleteList(&L);
	return R == 1;
}

List GetAllConnectedComponents(Graph G)
{
	Vertex P, V, Y;
	List Visited = CreateList();
	List Components = CreateList();
	
	for (P = G, V = First(G); V != NULL; P = V, V = Advance(V))
	{
		if (Find((ElementType)V, Visited))
			continue;
		
		PushGraphYieldState();
		
		ElementType X = Retrieve(V);
		for (Y = DepthFirstYield(X, G); Y != NULL; Y = DepthFirstYield(X, NULL))
			Insert((ElementType)Y, Visited, Last(Visited));
		Insert((ElementType)P, Components, Last(Components));
		
		PopGraphYieldState();
	}
	
	DeleteList(&Visited);
	return Components;
}

// Directed
int IsStronglyConnectedGraph(Graph G)
{ return 0; }

List GetAllStronglyConnectedComponents(Graph G)
{ return NULL; }
