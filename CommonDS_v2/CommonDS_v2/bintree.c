#include "bintree.h"
#include "common.h"

// -- General Binary Tree --

CommonDS_v2_Tree_Child CommonDS_v2_BinaryTree_PreOrderYield(CommonDS_v2_BinaryTree T)
{
	CommonDS_v2_Tree_Child C;
	
	if (T == NULL) /* Yield on existing tree */
	{
		if (CommonDS_v2_Tree_CurrentYieldingTree == NULL) /* No existing tree to yield */
			return NULL;
		else
		{
			// If yield stack is empty, the tree is completely traversed
			if (!CommonDS_v2_List_Size(CommonDS_v2_Tree_CurrentYieldingTree))
				return NULL;
			
			// Pop the first tree node in the stack, then push the right and left child of the tree node into the stack
			C = (CommonDS_v2_Tree_Child)CommonDS_v2_Stack_Pop(CommonDS_v2_Tree_CurrentYieldingTree);
			// Push right child
			if (C->NextSibling) CommonDS_v2_Stack_Push((CommonDS_v2_List_ElementType)CommonDS_v2_Tree_NextSibling((CommonDS_v2_Tree)C), CommonDS_v2_Tree_CurrentYieldingTree);
			// Push left child
			if (C->FirstChild) CommonDS_v2_Stack_Push((CommonDS_v2_List_ElementType)CommonDS_v2_Tree_FirstChild((CommonDS_v2_Tree)C), CommonDS_v2_Tree_CurrentYieldingTree);
			return C;
		}
	}
	else /* Yield new tree */
	{
		// Dispose previous yielding tree
		if (CommonDS_v2_Tree_CurrentYieldingTree != NULL)
			CommonDS_v2_Stack_Dispose(&CommonDS_v2_Tree_CurrentYieldingTree);
		
		// Initialize yield stack and return the root
		CommonDS_v2_Tree_CurrentYieldingTree = CommonDS_v2_Stack_CreateStack();
		// Push right child
		if (T->NextSibling) CommonDS_v2_Stack_Push((CommonDS_v2_List_ElementType)CommonDS_v2_Tree_NextSibling((CommonDS_v2_Tree)T), CommonDS_v2_Tree_CurrentYieldingTree);
		// Push left child
		if (T->FirstChild) CommonDS_v2_Stack_Push((CommonDS_v2_List_ElementType)CommonDS_v2_Tree_FirstChild((CommonDS_v2_Tree)T), CommonDS_v2_Tree_CurrentYieldingTree);
		return T;
	}
}

// TODO
CommonDS_v2_Tree_Child CommonDS_v2_BinaryTree_PostOrderYield(CommonDS_v2_BinaryTree T)
{ return NULL; }

CommonDS_v2_Tree_Child CommonDS_v2_BinaryTree_InOrderYield(CommonDS_v2_BinaryTree T)
{ return CommonDS_v2_Tree_PostOrderYield((CommonDS_v2_Tree)T); }

int CommonDS_v2_BinaryTree_HasLeft(CommonDS_v2_BinaryTree T)
{ return CommonDS_v2_Tree_HasChild(T); }

int CommonDS_v2_BinaryTree_HasRight(CommonDS_v2_BinaryTree T)
{ return CommonDS_v2_Tree_HasSibling(T); }

CommonDS_v2_List_ElementType CommonDS_v2_BinaryTree_RetrieveLeft(CommonDS_v2_BinaryTree T)
{ return CommonDS_v2_Tree_Retrieve(CommonDS_v2_Tree_FirstChild(T)); }

CommonDS_v2_List_ElementType CommonDS_v2_BinaryTree_RetrieveRight(CommonDS_v2_BinaryTree T)
{ return CommonDS_v2_Tree_Retrieve(CommonDS_v2_Tree_NextSibling(T)); }

CommonDS_v2_SizeType CommonDS_v2_BinaryTree_Depth(CommonDS_v2_BinaryTree T)
{
	if (T == NULL)
		return 0;
	
	return 1 + Max(CommonDS_v2_BinaryTree_Depth(CommonDS_v2_Tree_FirstChild(T)), CommonDS_v2_BinaryTree_Depth(CommonDS_v2_Tree_NextSibling(T)));
}

