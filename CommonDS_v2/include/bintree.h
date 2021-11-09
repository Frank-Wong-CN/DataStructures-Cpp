#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

#include "tnode.h"

#ifndef _TNODE_IMPL_
#include "tnode_impl_basic.h"
#warning Tree node definition not found, basic implementation included.
#endif

#include "tree.h"

typedef PTNode BinaryTree, BSTTree, AVLTree;

// -- General Binary Tree --

Child BiInOrderYield(BinaryTree T);
Child BiPostOrderYield(BinaryTree T);
int HasLeft(BinaryTree T);
int HasRight(BinaryTree T);
ElementType RetrieveLeft(BinaryTree T);
ElementType RetrieveRight(BinaryTree T);
int BinaryTreeDepth(BinaryTree T);

Child AddLeft(ElementType X, BinaryTree T);
Child AddRight(ElementType X, BinaryTree T);
void RemoveLeft(BinaryTree T);
void RemoveRight(BinaryTree T);

Tree ConvertToForest(BinaryTree T);

// -- Binary Search Tree --

Child BSTAdd(ElementType X, BinaryTree T);
Child BSTFind(ElementType X, BinaryTree T);
Child BSTFindMax(BinaryTree T, ElementType *Max);
Child BSTFindMin(BinaryTree T, ElementType *Min);
void BSTRemoveNode(Child C, BinaryTree *T);
void BSTRemoveValue(ElementType X, BinaryTree *T);

// -- AVL Tree --
void __AVLRotation_LL(BinaryTree T); // 011
void __AVLRotation_LR(BinaryTree T); // 001
void __AVLRotation_RR(BinaryTree T); // 111
void __AVLRotation_RL(BinaryTree T); // 101
Child AVLAdd(ElementType X, BinaryTree T);
void AVLRemoveNode(Child C, BinaryTree *T);
void AVLRemoveValue(Child C, BinaryTree *T);
int AVLBalanceFactor(BinaryTree T);
void AVLBalanceNode(BinaryTree T);
BinaryTree AVLBalanceNext(BinaryTree T);
void AVLArbitraryBalance(BinaryTree T);

#endif