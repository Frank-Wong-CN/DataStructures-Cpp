#ifndef DSV2_NODE_IMPL_
#define DSV2_NODE_IMPL_
#define DSV2_NODE_IMPL_BASIC

#include "node.h"
#include "common.h"

#ifndef CommonDS_v2_List_ElementType
#define CommonDS_v2_List_ElementType CommonDS_v2_PointerSize
#endif

struct CommonDS_v2_List__Node
{
	CommonDS_v2_List_ElementType Element;
	CommonDS_v2_List_Position Next;
};

#endif