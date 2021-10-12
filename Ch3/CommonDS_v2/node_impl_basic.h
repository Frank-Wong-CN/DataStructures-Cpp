#ifndef _NODE_IMPL_
#define _NODE_IMPL_
#define _NODE_IMPL_BASIC

#include "node.h"

#ifndef ElementType
#define ElementType void *
#endif

struct _Node
{
	ElementType Element;
	Position Next;
};

#endif