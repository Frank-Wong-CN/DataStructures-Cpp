#ifndef DSV2_TREE_H
#define DSV2_TREE_H

#include "tnode.h"

#ifndef DSV2_TNODE_IMPL_
#include "tnode_impl_basic.h"
#ifndef _MSC_VER
#warning Tree node definition not found, basic implementation included.
#endif
#endif

#ifndef CommonDS_v2_Tree_PayloadType
#define CommonDS_v2_Tree_PayloadType CommonDS_v2_PointerSize
#endif

#include "stack.h"
#include "queue.h"

CommonDS_v2_Stack CommonDS_v2_Tree_CurrentYieldingTree = NULL;
CommonDS_v2_Stack CommonDS_v2_Tree_SavedYieldState = NULL;

CommonDS_v2_Tree CommonDS_v2_Tree_CreateTree(CommonDS_v2_List_ElementType IV);
int CommonDS_v2_Tree_HasChild(CommonDS_v2_Tree T);
int CommonDS_v2_Tree_HasSibling(CommonDS_v2_Tree T);
int CommonDS_v2_Tree_IsChild(CommonDS_v2_Tree T, CommonDS_v2_Tree_Child C);
int CommonDS_v2_Tree_IsSibling(CommonDS_v2_Tree_Sibling A, CommonDS_v2_Tree_Sibling B);
int CommonDS_v2_Tree_IsProperAncestor(CommonDS_v2_Tree Ancestor, CommonDS_v2_Tree Descendant);
int CommonDS_v2_Tree_IsProperDescendant(CommonDS_v2_Tree Descendant, CommonDS_v2_Tree Ancestor);
int CommonDS_v2_Tree_IsInSameTree(CommonDS_v2_Tree A, CommonDS_v2_Tree B);
CommonDS_v2_Tree_Child CommonDS_v2_Tree_PreOrderYield(CommonDS_v2_Tree T);
CommonDS_v2_Tree_Child CommonDS_v2_Tree_PostOrderYield(CommonDS_v2_Tree T);
CommonDS_v2_Tree_Child CommonDS_v2_Tree_BottomUpLevelYield(CommonDS_v2_Tree T);
CommonDS_v2_Tree_Child CommonDS_v2_Tree_TopDownLevelYield(CommonDS_v2_Tree T);
CommonDS_v2_Tree CommonDS_v2_Tree_CurrentYieldParent();
void CommonDS_v2_Tree_PushYieldState();
void CommonDS_v2_Tree_PopYieldState();
void CommonDS_v2_Tree_Traverse(CommonDS_v2_Tree T, CommonDS_v2_Tree_Child (*Yielder)(CommonDS_v2_Tree T), int (*F)(CommonDS_v2_Tree_Child CurNode, CommonDS_v2_Tree_Sibling PrevNode, CommonDS_v2_Tree Parent, CommonDS_v2_Tree_PayloadType Data), CommonDS_v2_Tree_PayloadType D);
CommonDS_v2_Tree *CommonDS_v2_Tree_GetClosestConnection(CommonDS_v2_Tree_Child C, CommonDS_v2_Tree T, CommonDS_v2_Tree R, CommonDS_v2_Tree *P, unsigned long long *Offset);
CommonDS_v2_Tree_Child CommonDS_v2_Tree_FirstChild(CommonDS_v2_Tree T);
CommonDS_v2_Tree_Sibling CommonDS_v2_Tree_NextSibling(CommonDS_v2_Tree_Sibling S);
CommonDS_v2_List_ElementType CommonDS_v2_Tree_Retrieve(CommonDS_v2_Tree_PNode N);

void CommonDS_v2_Tree_Delete(CommonDS_v2_List_ElementType X, CommonDS_v2_Tree T, CommonDS_v2_Tree_Child (*Yielder)(CommonDS_v2_Tree T), int DeleteSubTreeAsWell);
CommonDS_v2_Tree_Child CommonDS_v2_Tree_AddChild(CommonDS_v2_List_ElementType X, CommonDS_v2_Tree T);
CommonDS_v2_Tree_Sibling CommonDS_v2_Tree_AddSibling(CommonDS_v2_List_ElementType X, CommonDS_v2_Tree T);
void CommonDS_v2_Tree_AppendTree(CommonDS_v2_Tree Sub, CommonDS_v2_Tree Dst);
void CommonDS_v2_Tree_DeleteTree(CommonDS_v2_Tree *T, CommonDS_v2_Tree P);
void CommonDS_v2_Tree_MakeEmpty(CommonDS_v2_Tree T);
void CommonDS_v2_Tree_Swap(CommonDS_v2_Tree_PNode A, CommonDS_v2_Tree_PNode B);

#endif
