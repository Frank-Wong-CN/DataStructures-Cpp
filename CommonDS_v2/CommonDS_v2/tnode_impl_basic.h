#ifndef DSV2_TNODE_IMPL_
#define DSV2_TNODE_IMPL_
#define DSV2_TNODE_IMPL_CHILD_SIBLING

#include "tnode.h"
#include "common.h"

#ifndef CommonDS_v2_Tree_ElementType
#define CommonDS_v2_Tree_ElementType CommonDS_v2_PointerSize
#endif

#define CommonDS_v2_Tree_ExtraDataType CommonDS_v2_PointerSize

struct CommonDS_v2_Tree__Node
{
	CommonDS_v2_Tree_ElementType Element;
	CommonDS_v2_Tree_ExtraDataType Param;
	CommonDS_v2_Tree_ExtraDataType Data;
	CommonDS_v2_Tree_Child FirstChild;
	CommonDS_v2_Tree_Sibling NextSibling;
};

#endif