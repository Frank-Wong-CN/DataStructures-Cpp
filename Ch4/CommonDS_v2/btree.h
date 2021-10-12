#ifndef _BTREE_H
#define _BTREE_H

#include "tnode.h"

#ifndef _TNODE_IMPL_
#error Include a tree node definition before "btree.h"!
#endif

#include "tree.h"

#include "../Ch3/CommonDS_v2/list.h"
#include "list_sort.h"

#ifndef BTREE_T
#define BTREE_T 5
#endif

#if (BTREE_T < 3)
#error B-Tree has only degree less than 3. If you so wish to use a B-Tree this small, use BST instead!
#endif

const int BTREE_T_LEAST = (int)ceil((double)(BTREE_T - 1) / 2.0);
const int BTREE_T_MOST = BTREE_T - 1;

typedef TNode *BTree;

// ADT
BTree BTreeCreateTree();
BTree BTreeCreateTreeWithList(List *L, int Len);
void BTreeAdd(ElementType X, BTree T, BTree P);
void BTreeRemoveNode(Child C, BTree T);
void BTreeRemoveValue(ElementType X, BTree T);
Child BTreeFind(ElementType X, BTree T);

#endif