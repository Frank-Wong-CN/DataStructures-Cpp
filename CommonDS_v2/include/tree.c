#include "tree.h"

#include "common.h"
#include <cstring>
#include <cstddef> // For offsetof

int __Walker_Deleter(Child CurNode, Sibling PrevNode, Tree Parent, Payload Data)
{
	if (Parent == NULL)
		return 0;
	
	if (PrevNode != NULL)
		free(PrevNode);
	
	return 1;
}

Tree CreateTree()
{
	Tree T;
	
	T = (Tree)malloc(sizeof(TNode));
	memset(T, 0, sizeof(TNode));
	
	return T;
}

int HasChild(Tree T)
{
	return T->FirstChild != NULL;
}

int HasSibling(Tree T)
{
	return T->NextSibling != NULL;
}

int IsChild(Tree T, Child C)
{
	return T->FirstChild == C;
}

int IsSibling(Sibling A, Sibling B)
{
	if (A == NULL || B == NULL)
		return 0;
	
	Sibling C;
	
	C = A;
	while (C != NULL)
	{
		C = C->NextSibling;
		if (C == B)
			return 1;
	}
	
	C = B;
	while (C != NULL)
	{
		C = C->NextSibling;
		if (C == A)
			return 1;
	}
	
	return 0;
}

int IsProperAncestor(Tree Ancestor, Tree Descendant)
{
	if (Ancestor == NULL || Descendant == NULL)
		return 0;
	
	Child C;
	
	PushYieldState();
	for (C = PreOrderYield(Ancestor); C != NULL; C = PreOrderYield(NULL))
		if (C == Descendant)
		{
			PopYieldState();
			return 1;
		}
	
	PopYieldState();
	return 0;
}

int IsProperDescendant(Tree Descendant, Tree Ancestor)
{
	return IsProperAncestor(Ancestor, Descendant);
}

int IsInSameTree(Tree A, Tree B)
{
	if (A == B && A != NULL)
		return 1;
	
	return IsProperAncestor(A, B) || IsProperDescendant(A, B);
}

Child PreOrderYield(Tree T)
{
	Child C;
	
	if (T == NULL) /* Yield on existing tree */
	{
		if (__CurrentYieldingTree == NULL) /* No existing tree to yield */
			return NULL;
		else
		{
			// Preorder yield: children first
			C = FirstChild((Tree)Top(__CurrentYieldingTree));
			if (C != NULL) /* If has child, then yield child */
			{
				Push((ElementType)C, __CurrentYieldingTree);
				return C;
			}
			else /* If leaf node, then yield next sibling */
			{
				// Try to iterate a valid sibling
				while (C == NULL && !IsEmpty(__CurrentYieldingTree))
				{
					C = (Child)Pop(__CurrentYieldingTree);
					C = NextSibling((Sibling)C);
				}
				
				if (C != NULL) /* A valid sibling is found */
				{
					Push((ElementType)C, __CurrentYieldingTree);
					return C;
				}
				else /* If no such sibling is found, then the tree is completely traversed */
				{
					DisposeStack(&__CurrentYieldingTree);
					return NULL;
				}
			}
		}
	}
	else /* Yield new tree */
	{
		// Dispose previous yielding tree
		if (__CurrentYieldingTree != NULL)
			DisposeStack(&__CurrentYieldingTree);
		
		// Initialize yield stack and return the root
		__CurrentYieldingTree = CreateStack();
		Push((ElementType)T, __CurrentYieldingTree);
		return T;
	}
}

Child PostOrderYield(Tree T)
{
	Child C;
	
	if (T == NULL)
	{
		if (__CurrentYieldingTree == NULL) /* No existing tree to yield */
			return NULL;
		
		// Postorder yield: siblings first
		C = (Child)Pop(__CurrentYieldingTree);
		C = C->NextSibling;
		if (C == NULL) /* Subtree traversed completely */
		{
			if (IsEmpty(__CurrentYieldingTree)) /* Entire tree is completely traversed */
			{
				DisposeStack(&__CurrentYieldingTree);
				return NULL;
			}
			else
				C = (Child)Top(__CurrentYieldingTree);
		}
		else /* More children to traverse */
		{
			// Search for the next leaf
			Push((ElementType)C, __CurrentYieldingTree);
			while (C->FirstChild != NULL)
			{
				C = C->FirstChild;
				Push((ElementType)C, __CurrentYieldingTree);
			}
		}
		return C;
	}
	else /* Yield new tree */
	{
		// Dispose previous yielding tree
		if (__CurrentYieldingTree != NULL)
			DisposeStack(&__CurrentYieldingTree);
		
		// Initialize yield stack and return the first leaf
		__CurrentYieldingTree = CreateStack();
		Push((ElementType)T, __CurrentYieldingTree);
		C = T;
		while (C->FirstChild != NULL)
		{
			C = C->FirstChild;
			Push((ElementType)C, __CurrentYieldingTree);
		}
		return C;
	}
}

// TODO
Child BottomUpLevelYield(Tree T)
{ return NULL; }

// TODO
Child TopDownLevelYield(Tree T)
{ return NULL; }

void PushYieldState()
{
	if (__CurrentYieldingTree == NULL)
		return;
	
	if (__SavedYieldState == NULL)
		__SavedYieldState = CreateStack();
	
	Stack Tmp = (Stack)CloneList(__CurrentYieldingTree);
	Push((ElementType)Tmp, __SavedYieldState);
}

