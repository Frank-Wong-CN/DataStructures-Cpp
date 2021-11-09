#ifndef _NODE_IMPL_
#define _NODE_IMPL_
#define _NODE_IMPL_ADJACENCY_LIST

#include "node.h"

#ifndef ElementType
#define ElementType unsigned long long
#endif

#define ExtraDataSize unsigned long long
#define WeightType long long

struct _Node
{
	ElementType Element;
	ExtraDataSize Param;
	ExtraDataSize Data;
	Position Next;
};

#endif