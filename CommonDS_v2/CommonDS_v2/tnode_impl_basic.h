#ifndef DSV2_TNODE_IMPL_
#define DSV2_TNODE_IMPL_
#define DSV2_TNODE_IMPL_CHILD_SIBLING

#include "tnode.h"
#include "common.h"

#ifndef CommonDS_v2_List_ElementType
#define CommonDS_v2_List_ElementType CommonDS_v2_PointerSize
#endif

struct CommonDS_v2_Tree__Node
{
	CommonDS_v2_List_ElementType Element;
	CommonDS_v2_Tree_Child FirstChild;
	CommonDS_v2_Tree_Sibling NextSibling;
};

#endif