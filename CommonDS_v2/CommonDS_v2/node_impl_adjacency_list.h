#ifndef DSV2_NODE_IMPL_
#define DSV2_NODE_IMPL_
#define DSV2_NODE_IMPL_ADJACENCY_LIST

#include "node.h"
#include "common.h"

#ifndef CommonDS_v2_List_ElementType
#define CommonDS_v2_List_ElementType CommonDS_v2_PointerSize
#endif

#define CommonDS_v2_AdjacencyList_ExtraDataType CommonDS_v2_PointerSize
#define CommonDS_v2_AdjacencyList_WeightType CommonDS_v2_PointerSize_Signed

struct CommonDS_v2_List__Node
{
	CommonDS_v2_List_ElementType Element;
	CommonDS_v2_AdjacencyList_ExtraDataType Param;
	CommonDS_v2_AdjacencyList_ExtraDataType Data;
	CommonDS_v2_List_Position Next;
};

#endif