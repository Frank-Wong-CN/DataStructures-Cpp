#ifndef _NODE_IMPL_
#define _NODE_IMPL_
#define _NODE_IMPL_ADJACENCY_LIST

#include "../Ch3/CommonDS_v2/node.h"

#ifndef ElementType
#define ElementType void *
#endif

#define ExtraDataSize unsigned long long
#define WeightType unsigned long long

struct _Node
{
	ElementType Element;
	ExtraDataSize Param;
	ExtraDataSize Data;
	Position Next;
};

#endif