#include "queue.h"

CommonDS_v2_Queue CommonDS_v2_Queue_CreateQueue()
{
	return (CommonDS_v2_Queue)CommonDS_v2_List_CreateList();
}

void CommonDS_v2_Queue_Dispose(CommonDS_v2_Queue *Q)
{
	CommonDS_v2_List_DeleteList(Q);
}

void CommonDS_v2_Queue_Enqueue(CommonDS_v2_List_ElementType X, CommonDS_v2_Queue Q)
{
	CommonDS_v2_List_Insert(X, Q, CommonDS_v2_List_Last(Q));
}

CommonDS_v2_List_ElementType CommonDS_v2_Queue_Front(CommonDS_v2_Queue Q)
{
	if (!CommonDS_v2_List_IsEmpty(Q))
		return CommonDS_v2_List_Retrieve(CommonDS_v2_List_First(Q));
	else
		FatalError("Trying to peek an empty queue!");
	
	return Q->Element;
}

CommonDS_v2_List_ElementType CommonDS_v2_Queue_Dequeue(CommonDS_v2_Queue Q)
{
	CommonDS_v2_List_ElementType X = (CommonDS_v2_List_ElementType)0;
	
	if (!CommonDS_v2_List_IsEmpty(Q))
	{
		X = CommonDS_v2_List_Retrieve(CommonDS_v2_List_First(Q));
		CommonDS_v2_List_Delete(X, Q);
		return X;
	}
	else
		FatalError("Trying to dequeue an empty queue!");
	
	return X;
}