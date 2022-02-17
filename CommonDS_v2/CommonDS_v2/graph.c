#include "graph.h"

CommonDS_v2_Vertex CommonDS_v2_Graph_DepthFirstYield(CommonDS_v2_List_ElementType X, CommonDS_v2_Graph G)
{
	if (G == NULL)
	{
		if (!CommonDS_v2_Graph_CurrentYieldingGraph)
			return NULL;
		
		CommonDS_v2_Graph G;
		CommonDS_v2_Vertex V;
		CommonDS_v2_Edge E;
		
		G = (CommonDS_v2_Vertex)CommonDS_v2_Stack_Pop(CommonDS_v2_Graph_CurrentYieldingGraph);
		if (!CommonDS_v2_List_Size(CommonDS_v2_Graph_CurrentYieldingGraph))
			return NULL;
		
		V = (CommonDS_v2_Vertex)CommonDS_v2_Stack_Pop(CommonDS_v2_Graph_CurrentYieldingGraph);
		if (V->Param)
			for (E = CommonDS_v2_List_First((CommonDS_v2_List)V->Param); E != NULL; E = CommonDS_v2_List_Advance(E))
				CommonDS_v2_Stack_Push((CommonDS_v2_List_ElementType)CommonDS_v2_Graph_FindVertex(E->Element, G), CommonDS_v2_Graph_CurrentYieldingGraph);
		
		CommonDS_v2_Stack_Push((CommonDS_v2_List_ElementType)G, CommonDS_v2_Graph_CurrentYieldingGraph);
		
		return V;
	}
	else
	{
		if (CommonDS_v2_Graph_CurrentYieldingGraph)
			CommonDS_v2_Stack_Dispose(&CommonDS_v2_Graph_CurrentYieldingGraph);
		
		CommonDS_v2_Graph_CurrentYieldingGraph = CommonDS_v2_Stack_CreateStack();
		CommonDS_v2_Stack_Push((CommonDS_v2_List_ElementType)CommonDS_v2_Graph_FindVertex(X, G), CommonDS_v2_Graph_CurrentYieldingGraph);
		CommonDS_v2_Stack_Push((CommonDS_v2_List_ElementType)G, CommonDS_v2_Graph_CurrentYieldingGraph);
		return CommonDS_v2_Graph_DepthFirstYield(X, NULL);
	}
}

CommonDS_v2_Vertex CommonDS_v2_Graph_BreadthFirstYield(CommonDS_v2_List_ElementType X, CommonDS_v2_Graph G)
{
	if (G == NULL)
	{
		if (!CommonDS_v2_Graph_CurrentYieldingGraph)
			return NULL;
		
		CommonDS_v2_Graph G;
		CommonDS_v2_Vertex V;
		CommonDS_v2_Edge E;
		
		G = (CommonDS_v2_Vertex)CommonDS_v2_Stack_Pop(CommonDS_v2_Graph_CurrentYieldingGraph);
		if (!CommonDS_v2_List_Size(CommonDS_v2_Graph_CurrentYieldingGraph))
			return NULL;
		
		V = (CommonDS_v2_Vertex)CommonDS_v2_Queue_Dequeue(CommonDS_v2_Graph_CurrentYieldingGraph);
		if (V->Param)
			for (E = CommonDS_v2_List_First((CommonDS_v2_List)V->Param); E != NULL; E = CommonDS_v2_List_Advance(E))
				CommonDS_v2_Queue_Enqueue((CommonDS_v2_List_ElementType)CommonDS_v2_Graph_FindVertex(E->Element, G), CommonDS_v2_Graph_CurrentYieldingGraph);
		
		CommonDS_v2_Stack_Push((CommonDS_v2_List_ElementType)G, CommonDS_v2_Graph_CurrentYieldingGraph);
		
		return V;
	}
	else
	{
		if (CommonDS_v2_Graph_CurrentYieldingGraph)
			CommonDS_v2_Queue_Dispose(&CommonDS_v2_Graph_CurrentYieldingGraph);
		
		CommonDS_v2_Graph_CurrentYieldingGraph = CommonDS_v2_Queue_CreateQueue();
		CommonDS_v2_Queue_Enqueue((CommonDS_v2_List_ElementType)CommonDS_v2_Graph_FindVertex(X, G), CommonDS_v2_Graph_CurrentYieldingGraph);
		CommonDS_v2_Stack_Push((CommonDS_v2_List_ElementType)G, CommonDS_v2_Graph_CurrentYieldingGraph);
		return CommonDS_v2_Graph_BreadthFirstYield(X, NULL);
	}
}

void CommonDS_v2_Graph_PushYieldState()
{
	if (CommonDS_v2_Graph_CurrentYieldingGraph == NULL)
		return;
	
	if (CommonDS_v2_Graph_SavedYieldState == NULL)
		CommonDS_v2_Graph_SavedYieldState = CommonDS_v2_Stack_CreateStack();
	
	CommonDS_v2_List Tmp = (CommonDS_v2_List)CommonDS_v2_List_CloneList(CommonDS_v2_Graph_CurrentYieldingGraph);
	CommonDS_v2_Stack_Push((CommonDS_v2_List_ElementType)Tmp, CommonDS_v2_Graph_SavedYieldState);
}

