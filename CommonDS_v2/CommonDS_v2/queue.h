#ifndef DSV2_QUEUE_H
#define DSV2_QUEUE_H

#include "node.h"
#include "list.h"

typedef CommonDS_v2_List_Node *CommonDS_v2_Queue;

CommonDS_v2_Queue CommonDS_v2_Queue_CreateQueue();
void CommonDS_v2_Queue_Dispose(CommonDS_v2_Queue *Q);
void CommonDS_v2_Queue_Enqueue(CommonDS_v2_List_ElementType X, CommonDS_v2_Queue Q);
CommonDS_v2_List_ElementType CommonDS_v2_Queue_Front(CommonDS_v2_Queue Q);
CommonDS_v2_List_ElementType CommonDS_v2_Queue_Dequeue(CommonDS_v2_Queue Q);

#endif