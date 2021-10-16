#include "list.h"
#include "common.h"

#include <cstring> // memset

List CreateList()
{
	List L;
	
	L = (List)malloc(sizeof(Node));
	memset(L, 0, sizeof(Node));
	
	return L;
}

List CloneList(List L)
{
	List C = CreateList();
	Position P, S;
	
	S = C;
	for (P = L; P != NULL; P = P->Next)
	{
		memcpy(S, P, sizeof(Node));
		if (P->Next != NULL)
		{
			S->Next = (Position)malloc(sizeof(Node));
			S = S->Next;
		}
	}
	
	return C;
}

int IsEmpty(List L)
{
	return L->Next == NULL;
}

int IsLast(Position P, List L)
{
	return P->Next == NULL;
}

Position Find(ElementType X, List L)
{
	Position P;
	
	P = L;
	while (P != NULL && P->Element != X)
		P = P->Next;
	
	return P;
}

Position FindPrevious(ElementType X, List L)
{
	Position P;
	
	P = L;
	while (P->Next != NULL && P->Next->Element != X)
		P = P->Next;
	
	return P;
}

Position Header(List L)
{
	return (Position)L;
}

Position First(List L)
{
	return L->Next;
}

Position Last(List L)
{
	Position P;
	
	P = L;
	while (P->Next != NULL)
		P = P->Next;
	
	return P;
}

Position Advance(Position P)
{
	return P->Next;
}

Position At(List L, unsigned int Index)
{
	Position P;
	
	P = L;
	while (Index-- >= 0 && P->Next != NULL)
		P = P->Next;
	
	return P;
}

ElementType Retrieve(Position P)
{
	return P->Element;
}

size_t Size(List L)
{
	size_t R = -1; // Does not count the first node (Header node)
	for (; L != NULL; L = L->Next)
		R += 1;
	return R;
}

void Delete(ElementType X, List L)
{
	Position P, TmpCell;
	
	P = FindPrevious(X, L);
	
	if (!IsLast(P, L))
	{
		TmpCell = P->Next;
		P->Next = TmpCell->Next;
		free(TmpCell);
	}
}

Position Insert(ElementType X, List L, Position P)
{
	if (P == NULL)
		P = L;
	if (P == NULL)
		return NULL;
	
	Position TmpCell;
	
	TmpCell = (Position)malloc(sizeof(Node));
	memset(TmpCell, 0, sizeof(Node));
	if (TmpCell == NULL)
		FatalError("Out of space!");
	
	TmpCell->Element = X;
	TmpCell->Next = P->Next;
	P->Next = TmpCell;
	
	return TmpCell;
}

void Swap(Position A, Position B)
{
	ElementType Tmp;
	Tmp = A->Element;
	A->Element = B->Element;
	B->Element = Tmp;
}

void MakeEmpty(List L)
{
	Position P, Tmp;
	
	P = L->Next;
	L->Next = NULL;
	while (P != NULL)
	{
		Tmp = P;
		P = P->Next;
		free(Tmp);
	}
}

void DeleteList(List *L)
{
	Position P, Tmp;
	
	P = *L;
	while (P != NULL)
	{
		Tmp = P;
		P = P->Next;
		free(Tmp);
	}
	
	*L = NULL;
}
