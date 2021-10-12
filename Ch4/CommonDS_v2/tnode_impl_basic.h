#ifndef _TNODE_IMPL_
#define _TNODE_IMPL_
#define _TNODE_IMPL_CHILD_SIBLING

#include "tnode.h"

#ifndef ElementType
#define ElementType void *
#endif

struct _TNode
{
	ElementType Element;
	Child FirstChild;
	Sibling NextSibling;
};

#endif