CommonDS_v2_Tree_Child CommonDS_v2_BinaryTree_AddLeft(CommonDS_v2_List_ElementType X, CommonDS_v2_BinaryTree T)
{
	if (T == NULL)
		return NULL;
	
	CommonDS_v2_Tree_Child N, O;
	
	N = (CommonDS_v2_Tree_Child)CommonDS_v2_Tree_CreateTree(X);
	O = CommonDS_v2_Tree_FirstChild(T);
	N->FirstChild = O;
	T->FirstChild = N;
	
	return N;
}

CommonDS_v2_Tree_Child CommonDS_v2_BinaryTree_AddRight(CommonDS_v2_List_ElementType X, CommonDS_v2_BinaryTree T)
{
	if (T == NULL)
		return NULL;
	
	CommonDS_v2_Tree_Child N, O;
	
	N = (CommonDS_v2_Tree_Child)CommonDS_v2_Tree_CreateTree(X);
	O = CommonDS_v2_Tree_NextSibling(T);
	N->NextSibling = O;
	T->NextSibling = N;
	
	return N;
}

void CommonDS_v2_BinaryTree_RemoveLeft(CommonDS_v2_BinaryTree T)
{ CommonDS_v2_BinaryTree_DeleteBinTree(&(T->FirstChild)); }

void CommonDS_v2_BinaryTree_RemoveRight(CommonDS_v2_BinaryTree T)
{ CommonDS_v2_BinaryTree_DeleteBinTree(&(T->NextSibling)); }

void CommonDS_v2_BinaryTree_MakeEmpty(CommonDS_v2_BinaryTree T)
{
	CommonDS_v2_Tree Dummy = CommonDS_v2_Tree_CreateTree(0);
	Dummy->FirstChild = T->FirstChild;
	CommonDS_v2_Tree_MakeEmpty(Dummy);
	Dummy->FirstChild = T->NextSibling;
	CommonDS_v2_Tree_MakeEmpty(Dummy);
	CommonDS_v2_Tree_DeleteTree(&Dummy, NULL);
	T->FirstChild = NULL;
	T->NextSibling = NULL;
}

void CommonDS_v2_BinaryTree_DeleteBinTree(CommonDS_v2_BinaryTree *T)
{
	CommonDS_v2_Tree Dummy = CommonDS_v2_Tree_CreateTree(0);
	Dummy->FirstChild = *T;
	CommonDS_v2_Tree_DeleteTree(&Dummy, NULL);
	*T = NULL;
}

// -- Binary Search Tree --

CommonDS_v2_Tree_Child CommonDS_v2_BST_Add(CommonDS_v2_List_ElementType X, CommonDS_v2_BinaryTree T)
{
	if (T == NULL)
		return NULL;
	
	if (X < CommonDS_v2_Tree_Retrieve(T))
	{
		if (T->FirstChild != NULL)
			return CommonDS_v2_BST_Add(X, T->FirstChild);
		else
			return CommonDS_v2_BinaryTree_AddLeft(X, T);
	}
	else
	{
		if (T->NextSibling != NULL)
			return CommonDS_v2_BST_Add(X, T->NextSibling);
		else
			return CommonDS_v2_BinaryTree_AddRight(X, T);
	}
}

CommonDS_v2_Tree_Child CommonDS_v2_BST_Find(CommonDS_v2_List_ElementType X, CommonDS_v2_BinaryTree T)
{
	if (T == NULL)
		return NULL;
	
	if (X < CommonDS_v2_Tree_Retrieve(T))
		return CommonDS_v2_BST_Find(X, T->FirstChild);
	else if (X > CommonDS_v2_Tree_Retrieve(T))
		return CommonDS_v2_BST_Find(X, T->NextSibling);
	return T;
}

CommonDS_v2_Tree_Child CommonDS_v2_BST_FindMax(CommonDS_v2_BinaryTree T, CommonDS_v2_List_ElementType *Max)
{
	while (T != NULL)
		if (T->NextSibling != NULL)
			T = T->NextSibling;
		else break;
	
	if (Max != NULL)
		*Max = CommonDS_v2_Tree_Retrieve(T);
	
	return T;
}

