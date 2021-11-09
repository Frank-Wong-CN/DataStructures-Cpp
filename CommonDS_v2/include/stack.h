#ifndef _STACK_H
#define _STACK_H

#include "node.h"

#ifndef _NODE_IMPL_
#error Include a node definition before "stack.h"!
#endif

#include "list.h"

typedef Node *Stack;

Stack CreateStack();
void DisposeStack(Stack *S);
void Push(ElementType X, Stack S);
ElementType Top(Stack S);
ElementType Pop(Stack S);

#endif