void PopYieldState()
{
	if (__SavedYieldState == NULL)
		return;
	
	DisposeStack(&__CurrentYieldingTree);
	__CurrentYieldingTree = (Stack)Pop(__SavedYieldState);
}

void Traverse(Tree T, Child (*Yield)(Tree T), int (*F)(Child CurNode, Sibling PrevNode, Tree Parent, Payload Data), Payload D)
{
	PushYieldState();
	
	Tree Cur, Prev, Par;
	
	for (Prev = NULL, Cur = (Tree)Yield(T); Cur != NULL; Prev = Cur, Cur = (Tree)Yield(NULL))
	{
		Par = CurrentYieldParent();
		if (!F(Cur, Prev, Par, D))
			break;
	}
	
	PopYieldState();
}

Tree *GetClosestConnection(Child C, Tree T, Tree R, Tree *P, unsigned long long *Offset)
{
	Tree Tmp;
	if (T == NULL)
		Tmp = R;
	else
		Tmp = T;
	
	if (Tmp == NULL)
		return NULL;
	
	while (Tmp->NextSibling != NULL && Tmp->NextSibling != C)
		Tmp = Tmp->NextSibling;
	
	if (Tmp->NextSibling == C)
	{
		if (P != NULL)
			*P = Tmp;
		if (Offset != NULL)
			*Offset = offsetof(TNode, NextSibling);
		
		return (Tree *)&(Tmp->NextSibling);
	}

	if (T == NULL)
		Tmp = R;
	else
		Tmp = T;
	
	if (Tmp->FirstChild != NULL)
	if (Tmp->FirstChild == C)
	{
		if (P != NULL)
			*P = Tmp;
		if (Offset != NULL)
			*Offset = offsetof(TNode, FirstChild);
		
		return (Tree *)&(Tmp->FirstChild);
	}
	else
	{
		Tmp = Tmp->FirstChild;
		while (Tmp->NextSibling != NULL && Tmp->NextSibling != C)
			Tmp = Tmp->NextSibling;
		
		if (Tmp->NextSibling == C)
		{
			if (P != NULL)
				*P = Tmp;
			if (Offset != NULL)
				*Offset = offsetof(TNode, NextSibling);
			
			return (Tree *)&(Tmp->NextSibling);
		}
		else
		{
			if (P != NULL)
				*P = NULL;
			if (Offset != NULL)
				*Offset = -1;
			
			return NULL;
		}
	}
	
	if (P != NULL)
		*P = NULL;
	if (Offset != NULL)
		*Offset = -1;
		
	return NULL;
}

Tree CurrentYieldParent()
{
	if (__CurrentYieldingTree == NULL)
		return NULL;
	
	Position L;
	
	L = First((List)__CurrentYieldingTree);
	if (L != NULL && L->Next != NULL)
		return (Tree)L->Next->Element;
	else
		return NULL;
}

Child FirstChild(Tree T)
{
	return T->FirstChild;
}

Sibling NextSibling(Sibling S)
{
	return S->NextSibling;
}

ElementType TNodeRetrieve(PTNode N)
{
	return N->Element;
}

void DeleteTNode(ElementType X, Tree T, Child (*Yield)(Tree T), int DeleteSubTreeAsWell)
{
	Child C, P;
	
	PushYieldState();
	for (C = Yield(T), P = NULL; C != NULL; P = C, C = Yield(NULL))
	{
		if (C == T)
			continue;
		
		if (TNodeRetrieve(C) == X)
		{	
			// P is sibling of C
			if (IsSibling(P, C))
				P->NextSibling = C->NextSibling;
			
			// P is parent of C
			if (IsProperAncestor(P, C))
				P->FirstChild = C->NextSibling;
			
			if (DeleteSubTreeAsWell)
				DeleteTree(&C, NULL); // DeleteTree will set C to NULL, which has no effect within this procedure
			else free(C);
			
			break;
		}
	}
	PopYieldState();
}

Child AddChild(ElementType X, Tree T)
{
	Child C;
	
	C = (Child)CreateTree();
	C->Element = X;
	
	AppendTree(C, T);
	
	return C;
}

Sibling AddSibling(ElementType X, Tree T)
{
	Sibling S, P;
	
	S = (Sibling)CreateTree();
	S->Element = X;
	
	P = T->NextSibling;
	if (P == NULL)
		T->NextSibling = S;
	else
	{
		while (P->NextSibling != NULL)
			P = P->NextSibling;
		P->NextSibling = S;
	}
	
	return S;
}

void AppendTree(Tree Sub, Tree Dst)
{
	Child P;
	
	P = Dst->FirstChild;
	if (P == NULL)
		Dst->FirstChild = Sub;
	else
	{
		while (P->NextSibling != NULL)
			P = P->NextSibling;
		P->NextSibling = Sub;
	}
}

void DeleteTree(Tree *T, Tree P)
{
	if (P != NULL)
		if ((P = (Tree)GetClosestConnection(*T, P, NULL, NULL, NULL)) != NULL)
			*((Tree *)P) = (*T)->NextSibling;
	Traverse(*T, PostOrderYield, __Walker_Deleter, NULL);
	free(*T);
	
	// Remember that setting an alias variable to NULL does not effect the tree itself
	// But it won't crash the program as well, so why not :)
	*T = NULL;
}

void ClearTree(Tree T)
{
	Traverse(T, PostOrderYield, __Walker_Deleter, NULL);
	T->FirstChild = NULL;
}

void TNodeSwap(PTNode A, PTNode B)
{
	ElementType Tmp;
	
	Tmp = A->Element;
	A->Element = B->Element;
	B->Element = Tmp;
}
