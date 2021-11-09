#ifndef _QUEUE_H
#define _QUEUE_H

#include "node.h"

#ifndef _NODE_IMPL_
#error Include a node definition before "queue.h"!
#endif

#include "list.h"

typedef Node *Queue;

Queue CreateQueue();
void DisposeQueue(Queue *Q);
void Enqueue(ElementType X, Queue Q);
ElementType Front(Queue Q);
ElementType Dequeue(Queue Q);

#endif