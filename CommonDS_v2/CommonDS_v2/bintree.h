#ifndef DSV2_BINARY_TREE_H
#define DSV2_BINARY_TREE_H

#include "tnode.h"
#include "tree.h"

typedef CommonDS_v2_Tree_PNode CommonDS_v2_BinaryTree, CommonDS_v2_BSTTree, CommonDS_v2_AVLTree;

// -- General Binary Tree --

CommonDS_v2_Tree_Child CommonDS_v2_BinaryTree_PreOrderYield(CommonDS_v2_BinaryTree T);
CommonDS_v2_Tree_Child CommonDS_v2_BinaryTree_InOrderYield(CommonDS_v2_BinaryTree T);
CommonDS_v2_Tree_Child CommonDS_v2_BinaryTree_PostOrderYield(CommonDS_v2_BinaryTree T);
int CommonDS_v2_BinaryTree_HasLeft(CommonDS_v2_BinaryTree T);
int CommonDS_v2_BinaryTree_HasRight(CommonDS_v2_BinaryTree T);
CommonDS_v2_Tree_ElementType CommonDS_v2_BinaryTree_RetrieveLeft(CommonDS_v2_BinaryTree T);
CommonDS_v2_Tree_ElementType CommonDS_v2_BinaryTree_RetrieveRight(CommonDS_v2_BinaryTree T);
CommonDS_v2_SizeType CommonDS_v2_BinaryTree_Depth(CommonDS_v2_BinaryTree T);

CommonDS_v2_Tree_Child CommonDS_v2_BinaryTree_AddLeft(CommonDS_v2_Tree_ElementType X, CommonDS_v2_BinaryTree T);
CommonDS_v2_Tree_Child CommonDS_v2_BinaryTree_AddRight(CommonDS_v2_Tree_ElementType X, CommonDS_v2_BinaryTree T);
void CommonDS_v2_BinaryTree_RemoveLeft(CommonDS_v2_BinaryTree T);
void CommonDS_v2_BinaryTree_RemoveRight(CommonDS_v2_BinaryTree T);
void CommonDS_v2_BinaryTree_MakeEmpty(CommonDS_v2_BinaryTree T);
void CommonDS_v2_BinaryTree_DeleteBinTree(CommonDS_v2_BinaryTree *T);

CommonDS_v2_Tree CommonDS_v2_BinaryTree_ConvertToForest(CommonDS_v2_BinaryTree T);

// -- Binary Search Tree --

CommonDS_v2_Tree_Child CommonDS_v2_BST_Add(CommonDS_v2_Tree_ElementType X, CommonDS_v2_BinaryTree T);
CommonDS_v2_Tree_Child CommonDS_v2_BST_Find(CommonDS_v2_Tree_ElementType X, CommonDS_v2_BinaryTree T);
CommonDS_v2_Tree_Child CommonDS_v2_BST_FindMax(CommonDS_v2_BinaryTree T, CommonDS_v2_Tree_ElementType *Max);
CommonDS_v2_Tree_Child CommonDS_v2_BST_FindMin(CommonDS_v2_BinaryTree T, CommonDS_v2_Tree_ElementType *Min);
void CommonDS_v2_BST_RemoveNode(CommonDS_v2_Tree_Child C, CommonDS_v2_BinaryTree *T);
void CommonDS_v2_BST_RemoveValue(CommonDS_v2_Tree_ElementType X, CommonDS_v2_BinaryTree *T);

// -- AVL Tree --
void __CommonDS_v2_AVL_Rotation_LL(CommonDS_v2_BinaryTree T); // 011
void __CommonDS_v2_AVL_Rotation_LR(CommonDS_v2_BinaryTree T); // 001
void __CommonDS_v2_AVL_Rotation_RR(CommonDS_v2_BinaryTree T); // 111
void __CommonDS_v2_AVL_Rotation_RL(CommonDS_v2_BinaryTree T); // 101
CommonDS_v2_Tree_Child CommonDS_v2_AVL_Add(CommonDS_v2_Tree_ElementType X, CommonDS_v2_BinaryTree T);
void CommonDS_v2_AVL_RemoveNode(CommonDS_v2_Tree_Child C, CommonDS_v2_BinaryTree *T);
void CommonDS_v2_AVL_RemoveValue(CommonDS_v2_Tree_ElementType X, CommonDS_v2_BinaryTree *T);
CommonDS_v2_PointerSize_Signed CommonDS_v2_AVL_BalanceFactor(CommonDS_v2_BinaryTree T);
void CommonDS_v2_AVL_BalanceNode(CommonDS_v2_BinaryTree T);
CommonDS_v2_BinaryTree CommonDS_v2_AVL_BalanceNext(CommonDS_v2_BinaryTree T);
void CommonDS_v2_AVL_ArbitraryBalance(CommonDS_v2_BinaryTree T);

#endif