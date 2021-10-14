#ifndef _CNODE_IMPL_
#define _CNODE_IMPL_
#define _CNODE_IMPL_BASIC

#ifndef ElementType
#define ElementType void *
#endif

#include "cnode.h"

struct _CNode
{
	ElementType Element;
	PCNode Next;
	PCNode *Cross;
};

#endif