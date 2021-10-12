#include "queue.h"

Queue CreateQueue()
{
	return (Queue)CreateList();
}

void DisposeQueue(Queue *Q)
{
	DeleteList(Q);
}

void Enqueue(ElementType X, Queue Q)
{
	Insert(X, Q, Last(Q));
}

ElementType Front(Queue Q)
{
	if (!IsEmpty(Q))
		return Retrieve(First(Q));
	else
		FatalError("Trying to peek an empty queue!");
	
	return Q->Element;
}

ElementType Dequeue(Queue Q)
{
	ElementType X;
	
	if (!IsEmpty(Q))
	{
		X = Retrieve(First(Q));
		Delete(X, Q);
		return X;
	}
	else
		FatalError("Trying to dequeue an empty queue!");
	
	return X;
}