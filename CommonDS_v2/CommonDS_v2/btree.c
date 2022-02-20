#include "btree.h"
#include "common.h"

CommonDS_v2_BTree CommonDS_v2_BTree_CreateTree()
{
	CommonDS_v2_BTree T;
	CommonDS_v2_List L;
	
	L = CommonDS_v2_List_CreateList();
	T = CommonDS_v2_Tree_CreateTree((CommonDS_v2_List_ElementType)L);
	
	return T;
}

CommonDS_v2_BTree CommonDS_v2_BTree_CreateTreeFromList(CommonDS_v2_List *L, CommonDS_v2_SizeType Len)
{
	CommonDS_v2_BTree T;
	CommonDS_v2_List Br, Tmp;
	
	T = CommonDS_v2_Tree_CreateTree((CommonDS_v2_List_ElementType)*L);
	
	Br = *L;
	for (; Len > 0; Len--)
		Br = CommonDS_v2_List_Advance(Br);
	Tmp = CommonDS_v2_List_Advance(Br);
	Br->Next = NULL;
	
	Br = CommonDS_v2_List_CreateList();
	Br->Next = Tmp;
	
	*L = Br;
	
	return T;
}

CommonDS_v2_Tree_Child __CommonDS_v2_BTree_GetNthChild(CommonDS_v2_BTree T, int i)
{
	CommonDS_v2_Tree_Child C;
	C = T->FirstChild;
	
	for (; i > 1; i--)
		C = C->NextSibling;
	
	return C;
}

void __CommonDS_v2_BTree_SplitDown(CommonDS_v2_BTree T, CommonDS_v2_BTree P)
{
	CommonDS_v2_List *Elem = (CommonDS_v2_List *)&(T->Element), Tmp;
	CommonDS_v2_SizeType CurSize = CommonDS_v2_List_Size(*Elem), i;
	//int SplitSize = (CurSize - 1) / 2; // BTREE_T_LEAST
	
	if (CurSize == DSV2_BTREE_T)
	{
		// Split and propagate element back to parent
		if (P == NULL) // Grow downwards
		{
			CommonDS_v2_BTree L, R, Br;
			L = CommonDS_v2_BTree_CreateTreeFromList(Elem, DSV2_BTREE_T_LEAST);
			R = CommonDS_v2_BTree_CreateTreeFromList(Elem, 1);
			
			if (CommonDS_v2_Tree_HasChild(T))
			{
				Br = T->FirstChild;
				// Give BTREE_T_LEAST + 1 children to left
				// Give BTREE_T_LEAST children to right
				L->FirstChild = Br;
				for (i = 0; i < DSV2_BTREE_T_LEAST; i++)
					Br = Br->NextSibling;
				R->FirstChild = Br->NextSibling;
				Br->NextSibling = NULL;
			}
			
			T->FirstChild = L;
			L->NextSibling = R;
			
			Tmp = (CommonDS_v2_List)*Elem;
			*Elem = (CommonDS_v2_List)R->Element;
			R->Element = (CommonDS_v2_List_ElementType)Tmp;
		}
		else // Propagate upwards
		{
			CommonDS_v2_BTree R;
			CommonDS_v2_List L, Prev;
			R = CommonDS_v2_BTree_CreateTreeFromList(Elem, DSV2_BTREE_T_LEAST + 1);
			
			Tmp = (CommonDS_v2_List)*Elem;
			*Elem = (CommonDS_v2_List)R->Element;
			R->Element = (CommonDS_v2_List_ElementType)Tmp;
			
			R->NextSibling = T->NextSibling;
			T->NextSibling = R;
			
			for (Prev = NULL, L = *Elem; L->Next != NULL; Prev = L, L = CommonDS_v2_List_Advance(L)) ; // Get the last and second last element of T->Element
			
			if (Prev != NULL) // If Prev is NULL, then L is a header node
			{
				Prev->Next = NULL;
				CommonDS_v2_List_Last((CommonDS_v2_List)P->Element)->Next = L;
				CommonDS_v2_List_BubbleSort((CommonDS_v2_List)P->Element);
			}
			else
				FatalError("Invalid split in B-Tree!\n");
		}
	}
}

void __CommonDS_v2_BTree_RecursiveAdd(CommonDS_v2_List_ElementType X, CommonDS_v2_BTree T, CommonDS_v2_BTree P)
{
	CommonDS_v2_List L = (CommonDS_v2_List)T->Element;
	CommonDS_v2_Tree_Child C;
	
	// Iterate elements to find where this newly added element belongs to
	int i;
	CommonDS_v2_List_Position Cur, Prev;
	for (i = 1, Prev = NULL, Cur = CommonDS_v2_List_First(L); Cur != NULL; i++, Prev = Cur, Cur = CommonDS_v2_List_Advance(Cur))
		if (Cur->Element > X)
			break;
	
	if (CommonDS_v2_Tree_HasChild(T))
	{
		C = __CommonDS_v2_BTree_GetNthChild(T, i);
		__CommonDS_v2_BTree_RecursiveAdd(X, C, T);
	}
	else
		CommonDS_v2_List_Insert(X, L, Prev);
	
	__CommonDS_v2_BTree_SplitDown(T, P);
}

void CommonDS_v2_BTree_Add(CommonDS_v2_List_ElementType X, CommonDS_v2_BTree T)
{
	__CommonDS_v2_BTree_RecursiveAdd(X, T, NULL);
}

// TODO
void CommonDS_v2_BTree_RemoveNode(CommonDS_v2_Tree_Child C, CommonDS_v2_BTree T) {}
void CommonDS_v2_BTree_RemoveValue(CommonDS_v2_List_ElementType X, CommonDS_v2_BTree T) {}
CommonDS_v2_Tree_Child CommonDS_v2_BTree_Find(CommonDS_v2_List_ElementType X, CommonDS_v2_BTree T) { return NULL; }
