#include "tree.h"
#include "common.h"

int __CommonDS_v2_Tree_Walker_Deleter(CommonDS_v2_Tree_Child CurNode, CommonDS_v2_Tree_Sibling PrevNode, CommonDS_v2_Tree Parent, CommonDS_v2_Tree_PayloadType Data)
{
	if (Parent == NULL)
		return 0;
	
	if (PrevNode != NULL)
		free(PrevNode);
	
	return 1;
}

CommonDS_v2_Tree CommonDS_v2_Tree_CreateTree()
{
	CommonDS_v2_Tree T;
	
	T = (CommonDS_v2_Tree)malloc(sizeof(CommonDS_v2_Tree_Node));
	memset(T, 0, sizeof(CommonDS_v2_Tree_Node));
	
	return T;
}

int CommonDS_v2_Tree_HasChild(CommonDS_v2_Tree T)
{
	return T->FirstChild != NULL;
}

int CommonDS_v2_Tree_HasSibling(CommonDS_v2_Tree T)
{
	return T->NextSibling != NULL;
}

int CommonDS_v2_Tree_IsChild(CommonDS_v2_Tree T, CommonDS_v2_Tree_Child C)
{
	return T->FirstChild == C;
}

int CommonDS_v2_Tree_IsSibling(CommonDS_v2_Tree_Sibling A, CommonDS_v2_Tree_Sibling B)
{
	if (A == NULL || B == NULL)
		return 0;
	
	CommonDS_v2_Tree_Sibling C;
	
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

int CommonDS_v2_Tree_IsProperAncestor(CommonDS_v2_Tree Ancestor, CommonDS_v2_Tree Descendant)
{
	if (Ancestor == NULL || Descendant == NULL)
		return 0;
	
	CommonDS_v2_Tree_Child C;
	
	CommonDS_v2_Tree_PushYieldState();
	for (C = CommonDS_v2_Tree_PreOrderYield(Ancestor); C != NULL; C = CommonDS_v2_Tree_PreOrderYield(NULL))
		if (C == Descendant)
		{
			CommonDS_v2_Tree_PopYieldState();
			return 1;
		}
	
	CommonDS_v2_Tree_PopYieldState();
	return 0;
}

int CommonDS_v2_Tree_IsProperDescendant(CommonDS_v2_Tree Descendant, CommonDS_v2_Tree Ancestor)
{
	return CommonDS_v2_Tree_IsProperAncestor(Ancestor, Descendant);
}

int CommonDS_v2_Tree_IsInSameTree(CommonDS_v2_Tree A, CommonDS_v2_Tree B)
{
	if (A == B && A != NULL)
		return 1;
	
	return CommonDS_v2_Tree_IsProperAncestor(A, B) || CommonDS_v2_Tree_IsProperDescendant(A, B);
}

CommonDS_v2_Tree_Child CommonDS_v2_Tree_PreOrderYield(CommonDS_v2_Tree T)
{
	CommonDS_v2_Tree_Child C;
	
	if (T == NULL) /* Yield on existing tree */
	{
		if (CommonDS_v2_Tree_CurrentYieldingTree == NULL) /* No existing tree to yield */
			return NULL;
		else
		{
			// Preorder yield: children first
			C = CommonDS_v2_Tree_FirstChild((CommonDS_v2_Tree)CommonDS_v2_Stack_Top(CommonDS_v2_Tree_CurrentYieldingTree));
			if (C != NULL) /* If has child, then yield child */
			{
				CommonDS_v2_Stack_Push((CommonDS_v2_List_ElementType)C, CommonDS_v2_Tree_CurrentYieldingTree);
				return C;
			}
			else /* If leaf node, then yield next sibling */
			{
				// Try to iterate a valid sibling
				while (C == NULL && !CommonDS_v2_List_IsEmpty(CommonDS_v2_Tree_CurrentYieldingTree))
				{
					C = (CommonDS_v2_Tree_Child)CommonDS_v2_Stack_Pop(CommonDS_v2_Tree_CurrentYieldingTree);
					C = CommonDS_v2_Tree_NextSibling((CommonDS_v2_Tree_Sibling)C);
				}
				
				if (C != NULL) /* A valid sibling is found */
				{
					CommonDS_v2_Stack_Push((CommonDS_v2_List_ElementType)C, CommonDS_v2_Tree_CurrentYieldingTree);
					return C;
				}
				else /* If no such sibling is found, then the tree is completely traversed */
				{
					CommonDS_v2_Stack_Dispose(&CommonDS_v2_Tree_CurrentYieldingTree);
					return NULL;
				}
			}
		}
	}
	else /* Yield new tree */
	{
		// Dispose previous yielding tree
		if (CommonDS_v2_Tree_CurrentYieldingTree != NULL)
			CommonDS_v2_Stack_Dispose(&CommonDS_v2_Tree_CurrentYieldingTree);
		
		// Initialize yield stack and return the root
		CommonDS_v2_Tree_CurrentYieldingTree = CommonDS_v2_Stack_CreateStack();
		CommonDS_v2_Stack_Push((CommonDS_v2_List_ElementType)T, CommonDS_v2_Tree_CurrentYieldingTree);
		return T;
	}
}

CommonDS_v2_Tree_Child CommonDS_v2_Tree_PostOrderYield(CommonDS_v2_Tree T)
{
	CommonDS_v2_Tree_Child C;
	
	if (T == NULL)
	{
		if (CommonDS_v2_Tree_CurrentYieldingTree == NULL) /* No existing tree to yield */
			return NULL;
		
		// Postorder yield: siblings first
		C = (CommonDS_v2_Tree_Child)CommonDS_v2_Stack_Pop(CommonDS_v2_Tree_CurrentYieldingTree);
		C = C->NextSibling;
		if (C == NULL) /* Subtree traversed completely */
		{
			if (CommonDS_v2_List_IsEmpty(CommonDS_v2_Tree_CurrentYieldingTree)) /* Entire tree is completely traversed */
			{
				CommonDS_v2_Stack_Dispose(&CommonDS_v2_Tree_CurrentYieldingTree);
				return NULL;
			}
			else
				C = (CommonDS_v2_Tree_Child)CommonDS_v2_Stack_Top(CommonDS_v2_Tree_CurrentYieldingTree);
		}
		else /* More children to traverse */
		{
			// Search for the next leaf
			CommonDS_v2_Stack_Push((CommonDS_v2_List_ElementType)C, CommonDS_v2_Tree_CurrentYieldingTree);
			while (C->FirstChild != NULL)
			{
				C = C->FirstChild;
				CommonDS_v2_Stack_Push((CommonDS_v2_List_ElementType)C, CommonDS_v2_Tree_CurrentYieldingTree);
			}
		}
		return C;
	}
	else /* Yield new tree */
	{
		// Dispose previous yielding tree
		if (CommonDS_v2_Tree_CurrentYieldingTree != NULL)
			CommonDS_v2_Stack_Dispose(&CommonDS_v2_Tree_CurrentYieldingTree);
		
		// Initialize yield stack and return the first leaf
		CommonDS_v2_Tree_CurrentYieldingTree = CommonDS_v2_Stack_CreateStack();
		CommonDS_v2_Stack_Push((CommonDS_v2_List_ElementType)T, CommonDS_v2_Tree_CurrentYieldingTree);
		C = T;
		while (C->FirstChild != NULL)
		{
			C = C->FirstChild;
			CommonDS_v2_Stack_Push((CommonDS_v2_List_ElementType)C, CommonDS_v2_Tree_CurrentYieldingTree);
		}
		return C;
	}
}

// TODO
CommonDS_v2_Tree_Child CommonDS_v2_Tree_BottomUpLevelYield(CommonDS_v2_Tree T)
{ return NULL; }

// TODO
CommonDS_v2_Tree_Child CommonDS_v2_Tree_TopDownLevelYield(CommonDS_v2_Tree T)
{ return NULL; }

void CommonDS_v2_Tree_PushYieldState()
{
	if (CommonDS_v2_Tree_CurrentYieldingTree == NULL)
		return;
	
	if (CommonDS_v2_Tree_SavedYieldState == NULL)
		CommonDS_v2_Tree_SavedYieldState = CommonDS_v2_Stack_CreateStack();
	
	CommonDS_v2_Stack Tmp = (CommonDS_v2_Stack)CommonDS_v2_List_CloneList(CommonDS_v2_Tree_CurrentYieldingTree);
	CommonDS_v2_Stack_Push((CommonDS_v2_List_ElementType)Tmp, CommonDS_v2_Tree_SavedYieldState);
}

void CommonDS_v2_Tree_PopYieldState()
{
	if (CommonDS_v2_Tree_SavedYieldState == NULL)
		return;
	
	CommonDS_v2_Stack_Dispose(&CommonDS_v2_Tree_CurrentYieldingTree);
	CommonDS_v2_Tree_CurrentYieldingTree = (CommonDS_v2_Stack)CommonDS_v2_Stack_Pop(CommonDS_v2_Tree_SavedYieldState);
}

void CommonDS_v2_Tree_Traverse(CommonDS_v2_Tree T, CommonDS_v2_Tree_Child (*Yielder)(CommonDS_v2_Tree T), int (*F)(CommonDS_v2_Tree_Child CurNode, CommonDS_v2_Tree_Sibling PrevNode, CommonDS_v2_Tree Parent, CommonDS_v2_Tree_PayloadType Data), CommonDS_v2_Tree_PayloadType D)
{
	CommonDS_v2_Tree_PushYieldState();
	
	CommonDS_v2_Tree Cur, Prev, Par;
	
	for (Prev = NULL, Cur = (CommonDS_v2_Tree)Yielder(T); Cur != NULL; Prev = Cur, Cur = (CommonDS_v2_Tree)Yielder(NULL))
	{
		Par = CommonDS_v2_Tree_CurrentYieldParent();
		if (!F(Cur, Prev, Par, D))
			break;
	}
	
	CommonDS_v2_Tree_PopYieldState();
}

CommonDS_v2_Tree *CommonDS_v2_Tree_GetClosestConnection(CommonDS_v2_Tree_Child C, CommonDS_v2_Tree T, CommonDS_v2_Tree R, CommonDS_v2_Tree *P, unsigned long long *Offset)
{
	CommonDS_v2_Tree Tmp;
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
			*Offset = offsetof(CommonDS_v2_Tree_Node, NextSibling);
		
		return (CommonDS_v2_Tree *)&(Tmp->NextSibling);
	}

	if (T == NULL)
		Tmp = R;
	else
		Tmp = T;
	
	if (Tmp->FirstChild != NULL)
	{
		if (Tmp->FirstChild == C)
		{
			if (P != NULL)
				*P = Tmp;
			if (Offset != NULL)
				*Offset = offsetof(CommonDS_v2_Tree_Node, FirstChild);
			
			return (CommonDS_v2_Tree *)&(Tmp->FirstChild);
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
					*Offset = offsetof(CommonDS_v2_Tree_Node, NextSibling);
				
				return (CommonDS_v2_Tree *)&(Tmp->NextSibling);
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
	}
	
	if (P != NULL)
		*P = NULL;
	if (Offset != NULL)
		*Offset = -1;
		
	return NULL;
}

CommonDS_v2_Tree CommonDS_v2_Tree_CurrentYieldParent()
{
	if (CommonDS_v2_Tree_CurrentYieldingTree == NULL)
		return NULL;
	
	CommonDS_v2_List_Position L;
	
	L = CommonDS_v2_List_First((CommonDS_v2_List)CommonDS_v2_Tree_CurrentYieldingTree);
	if (L != NULL && L->Next != NULL)
		return (CommonDS_v2_Tree)L->Next->Element;
	else
		return NULL;
}

CommonDS_v2_Tree_Child CommonDS_v2_Tree_FirstChild(CommonDS_v2_Tree T)
{
	return T->FirstChild;
}

CommonDS_v2_Tree_Sibling CommonDS_v2_Tree_NextSibling(CommonDS_v2_Tree_Sibling S)
{
	return S->NextSibling;
}

CommonDS_v2_List_ElementType CommonDS_v2_Tree_Retrieve(CommonDS_v2_Tree_PNode N)
{
	return N->Element;
}

void CommonDS_v2_Tree_Delete(CommonDS_v2_List_ElementType X, CommonDS_v2_Tree T, CommonDS_v2_Tree_Child (*Yielder)(CommonDS_v2_Tree T), int DeleteSubTreeAsWell)
{
	CommonDS_v2_Tree_Child C, P;
	
	CommonDS_v2_Tree_PushYieldState();
	for (C = Yielder(T), P = NULL; C != NULL; P = C, C = Yielder(NULL))
	{
		if (C == T)
			continue;
		
		if (CommonDS_v2_Tree_Retrieve(C) == X)
		{	
			// P is sibling of C
			if (CommonDS_v2_Tree_IsSibling(P, C))
				P->NextSibling = C->NextSibling;
			
			// P is parent of C
			if (CommonDS_v2_Tree_IsProperAncestor(P, C))
				P->FirstChild = C->NextSibling;
			
			if (DeleteSubTreeAsWell)
				CommonDS_v2_Tree_DeleteTree(&C, NULL); // CommonDS_v2_Tree_DeleteTree will set C to NULL, which has no effect within this procedure
			else free(C);
			
			break;
		}
	}
	CommonDS_v2_Tree_PopYieldState();
}

CommonDS_v2_Tree_Child CommonDS_v2_Tree_AddChild(CommonDS_v2_List_ElementType X, CommonDS_v2_Tree T)
{
	CommonDS_v2_Tree_Child C;
	
	C = (CommonDS_v2_Tree_Child)CommonDS_v2_Tree_CreateTree();
	C->Element = X;
	
	CommonDS_v2_Tree_AppendTree(C, T);
	
	return C;
}

CommonDS_v2_Tree_Sibling CommonDS_v2_Tree_AddSibling(CommonDS_v2_List_ElementType X, CommonDS_v2_Tree T)
{
	CommonDS_v2_Tree_Sibling S, P;
	
	S = (CommonDS_v2_Tree_Sibling)CommonDS_v2_Tree_CreateTree();
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

void CommonDS_v2_Tree_AppendTree(CommonDS_v2_Tree Sub, CommonDS_v2_Tree Dst)
{
	CommonDS_v2_Tree_Child P;
	
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

void CommonDS_v2_Tree_DeleteTree(CommonDS_v2_Tree *T, CommonDS_v2_Tree P)
{
	if (P != NULL)
		if ((P = (CommonDS_v2_Tree)CommonDS_v2_Tree_GetClosestConnection(*T, P, NULL, NULL, NULL)) != NULL)
			*((CommonDS_v2_Tree *)P) = (*T)->NextSibling;

	CommonDS_v2_Tree_Traverse(*T, CommonDS_v2_Tree_PostOrderYield, __CommonDS_v2_Tree_Walker_Deleter, (CommonDS_v2_Tree_PayloadType)0);
	free(*T);
	
	*T = NULL;
}

void CommonDS_v2_Tree_MakeEmpty(CommonDS_v2_Tree T)
{
	CommonDS_v2_Tree_Traverse(T, CommonDS_v2_Tree_PostOrderYield, __CommonDS_v2_Tree_Walker_Deleter, (CommonDS_v2_Tree_PayloadType)0);
	T->FirstChild = NULL;
}

void CommonDS_v2_Tree_Swap(CommonDS_v2_Tree_PNode A, CommonDS_v2_Tree_PNode B)
{
	CommonDS_v2_List_ElementType Tmp;
	
	Tmp = A->Element;
	A->Element = B->Element;
	B->Element = Tmp;
}
