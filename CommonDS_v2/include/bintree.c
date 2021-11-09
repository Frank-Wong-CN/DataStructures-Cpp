#include "bintree.h"

#include "common.h"
#include <cstring>

// -- General Binary Tree --

// TODO
Child BiPostOrderYield(BinaryTree T)
{ return NULL; }

Child BiInOrderYield(BinaryTree T)
{ return PostOrderYield((Tree)T); }

int HasLeft(BinaryTree T)
{ return HasChild(T); }

int HasRight(BinaryTree T)
{ return HasSibling(T); }

ElementType RetrieveLeft(BinaryTree T)
{ return TNodeRetrieve(FirstChild(T)); }

ElementType RetrieveRight(BinaryTree T)
{ return TNodeRetrieve(NextSibling(T)); }

int BinaryTreeDepth(BinaryTree T)
{
	if (T == NULL)
		return 0;
	
	return 1 + MaxI32(BinaryTreeDepth(FirstChild(T)), BinaryTreeDepth(NextSibling(T)));
}

Child AddLeft(ElementType X, BinaryTree T)
{
	if (T == NULL)
		return NULL;
	
	Child N, O;
	
	N = (Child)CreateTree();
	O = FirstChild(T);
	N->Element = X;
	N->FirstChild = O;
	T->FirstChild = N;
	
	return N;
}

Child AddRight(ElementType X, BinaryTree T)
{
	if (T == NULL)
		return NULL;
	
	Child N, O;
	
	N = (Child)CreateTree();
	O = NextSibling(T);
	N->Element = X;
	N->NextSibling = O;
	T->NextSibling = N;
	
	return N;
}

void RemoveLeft(BinaryTree T)
{ DeleteTree(&(T->FirstChild), T); }

void RemoveRight(BinaryTree T)
{ DeleteTree(&(T->NextSibling), T); }

// -- Binary Search Tree --

Child BSTAdd(ElementType X, BinaryTree T)
{
	if (T == NULL)
		return NULL;
	
	if (X < TNodeRetrieve(T))
	{
		if (T->FirstChild != NULL)
			return BSTAdd(X, T->FirstChild);
		else
			return AddLeft(X, T);
	}
	else
	{
		if (T->NextSibling != NULL)
			return BSTAdd(X, T->NextSibling);
		else
			return AddRight(X, T);
	}
}

Child BSTFind(ElementType X, BinaryTree T)
{
	if (T == NULL)
		return NULL;
	
	if (X < TNodeRetrieve(T))
		return BSTFind(X, T->FirstChild);
	else if (X > TNodeRetrieve(T))
		return BSTFind(X, T->NextSibling);
	return T;
}

Child BSTFindMax(BinaryTree T, ElementType *Max)
{
	while (T != NULL)
		if (T->NextSibling != NULL)
			T = T->NextSibling;
		else break;
	
	if (Max != NULL)
		*Max = TNodeRetrieve(T);
	
	return T;
}

Child BSTFindMin(BinaryTree T, ElementType *Min)
{
	while (T != NULL)
		if (T->FirstChild != NULL)
			T = T->FirstChild;
		else break;
	
	if (Min != NULL)
		*Min = TNodeRetrieve(T);
	
	return T;
}

void BSTRemoveNode(Child C, BinaryTree *T)
{
	if (C == NULL)
		return;
	
	Child Prev, Cur;
	Tree PrevPar, CurPar;
	
	// Yield so I can find its predecessor or successor
	PushYieldState();
	
	Prev = Cur = NULL;
	PrevPar = CurPar = NULL;
	Cur = PostOrderYield(*T);
	while (Cur != NULL)
	{
		PrevPar = CurPar;
		CurPar = CurrentYieldParent();
		if (Cur == C)
		{
			if (HasLeft(C) && HasRight(C))
			{
				C->Element = Prev->Element;
				C = Prev;
				*GetClosestConnection(Prev, PrevPar, *T, NULL, NULL) = NULL;
			}
			else if (HasLeft(C))
			{
				if (CurPar == NULL)
				{
					if ((CurPar = (Tree)GetClosestConnection(C, Prev, *T, NULL, NULL)) != NULL)
						*((Tree *)CurPar) = C->FirstChild;
					else
						*T = C->FirstChild; // C == T
				}
				else
					/*
					GetClosestConnection(C, CurPar, *T, &Conn, &O);
					if (Conn == NULL)
						FatalError("Impossible: In function BSTRemoveNode, Child's BST parent cannot be deferred from its general parent.");
					*((Tree *)((unsigned long long)Conn + O)) = C->FirstChild;
					*/
					*GetClosestConnection(C, CurPar, *T, NULL, NULL) = C->FirstChild;
			}
			else if (HasRight(C))
			{
				if (CurPar == NULL)
				{
					if ((CurPar = (Tree)GetClosestConnection(C, Prev, *T, NULL, NULL)) != NULL)
						*((Tree *)CurPar) = C->NextSibling;
					else
						*T = C->NextSibling; // C == T
				}
				else
					*GetClosestConnection(C, CurPar, *T, NULL, NULL) = C->NextSibling;
			}
			else
			{
				if (CurPar == NULL)
				{
					if ((CurPar = (Tree)GetClosestConnection(C, Prev, *T, NULL, NULL)) != NULL)
						*((Tree *)CurPar) = NULL;
					else
						*T = NULL; // C == T
				}
				else
					*GetClosestConnection(C, CurPar, *T, NULL, NULL) = NULL;
			}
			free(C);
			break;
		}
		Prev = Cur;
		Cur = PostOrderYield(NULL);
	}
	
	PopYieldState();
}

