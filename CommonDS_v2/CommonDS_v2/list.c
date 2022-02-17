#include "list.h"
#include "common.h"

CommonDS_v2_List CommonDS_v2_List_CreateList()
{
	CommonDS_v2_List L;
	
	L = (CommonDS_v2_List)malloc(sizeof(CommonDS_v2_List_Node));
	memset(L, 0, sizeof(CommonDS_v2_List_Node));
	
	return L;
}

CommonDS_v2_List CommonDS_v2_List_CloneList(CommonDS_v2_List L)
{
	CommonDS_v2_List C = CommonDS_v2_List_CreateList();
	CommonDS_v2_List_Position P, S;
	
	S = C;
	for (P = L; P != NULL; P = P->Next)
	{
		memcpy(S, P, sizeof(CommonDS_v2_List_Node));
		if (P->Next != NULL)
		{
			S->Next = (CommonDS_v2_List_Position)malloc(sizeof(CommonDS_v2_List_Node));
			S = S->Next;
		}
	}
	
	return C;
}

int CommonDS_v2_List_IsEmpty(CommonDS_v2_List L)
{
	return L->Next == NULL;
}

int CommonDS_v2_List_IsLast(CommonDS_v2_List_Position P, CommonDS_v2_List L)
{
	return P->Next == NULL;
}

CommonDS_v2_List_Position CommonDS_v2_List_Find(CommonDS_v2_List_ElementType X, CommonDS_v2_List L)
{
	CommonDS_v2_List_Position P;
	
	P = L;
	while (P != NULL && P->Element != X)
		P = P->Next;
	
	return P;
}

CommonDS_v2_List_Position CommonDS_v2_List_FindPrevious(CommonDS_v2_List_ElementType X, CommonDS_v2_List L)
{
	CommonDS_v2_List_Position P;
	
	P = L;
	while (P->Next != NULL && P->Next->Element != X)
		P = P->Next;
	
	return P;
}

CommonDS_v2_List_Position CommonDS_v2_List_Header(CommonDS_v2_List L)
{
	return (CommonDS_v2_List_Position)L;
}

CommonDS_v2_List_Position CommonDS_v2_List_First(CommonDS_v2_List L)
{
	return L->Next;
}

CommonDS_v2_List_Position CommonDS_v2_List_Last(CommonDS_v2_List L)
{
	CommonDS_v2_List_Position P;
	
	P = L;
	while (P->Next != NULL)
		P = P->Next;
	
	return P;
}

CommonDS_v2_List_Position CommonDS_v2_List_Advance(CommonDS_v2_List_Position P)
{
	return P->Next;
}

CommonDS_v2_List_Position CommonDS_v2_List_At(CommonDS_v2_List L, unsigned int Index)
{
	CommonDS_v2_List_Position P;
	
	P = L->Next;
	while (Index != 0 && P != NULL)
	{
		Index -= 1;
		P = P->Next;
	}
	
	return P;
}

CommonDS_v2_List_ElementType CommonDS_v2_List_Retrieve(CommonDS_v2_List_Position P)
{
	return P->Element;
}

CommonDS_v2_SizeType CommonDS_v2_List_Size(CommonDS_v2_List L)
{
	CommonDS_v2_SizeType R = -1; // Does not count the first node (Header node)
	for (; L != NULL; L = L->Next)
		R += 1;
	return R;
}

void CommonDS_v2_List_Delete(CommonDS_v2_List_ElementType X, CommonDS_v2_List L)
{
	CommonDS_v2_List_Position P, TmpCell;
	
	P = CommonDS_v2_List_FindPrevious(X, L);
	
	if (!CommonDS_v2_List_IsLast(P, L))
	{
		TmpCell = P->Next;
		P->Next = TmpCell->Next;
		free(TmpCell);
	}
}

CommonDS_v2_List_Position CommonDS_v2_List_Insert(CommonDS_v2_List_ElementType X, CommonDS_v2_List L, CommonDS_v2_List_Position P)
{
	if (P == NULL)
		P = L;
	if (P == NULL)
		return NULL;
	
	CommonDS_v2_List_Position TmpCell;
	
	TmpCell = (CommonDS_v2_List_Position)malloc(sizeof(CommonDS_v2_List_Node));
	memset(TmpCell, 0, sizeof(CommonDS_v2_List_Node));
	if (TmpCell == NULL)
		FatalError("Out of space!");
	
	TmpCell->Element = X;
	TmpCell->Next = P->Next;
	P->Next = TmpCell;
	
	return TmpCell;
}

void CommonDS_v2_List_Swap(CommonDS_v2_List_Position A, CommonDS_v2_List_Position B)
{
	CommonDS_v2_List_ElementType Tmp;
	Tmp = A->Element;
	A->Element = B->Element;
	B->Element = Tmp;
}

void CommonDS_v2_List_MakeEmpty(CommonDS_v2_List L)
{
	CommonDS_v2_List_Position P, Tmp;
	
	P = L->Next;
	L->Next = NULL;
	while (P != NULL)
	{
		Tmp = P;
		P = P->Next;
		free(Tmp);
	}
}

void CommonDS_v2_List_DeleteList(CommonDS_v2_List *L)
{
	CommonDS_v2_List_Position P, Tmp;
	
	P = *L;
	while (P != NULL)
	{
		Tmp = P;
		P = P->Next;
		free(Tmp);
	}
	
	*L = NULL;
}
