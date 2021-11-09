#ifndef _GRAPH_DS_INTERFACE_H
#define _GRAPH_DS_INTERFACE_H

#ifndef ElementType
#define ExtraDataSize void *
#endif

#ifndef WeightType
#define WeightType int
#endif

Graph CreateGraph();
void AddVertex(ElementType X, Graph G);
void RemoveVertex(ElementType X, Graph G);
Vertex FindVertex(ElementType X, Graph G);
int CountVertex(Graph G);

void Connect(ElementType X1, ElementType X2, WeightType N, Graph G, int Directed);
void DisconnectVertex(ElementType X1, ElementType X2, Graph G, int Directed);
Edge FindEdge(ElementType X1, ElementType X2, Graph G);
int CountEdge(Graph G);

void AttachDataToVertex(ExtraDataSize Data, ElementType V, Graph G);
void AttachDataToEdge(ExtraDataSize Data, ElementType X1, ElementType X2, Graph G, int Directed);

void DestroyGraph(Graph *G);

#endif