#ifndef _MNODE_IMPL_
#define _MNODE_IMPL_
#define _MNODE_IMPL_BASIC

#include "mnode.h"

struct _MultiNode
{
	MNodeElementType Element;
	MultiNode *Next[];
};

#endif