CommonDS_v2_Tree_Child CommonDS_v2_BST_FindMin(CommonDS_v2_BinaryTree T, CommonDS_v2_List_ElementType *Min)
{
	while (T != NULL)
		if (T->FirstChild != NULL)
			T = T->FirstChild;
		else break;
	
	if (Min != NULL)
		*Min = CommonDS_v2_Tree_Retrieve(T);
	
	return T;
}

void CommonDS_v2_BST_RemoveNode(CommonDS_v2_Tree_Child C, CommonDS_v2_BinaryTree *T)
{
	if (C == NULL)
		return;
	
	CommonDS_v2_Tree_Child Prev, Cur;
	CommonDS_v2_Tree PrevPar, CurPar;
	
	// Yield so I can find its predecessor or successor
	CommonDS_v2_Tree_PushYieldState();
	
	Prev = Cur = NULL;
	PrevPar = CurPar = NULL;
	Cur = CommonDS_v2_Tree_PostOrderYield(*T);
	while (Cur != NULL)
	{
		PrevPar = CurPar;
		CurPar = CommonDS_v2_Tree_CurrentYieldParent();
		if (Cur == C)
		{
			if (CommonDS_v2_BinaryTree_HasLeft(C) && CommonDS_v2_BinaryTree_HasRight(C))
			{
				C->Element = Prev->Element;
				C = Prev;
				*CommonDS_v2_Tree_GetClosestConnection(Prev, PrevPar, *T, NULL, NULL) = NULL;
			}
			else if (CommonDS_v2_BinaryTree_HasLeft(C))
			{
				if (CurPar == NULL)
				{
					if ((CurPar = (CommonDS_v2_Tree)CommonDS_v2_Tree_GetClosestConnection(C, Prev, *T, NULL, NULL)) != NULL)
						*((CommonDS_v2_Tree *)CurPar) = C->FirstChild;
					else
						*T = C->FirstChild; // C == T
				}
				else
					/*
					CommonDS_v2_Tree_GetClosestConnection(C, CurPar, *T, &Conn, &O);
					if (Conn == NULL)
						FatalError("Impossible: In function CommonDS_v2_BST_RemoveNode, Child's BST parent cannot be deferred from its general parent.");
					*((CommonDS_v2_Tree *)((unsigned long long)Conn + O)) = C->FirstChild;
					*/
					*CommonDS_v2_Tree_GetClosestConnection(C, CurPar, *T, NULL, NULL) = C->FirstChild;
			}
			else if (CommonDS_v2_BinaryTree_HasRight(C))
			{
				if (CurPar == NULL)
				{
					if ((CurPar = (CommonDS_v2_Tree)CommonDS_v2_Tree_GetClosestConnection(C, Prev, *T, NULL, NULL)) != NULL)
						*((CommonDS_v2_Tree *)CurPar) = C->NextSibling;
					else
						*T = C->NextSibling; // C == T
				}
				else
					*CommonDS_v2_Tree_GetClosestConnection(C, CurPar, *T, NULL, NULL) = C->NextSibling;
			}
			else
			{
				if (CurPar == NULL)
				{
					if ((CurPar = (CommonDS_v2_Tree)CommonDS_v2_Tree_GetClosestConnection(C, Prev, *T, NULL, NULL)) != NULL)
						*((CommonDS_v2_Tree *)CurPar) = NULL;
					else
						*T = NULL; // C == T
				}
				else
					*CommonDS_v2_Tree_GetClosestConnection(C, CurPar, *T, NULL, NULL) = NULL;
			}
			free(C);
			break;
		}
		Prev = Cur;
		Cur = CommonDS_v2_Tree_PostOrderYield(NULL);
	}
	
	CommonDS_v2_Tree_PopYieldState();
}

void CommonDS_v2_BST_RemoveValue(CommonDS_v2_List_ElementType X, CommonDS_v2_BinaryTree *T)
{
	// TODO: Optimize
	CommonDS_v2_BST_RemoveNode(CommonDS_v2_BST_Find(X, *T), T);
}

// TODO
CommonDS_v2_Tree CommonDS_v2_BinaryTree_ConvertToForest(CommonDS_v2_BinaryTree T)
{ return NULL; }

// -- AVL Tree --