void BSTRemoveValue(ElementType X, BinaryTree *T)
{
	// TODO: Optimize
	BSTRemoveNode(BSTFind(X, *T), T);
}

// TODO
Tree ConvertToForest(BinaryTree T)
{ return NULL; }

// -- AVL Tree --

void __AVLRotation_LL(BinaryTree T)
{
	#ifdef __AVL_OUTPUT__
	fmt::print("AVL Imbalance, ID: {}, Type: LL\n", T->Element);
	#endif
	Child L1 = T->FirstChild;
	Child L2 = L1->FirstChild;
	Child R2 = L1->NextSibling;
	Child R1 = T->NextSibling;
	
	TNodeSwap(T, L1);
	T->FirstChild = L2;
	T->NextSibling = L1;
	L1->FirstChild = R2;
	L1->NextSibling = R1;
}

void __AVLRotation_LR(BinaryTree T)
{
	#ifdef __AVL_OUTPUT__
	fmt::print("AVL Imbalance, ID: {}, Type: LR\n", T->Element);
	#endif
	Child L1 = T->FirstChild;
	Child R2 = L1->NextSibling;
	Child L3 = R2->FirstChild;
	Child R3 = R2->NextSibling;
	Child R1 = T->NextSibling;
	
	TNodeSwap(T, R2);
	T->NextSibling = R2;
	L1->NextSibling = L3;
	R2->FirstChild = R3;
	R2->NextSibling = R1;
}

void __AVLRotation_RR(BinaryTree T)
{
	#ifdef __AVL_OUTPUT__
	fmt::print("AVL Imbalance, ID: {}, Type: RR\n", T->Element);
	#endif
	Child R1 = T->NextSibling;
	Child R2 = R1->NextSibling;
	Child L2 = R1->FirstChild;
	Child L1 = T->FirstChild;
	
	TNodeSwap(T, R1);
	T->FirstChild = R1;
	T->NextSibling = R2;
	R1->FirstChild = L1;
	R1->NextSibling = L2;
}

void __AVLRotation_RL(BinaryTree T)
{
	#ifdef __AVL_OUTPUT__
	fmt::print("AVL Imbalance, ID: {}, Type: RL\n", T->Element);
	#endif
	Child R1 = T->NextSibling;
	Child L2 = R1->FirstChild;
	Child L3 = L2->FirstChild;
	Child R3 = L2->NextSibling;
	Child L1 = T->FirstChild;
	
	TNodeSwap(T, L2);
	T->FirstChild = L2;
	L2->FirstChild = L1;
	L2->NextSibling = L3;
	R1->FirstChild = R3;
}

Child AVLAdd(ElementType X, BinaryTree T)
{
	if (T == NULL)
		return NULL;
	
	#ifdef __AVL_OUTPUT__
	fmt::print("Adding {} at {}...\n", X, T->Element);
	#endif
	
	Child C;
	
	if (X < TNodeRetrieve(T))
	{
		if (T->FirstChild != NULL)
			C = AVLAdd(X, T->FirstChild);
		else
			C = AddLeft(X, T);
	}
	else
	{
		if (T->NextSibling != NULL)
			C = AVLAdd(X, T->NextSibling);
		else
			C = AddRight(X, T);
	}
	
	if (abs(AVLBalanceFactor(T)) > 1)
		AVLBalanceNode(T);
	
	return C;
}

