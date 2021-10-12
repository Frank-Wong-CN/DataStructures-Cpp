#ifndef _NODE_IMPL_
#define _NODE_IMPL_
#define _NODE_IMPL_POLYNOMIAL

#include "node.h"

#define ElementType int
#define Element Exponent

struct _Node
{
	ElementType Exponent;
	int Coefficient;
	Position Next;
};

#endif