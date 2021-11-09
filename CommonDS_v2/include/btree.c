#include "btree.h"

#include "common.h"

BTree BTreeCreateTree()
{
	BTree T;
	List L;
	
	T = CreateTree();
	L = CreateList();
	
	T->Element = (ElementType)L;
	
	return T;
}

BTree BTreeCreateTreeWithList(List *L, int Len)
{
	BTree T;
	List Br, Tmp;
	
	T = CreateTree();
	T->Element = (ElementType)*L;
	
	Br = *L;
	for (; Len > 0; Len--)
		Br = Advance(Br);
	Tmp = Advance(Br);
	Br->Next = NULL;
	
	Br = CreateList();
	Br->Next = Tmp;
	
	*L = Br;
	
	return T;
}

Child __BTree_GetNthChild(BTree T, int i)
{
	Child C;
	C = T->FirstChild;
	
	for (; i > 1; i--)
		C = C->NextSibling;
	
	return C;
}

void __BTree_SplitDown(BTree T, BTree P)
{
	List *Elem = (List *)&(T->Element), Tmp;
	int CurSize = Size(*Elem), i;
	//int SplitSize = (CurSize - 1) / 2; // BTREE_T_LEAST
	
	if (CurSize == BTREE_T)
	{
		// Split and propagate element back to parent
		if (P == NULL) // Grow downwards
		{
			BTree L, R, Br;
			L = BTreeCreateTreeWithList(Elem, BTREE_T_LEAST);
			R = BTreeCreateTreeWithList(Elem, 1);
			
			if (HasChild(T))
			{
				Br = T->FirstChild;
				// Give BTREE_T_LEAST + 1 children to left
				// Give BTREE_T_LEAST children to right
				L->FirstChild = Br;
				for (i = 0; i < BTREE_T_LEAST; i++)
					Br = Br->NextSibling;
				R->FirstChild = Br->NextSibling;
				Br->NextSibling = NULL;
			}
			
			T->FirstChild = L;
			L->NextSibling = R;
			
			Tmp = (List)*Elem;
			*Elem = (List)R->Element;
			R->Element = (ElementType)Tmp;
		}
		else // Propagate upwards
		{
			BTree R;
			List L, Prev;
			R = BTreeCreateTreeWithList(Elem, BTREE_T_LEAST + 1);
			
			Tmp = (List)*Elem;
			*Elem = (List)R->Element;
			R->Element = (ElementType)Tmp;
			
			R->NextSibling = T->NextSibling;
			T->NextSibling = R;
			
			for (Prev = NULL, L = *Elem; L->Next != NULL; Prev = L, L = Advance(L)) ; // Get the last and second last element of T->Element
			
			if (Prev != NULL) // If Prev is NULL, then L is a header node
			{
				Prev->Next = NULL;
				Last((List)P->Element)->Next = L;
				BubbleSort((List)P->Element);
			}
			else
				FatalError("Invalid split in B-Tree!\n");
		}
	}
}

void __BTreeAdd_Recursive(ElementType X, BTree T, BTree P)
{
	List L = (List)T->Element;
	Child C;
	
	// Iterate elements to find where this newly added element belongs to
	int i;
	Position Cur, Prev;
	for (i = 1, Prev = NULL, Cur = First(L); Cur != NULL; i++, Prev = Cur, Cur = Advance(Cur))
		if (Cur->Element > X)
			break;
	
	if (HasChild(T))
	{
		C = __BTree_GetNthChild(T, i);
		__BTreeAdd_Recursive(X, C, T);
	}
	else
		Insert(X, L, Prev);
	
	__BTree_SplitDown(T, P);
}

void BTreeAdd(ElementType X, BTree T)
{
	__BTreeAdd_Recursive(X, T, NULL);
}

// TODO
void BTreeRemoveNode(Child C, BTree T);
void BTreeRemoveValue(ElementType X, BTree T);
Child BTreeFind(ElementType X, BTree T);