void AVLRemoveNode(Child X, BinaryTree *T)
{
	if (X == NULL || T == NULL || *T == NULL)
		return;	
	
	#ifdef __AVL_OUTPUT__
	fmt::print("Removing node with element: {}...\n", X->Element);
	#endif
	Child Max = NULL;
	
	if (X->Element < TNodeRetrieve(*T) && (*T)->FirstChild != NULL)
		AVLRemoveNode(X, &((*T)->FirstChild));
	else if (X->Element > TNodeRetrieve(*T) && (*T)->NextSibling != NULL)
		AVLRemoveNode(X, &((*T)->NextSibling));
	else if (X == *T)
	{
		if (HasLeft(X) && HasRight(X))
		{
			#ifdef __AVL_OUTPUT__
			fmt::print("Found element with 2 children.\n");
			#endif
			Max = BSTFindMax(X->FirstChild, NULL);
			X->Element = Max->Element;
			AVLRemoveNode(Max, &(X->FirstChild));
		}
		else if (HasLeft(X))
			*T = X->FirstChild;
		else if (HasRight(X))
			*T = X->NextSibling;
		else
			*T = NULL;
		
		#ifdef __AVL_OUTPUT__
		fmt::print("Removing element.\n");
		#endif
		if (Max == NULL)
			free(X);
	}
	else if (X->Element == TNodeRetrieve(*T))
	{
		if ((*T)->FirstChild != NULL)
			AVLRemoveNode(X, &((*T)->FirstChild));
		if ((*T)->NextSibling != NULL)
			AVLRemoveNode(X, &((*T)->NextSibling));
	}
	#ifdef __AVL_OUTPUT__
	else
		fmt::print("No such element is found.\n");
	#endif
	
	// I have to rebalance the tree from top to bottom
	//AVLArbitraryBalance(*T);
	if (abs(AVLBalanceFactor(*T)) > 1)
		AVLBalanceNode(*T);
}

void AVLRemoveValue(ElementType X, BinaryTree *T)
{
	AVLRemoveNode(BSTFind(X, *T), T);
}

int AVLBalanceFactor(BinaryTree T)
{
	if (T == NULL)
		return 0;
	return BinaryTreeDepth(FirstChild(T)) - BinaryTreeDepth(NextSibling(T));
}

void AVLBalanceNode(BinaryTree T)
{
	int BalanceType;
	int DLL, DLR, DRL, DRR;
	int BFT, BFL, BFR;
	
	BFL = BFR = 0;
	
	if (T->FirstChild == NULL)
		DLL = DLR = -1;
	else
	{
		DLL = BinaryTreeDepth(T->FirstChild->FirstChild);
		DLR = BinaryTreeDepth(T->FirstChild->NextSibling);
	}
	
	if (T->NextSibling == NULL)
		DRL = DRR = -1;
	else
	{
		DRL = BinaryTreeDepth(T->NextSibling->FirstChild);
		DRR = BinaryTreeDepth(T->NextSibling->NextSibling);
	}
	
	BFT = MaxI32(DLL, DLR) - MaxI32(DRL, DRR);
	
	if (BFT > 0)
		BFL = DLL - DLR;
	else
		BFR = DRL - DRR;
	
	BalanceType = BFT + BFL + BFR;
	
	#ifdef __AVL_OUTPUT__
	fmt::print("Balancing Node {} w/ BFS {} (T: {}, L: {}, R: {}) ...\n", T->Element, BalanceType, BFT, BFL, BFR);
	#endif
	
	switch (BalanceType)
	{
	case 3:
	case 2:
		__AVLRotation_LL(T);
		break;
	case 1:
		__AVLRotation_LR(T);
		break;
	case -3:
	case -2:
		__AVLRotation_RR(T);
		break;
	case -1:
		__AVLRotation_RL(T);
		break;
	}
}

BinaryTree AVLBalanceNext(BinaryTree T)
{
	BinaryTree ST;
	
	PushYieldState();
	for (ST = PostOrderYield(T); ST != NULL; ST = PostOrderYield(NULL))
		if (abs(AVLBalanceFactor(ST)) > 1)
			break;
	PopYieldState();
	
	return ST;
}

void AVLArbitraryBalance(BinaryTree T)
{
	Child C;
	
	while ((C = AVLBalanceNext(T)) != NULL)
		AVLBalanceNode(C);
}
