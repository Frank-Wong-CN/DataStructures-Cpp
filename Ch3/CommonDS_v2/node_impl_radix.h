#ifndef _NODE_IMPL_
#define _NODE_IMPL_
#define _NODE_IMPL_RADIX

#include "node.h"

#define ElementType int
#define Element Index

struct _Node
{
	ElementType Index;
	List Numbers;
	Position Next;
};

#endif