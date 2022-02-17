#ifndef DSV2_STACK_H
#define DSV2_STACK_H

#include "node.h"
#include "list.h"

typedef CommonDS_v2_List_Node *CommonDS_v2_Stack;

CommonDS_v2_Stack CommonDS_v2_Stack_CreateStack();
void CommonDS_v2_Stack_Dispose(CommonDS_v2_Stack *S);
void CommonDS_v2_Stack_Push(CommonDS_v2_List_ElementType X, CommonDS_v2_Stack S);
CommonDS_v2_List_ElementType CommonDS_v2_Stack_Top(CommonDS_v2_Stack S);
CommonDS_v2_List_ElementType CommonDS_v2_Stack_Pop(CommonDS_v2_Stack S);

#endif