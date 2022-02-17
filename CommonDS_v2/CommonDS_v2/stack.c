#include "stack.h"

CommonDS_v2_Stack CommonDS_v2_Stack_CreateStack()
{
	return (CommonDS_v2_Stack)CommonDS_v2_List_CreateList();
}

void CommonDS_v2_Stack_Dispose(CommonDS_v2_Stack *S)
{
	CommonDS_v2_List_DeleteList(S);
}

void CommonDS_v2_Stack_Push(CommonDS_v2_List_ElementType X, CommonDS_v2_Stack S)
{
	CommonDS_v2_List_Insert(X, S, S);
}

CommonDS_v2_List_ElementType CommonDS_v2_Stack_Top(CommonDS_v2_Stack S)
{
	if (!CommonDS_v2_List_IsEmpty(S))
		return CommonDS_v2_List_Retrieve(CommonDS_v2_List_First(S));
	else
		FatalError("Trying to peek an empty stack!");
	
	return S->Element;
}

CommonDS_v2_List_ElementType CommonDS_v2_Stack_Pop(CommonDS_v2_Stack S)
{
	CommonDS_v2_List_ElementType X = (CommonDS_v2_List_ElementType)0;
	
	if (!CommonDS_v2_List_IsEmpty(S))
	{
		X = CommonDS_v2_List_Retrieve(CommonDS_v2_List_First(S));
		CommonDS_v2_List_Delete(X, S);
		return X;
	}
	else
		FatalError("Trying to pop an empty stack!");
	
	return X;
}