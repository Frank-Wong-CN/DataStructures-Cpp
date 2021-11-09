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
		if (V->Param)
			for (E = First((List)V->Param); E != NULL; E = Advance(E))
				Push((ElementType)FindVertex(E->Element, G), __Graph_CurrentYieldingGraph);
		
		Push((ElementType)G, __Graph_CurrentYieldingGraph);
		
		return V;
	}
	else
	{
		if (__Graph_CurrentYieldingGraph)
			DisposeStack(&__Graph_CurrentYieldingGraph);
		
		__Graph_CurrentYieldingGraph = CreateStack();
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
		if (V->Param)
			for (E = First((List)V->Param); E != NULL; E = Advance(E))
				Enqueue((ElementType)FindVertex(E->Element, G), __Graph_CurrentYieldingGraph);
		
		Push((ElementType)G, __Graph_CurrentYieldingGraph);
		
		return V;
	}
	else
	{
		if (__Graph_CurrentYieldingGraph)
			DisposeQueue(&__Graph_CurrentYieldingGraph);
		
		__Graph_CurrentYieldingGraph = CreateQueue();
		Enqueue((ElementType)FindVertex(X, G), __Graph_CurrentYieldingGraph);
		Push((ElementType)G, __Graph_CurrentYieldingGraph);
		return BreadthFirstYield(X, NULL);
	}
}

void PushGraphYieldState()
{
	if (__Graph_CurrentYieldingGraph == NULL)
		return;
	
	if (__Graph_SavedYieldState == NULL)
		__Graph_SavedYieldState = CreateStack();
	
	List Tmp = (List)CloneList(__Graph_CurrentYieldingGraph);
	Push((ElementType)Tmp, __Graph_SavedYieldState);
}

void PopGraphYieldState()
{
	if (__Graph_SavedYieldState == NULL)
		return;
	
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
		Insert((ElementType)V, L, Last(L));
		if (V->Param)
			for (E = First((List)V->Param); E != NULL; E = Advance(E))
				Enqueue(E->Element, S);
	}
	
	DisposeQueue(&S);
	return L;
}

void SpanningForestFromGraph(Graph G, Tree *Out, size_t *Size) {}
Graph MST_Prim(Graph G) { return NULL; }
Graph MST_Kruskal(Graph G) { return NULL; }
List PathFinding_Dijkstra(Graph G) { return NULL; }
List PathFinding_Floyd(Graph G) { return NULL; }

int IsSimpleGraph(Graph G) { return 0; }
int IsDirectedGraph(Graph G) { return 0; }
int IsCyclicGraph(Graph G) { return 0; }
int IsCompleteGraph(Graph G) { return 0; }
int IsPathSimple(List L) { return 0; }
int IsPathCircuit(List L) { return 0; }

// Undirected
int IsConnectedGraph(Graph G) { return 0; }
void GetAllConnectedComponents(Graph G, Graph *Out, size_t *Size) {}

// Directed
int IsStronglyConnectedGraph(Graph G) { return 0; }
void GetAllStronglyConnectedComponents(Graph G, Graph *Out, size_t *Size) {}

int InDegree(ElementType X, Graph G)
{
	if (G == NULL || !FindVertex(X, G))
		return -1;
	
	Vertex V;
	Edge E;
	int D = 0;
	
	for (V = First(G); V != NULL; V = Advance(V))
		if (V->Param)
			for (E = First((List)V->Param); E != NULL; E = Advance(E))
				if (E->Element == X)
					D++;
	
	return D;
}

int OutDegree(ElementType X, Graph G)
{
	if (G == NULL)
		return -1;
	
	Vertex V = FindVertex(X, G);
	if (!V)
		return -1;
	
	if (!V->Param)
		return 0;
	else return Size((List)V->Param);
}