void __CommonDS_v2_AVL_Rotation_LL(CommonDS_v2_BinaryTree T)
{
	CommonDS_v2_Tree_Child L1 = T->FirstChild;
	CommonDS_v2_Tree_Child L2 = L1->FirstChild;
	CommonDS_v2_Tree_Child R2 = L1->NextSibling;
	CommonDS_v2_Tree_Child R1 = T->NextSibling;
	
	CommonDS_v2_Tree_Swap(T, L1);
	T->FirstChild = L2;
	T->NextSibling = L1;
	L1->FirstChild = R2;
	L1->NextSibling = R1;
}

void __CommonDS_v2_AVL_Rotation_LR(CommonDS_v2_BinaryTree T)
{
	CommonDS_v2_Tree_Child L1 = T->FirstChild;
	CommonDS_v2_Tree_Child R2 = L1->NextSibling;
	CommonDS_v2_Tree_Child L3 = R2->FirstChild;
	CommonDS_v2_Tree_Child R3 = R2->NextSibling;
	CommonDS_v2_Tree_Child R1 = T->NextSibling;
	
	CommonDS_v2_Tree_Swap(T, R2);
	T->NextSibling = R2;
	L1->NextSibling = L3;
	R2->FirstChild = R3;
	R2->NextSibling = R1;
}

void __CommonDS_v2_AVL_Rotation_RR(CommonDS_v2_BinaryTree T)
{
	CommonDS_v2_Tree_Child R1 = T->NextSibling;
	CommonDS_v2_Tree_Child R2 = R1->NextSibling;
	CommonDS_v2_Tree_Child L2 = R1->FirstChild;
	CommonDS_v2_Tree_Child L1 = T->FirstChild;
	
	CommonDS_v2_Tree_Swap(T, R1);
	T->FirstChild = R1;
	T->NextSibling = R2;
	R1->FirstChild = L1;
	R1->NextSibling = L2;
}

void __CommonDS_v2_AVL_Rotation_RL(CommonDS_v2_BinaryTree T)
{
	CommonDS_v2_Tree_Child R1 = T->NextSibling;
	CommonDS_v2_Tree_Child L2 = R1->FirstChild;
	CommonDS_v2_Tree_Child L3 = L2->FirstChild;
	CommonDS_v2_Tree_Child R3 = L2->NextSibling;
	CommonDS_v2_Tree_Child L1 = T->FirstChild;
	
	CommonDS_v2_Tree_Swap(T, L2);
	T->FirstChild = L2;
	L2->FirstChild = L1;
	L2->NextSibling = L3;
	R1->FirstChild = R3;
}

CommonDS_v2_Tree_Child CommonDS_v2_AVL_Add(CommonDS_v2_List_ElementType X, CommonDS_v2_BinaryTree T)
{
	if (T == NULL)
		return NULL;
	
	CommonDS_v2_Tree_Child C;
	
	if (X < CommonDS_v2_Tree_Retrieve(T))
	{
		if (T->FirstChild != NULL)
			C = CommonDS_v2_AVL_Add(X, T->FirstChild);
		else
			C = CommonDS_v2_BinaryTree_AddLeft(X, T);
	}
	else
	{
		if (T->NextSibling != NULL)
			C = CommonDS_v2_AVL_Add(X, T->NextSibling);
		else
			C = CommonDS_v2_BinaryTree_AddRight(X, T);
	}
	
	if (Abs(CommonDS_v2_AVL_BalanceFactor(T)) > 1)
		CommonDS_v2_AVL_BalanceNode(T);
	
	return C;
}

