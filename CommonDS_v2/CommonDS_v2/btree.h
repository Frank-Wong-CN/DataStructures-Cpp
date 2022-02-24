#ifndef DSV2_BTREE_H
#define DSV2_BTREE_H

#include "tnode.h"
#include "tree.h"

#include "list.h"
#include "list_sort.h"

#ifndef DSV2_BTREE_T
#define DSV2_BTREE_T 5
#endif

#if (DSV2_BTREE_T < 3)
#error B-Tree has only degree more than 2. If you so wish to use a B-Tree this small, use BST instead!
#endif

#include <math.h> // ceil

#ifndef _MSC_VER
const CommonDS_v2_SizeType DSV2_BTREE_T_LEAST = (CommonDS_v2_SizeType)ceil((double)(DSV2_BTREE_T - 1) / 2.0);
const CommonDS_v2_SizeType DSV2_BTREE_T_MOST = DSV2_BTREE_T - 1;
#else
#define DSV2_BTREE_T_LEAST ((CommonDS_v2_SizeType)ceil((double)(DSV2_BTREE_T - 1) / 2.0))
#define DSV2_BTREE_T_MOST = (DSV2_BTREE_T - 1)
#endif

typedef CommonDS_v2_Tree_PNode CommonDS_v2_BTree;

// ADT
CommonDS_v2_BTree CommonDS_v2_BTree_CreateTree();
CommonDS_v2_BTree CommonDS_v2_BTree_CreateTreeFromList(CommonDS_v2_List *L, CommonDS_v2_SizeType Len);
void CommonDS_v2_BTree_Add(CommonDS_v2_Tree_ElementType X, CommonDS_v2_BTree T);
void CommonDS_v2_BTree_RemoveNode(CommonDS_v2_Tree_Child C, CommonDS_v2_BTree T);
void CommonDS_v2_BTree_RemoveValue(CommonDS_v2_Tree_ElementType X, CommonDS_v2_BTree T);
CommonDS_v2_Tree_Child CommonDS_v2_BTree_Find(CommonDS_v2_Tree_ElementType X, CommonDS_v2_BTree T);

#endif