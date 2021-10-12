#include "stack.h"

Stack CreateStack()
{
	return (Stack)CreateList();
}

void DisposeStack(Stack *S)
{
	DeleteList(S);
}

void Push(ElementType X, Stack S)
{
	Insert(X, S, S);
}

ElementType Top(Stack S)
{
	if (!IsEmpty(S))
		return Retrieve(First(S));
	else
		FatalError("Trying to peek an empty stack!");
	
	return S->Element;
}

ElementType Pop(Stack S)
{
	ElementType X;
	
	if (!IsEmpty(S))
	{
		X = Retrieve(First(S));
		Delete(X, S);
		return X;
	}
	else
		FatalError("Trying to pop an empty stack!");
	
	return X;
}