void CommonDS_v2_AVL_RemoveNode(CommonDS_v2_Tree_Child X, CommonDS_v2_BinaryTree *T)
{
	if (X == NULL || T == NULL || *T == NULL)
		return;	
	
	CommonDS_v2_Tree_Child Max = NULL;
	
	if (X->Element < CommonDS_v2_Tree_Retrieve(*T) && (*T)->FirstChild != NULL)
		CommonDS_v2_AVL_RemoveNode(X, &((*T)->FirstChild));
	else if (X->Element > CommonDS_v2_Tree_Retrieve(*T) && (*T)->NextSibling != NULL)
		CommonDS_v2_AVL_RemoveNode(X, &((*T)->NextSibling));
	else if (X == *T)
	{
		if (CommonDS_v2_BinaryTree_HasLeft(X) && CommonDS_v2_BinaryTree_HasRight(X))
		{
			Max = CommonDS_v2_BST_FindMax(X->FirstChild, NULL);
			X->Element = Max->Element;
			CommonDS_v2_AVL_RemoveNode(Max, &(X->FirstChild));
		}
		else if (CommonDS_v2_BinaryTree_HasLeft(X))
			*T = X->FirstChild;
		else if (CommonDS_v2_BinaryTree_HasRight(X))
			*T = X->NextSibling;
		else
			*T = NULL;
		
		if (Max == NULL)
			free(X);
	}
	else if (X->Element == CommonDS_v2_Tree_Retrieve(*T))
	{
		if ((*T)->FirstChild != NULL)
			CommonDS_v2_AVL_RemoveNode(X, &((*T)->FirstChild));
		if ((*T)->NextSibling != NULL)
			CommonDS_v2_AVL_RemoveNode(X, &((*T)->NextSibling));
	}
	
	if (Abs(CommonDS_v2_AVL_BalanceFactor(*T)) > 1)
		CommonDS_v2_AVL_BalanceNode(*T);
}

void CommonDS_v2_AVL_RemoveValue(CommonDS_v2_List_ElementType X, CommonDS_v2_BinaryTree *T)
{
	CommonDS_v2_AVL_RemoveNode(CommonDS_v2_BST_Find(X, *T), T);
}

CommonDS_v2_PointerSize_Signed CommonDS_v2_AVL_BalanceFactor(CommonDS_v2_BinaryTree T)
{
	if (T == NULL)
		return 0;
	return CommonDS_v2_BinaryTree_Depth(CommonDS_v2_Tree_FirstChild(T)) - CommonDS_v2_BinaryTree_Depth(CommonDS_v2_Tree_NextSibling(T));
}

void CommonDS_v2_AVL_BalanceNode(CommonDS_v2_BinaryTree T)
{
	CommonDS_v2_PointerSize_Signed BalanceType;
	CommonDS_v2_PointerSize_Signed DLL, DLR, DRL, DRR;
	CommonDS_v2_PointerSize_Signed BFT, BFL, BFR;
	
	BFL = BFR = 0;
	
	if (T->FirstChild == NULL)
		DLL = DLR = -1;
	else
	{
		DLL = CommonDS_v2_BinaryTree_Depth(T->FirstChild->FirstChild);
		DLR = CommonDS_v2_BinaryTree_Depth(T->FirstChild->NextSibling);
	}
	
	if (T->NextSibling == NULL)
		DRL = DRR = -1;
	else
	{
		DRL = CommonDS_v2_BinaryTree_Depth(T->NextSibling->FirstChild);
		DRR = CommonDS_v2_BinaryTree_Depth(T->NextSibling->NextSibling);
	}
	
	BFT = Max(DLL, DLR) - Max(DRL, DRR);
	
	if (BFT > 0)
		BFL = DLL - DLR;
	else
		BFR = DRL - DRR;
	
	BalanceType = BFT + BFL + BFR;
	
	switch (BalanceType)
	{
	case 3:
	case 2:
		__CommonDS_v2_AVL_Rotation_LL(T);
		break;
	case 1:
		__CommonDS_v2_AVL_Rotation_LR(T);
		break;
	case -3:
	case -2:
		__CommonDS_v2_AVL_Rotation_RR(T);
		break;
	case -1:
		__CommonDS_v2_AVL_Rotation_RL(T);
		break;
	}
}

CommonDS_v2_BinaryTree CommonDS_v2_AVL_BalanceNext(CommonDS_v2_BinaryTree T)
{
	CommonDS_v2_BinaryTree ST;
	
	CommonDS_v2_Tree_PushYieldState();
	for (ST = CommonDS_v2_Tree_PostOrderYield(T); ST != NULL; ST = CommonDS_v2_Tree_PostOrderYield(NULL))
		if (Abs(CommonDS_v2_AVL_BalanceFactor(ST)) > 1)
			break;
	CommonDS_v2_Tree_PopYieldState();
	
	return ST;
}

void CommonDS_v2_AVL_ArbitraryBalance(CommonDS_v2_BinaryTree T)
{
	CommonDS_v2_Tree_Child C;
	
	while ((C = CommonDS_v2_AVL_BalanceNext(T)) != NULL)
		CommonDS_v2_AVL_BalanceNode(C);
}