void CommonDS_v2_Graph_PopYieldState()
{
	if (CommonDS_v2_Graph_SavedYieldState == NULL)
		return;
	
	CommonDS_v2_List_DeleteList(&CommonDS_v2_Graph_CurrentYieldingGraph);
	CommonDS_v2_Graph_CurrentYieldingGraph = (CommonDS_v2_Stack)CommonDS_v2_Stack_Pop(CommonDS_v2_Graph_SavedYieldState);
}

CommonDS_v2_List CommonDS_v2_Graph_DepthFirstTraverse(CommonDS_v2_List_ElementType X, CommonDS_v2_Graph G)
{
	if (G == NULL || !CommonDS_v2_Graph_FindVertex(X, G))
		return NULL;
	
	CommonDS_v2_List L = CommonDS_v2_List_CreateList();
	CommonDS_v2_Stack S = CommonDS_v2_Stack_CreateStack();
	CommonDS_v2_Vertex V;
	CommonDS_v2_Edge E;
	
	CommonDS_v2_Stack_Push(X, S);
	while (CommonDS_v2_List_Size(S) > 0)
	{
		V = CommonDS_v2_List_Find(CommonDS_v2_Stack_Pop(S), G);
		CommonDS_v2_List_Insert((CommonDS_v2_List_ElementType)V, L, CommonDS_v2_List_Last(L));
		if (V->Param)
			for (E = CommonDS_v2_List_First((CommonDS_v2_List)V->Param); E != NULL; E = CommonDS_v2_List_Advance(E))
				CommonDS_v2_Stack_Push(E->Element, S);
	}
	
	CommonDS_v2_Stack_Dispose(&S);
	return L;
}

CommonDS_v2_List CommonDS_v2_Graph_BreadthFirstTraverse(CommonDS_v2_List_ElementType X, CommonDS_v2_Graph G)
{
	if (G == NULL || !CommonDS_v2_Graph_FindVertex(X, G))
		return NULL;
	
	CommonDS_v2_List L = CommonDS_v2_List_CreateList();
	CommonDS_v2_Queue S = CommonDS_v2_Queue_CreateQueue();
	CommonDS_v2_Vertex V;
	CommonDS_v2_Edge E;
	
	CommonDS_v2_Queue_Enqueue(X, S);
	while (CommonDS_v2_List_Size(S) > 0)
	{
		V = CommonDS_v2_List_Find(CommonDS_v2_Queue_Dequeue(S), G);
		CommonDS_v2_List_Insert((CommonDS_v2_List_ElementType)V, L, CommonDS_v2_List_Last(L));
		if (V->Param)
			for (E = CommonDS_v2_List_First((CommonDS_v2_List)V->Param); E != NULL; E = CommonDS_v2_List_Advance(E))
				CommonDS_v2_Queue_Enqueue(E->Element, S);
	}
	
	CommonDS_v2_Queue_Dispose(&S);
	return L;
}

void CommonDS_v2_Graph_SpanningForestFromGraph(CommonDS_v2_Graph G, CommonDS_v2_Tree *Out, CommonDS_v2_SizeType *Size) {}
CommonDS_v2_Graph CommonDS_v2_Graph_MST_Prim(CommonDS_v2_Graph G) { return NULL; }
CommonDS_v2_Graph CommonDS_v2_Graph_MST_Kruskal(CommonDS_v2_Graph G) { return NULL; }
CommonDS_v2_List CommonDS_v2_Graph_PathFinding_Dijkstra(CommonDS_v2_Graph G) { return NULL; }
CommonDS_v2_List CommonDS_v2_Graph_PathFinding_Floyd(CommonDS_v2_Graph G) { return NULL; }

int CommonDS_v2_Graph_IsSimpleGraph(CommonDS_v2_Graph G) { return 0; }
int CommonDS_v2_Graph_IsDirectedGraph(CommonDS_v2_Graph G) { return 0; }
int CommonDS_v2_Graph_IsCyclicGraph(CommonDS_v2_Graph G) { return 0; }
int CommonDS_v2_Graph_IsCompleteGraph(CommonDS_v2_Graph G) { return 0; }
int CommonDS_v2_Graph_IsPathSimple(CommonDS_v2_List L) { return 0; }
int CommonDS_v2_Graph_IsPathCircuit(CommonDS_v2_List L) { return 0; }

// Undirected
int CommonDS_v2_Graph_IsConnectedGraph(CommonDS_v2_Graph G) { return 0; }
void CommonDS_v2_Graph_GetAllConnectedComponents(CommonDS_v2_Graph G, CommonDS_v2_Graph *Out, CommonDS_v2_SizeType *Size) {}

// Directed
int CommonDS_v2_Graph_IsStronglyConnectedGraph(CommonDS_v2_Graph G) { return 0; }
void CommonDS_v2_Graph_GetAllStronglyConnectedComponents(CommonDS_v2_Graph G, CommonDS_v2_Graph *Out, CommonDS_v2_SizeType *Size) {}
