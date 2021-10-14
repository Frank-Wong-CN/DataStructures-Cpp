#ifndef _MULTI_LIST_H
#define _MULTI_LIST_H

#ifndef _NODE_IMPL_
#include "../Ch3/CommonDS_v2/node_impl_basic.h"
#endif

#include "../Ch3/CommonDS_v2/list.h"
#include "../Ch3/CommonDS_v2/stack.h"
#include "../Ch3/CommonDS_v2/queue.h"

#include "mnode.h"

#ifndef _NODE_IMPL_
#error Include a node definition before "multi_list.h"!
#endif

#include <stdarg.h>

// ADT
MultiList CreateMList();
MultiListPosition Find(MultiList L, int D, MNodeElementType X);
MultiListPosition At(MultiList L, int X, ...);
MNodeElementType Retrieve(MultiListPosition P);
size_t Size(MultiList L, int D);

void MDelete(MultiList L, int D, MNodeElementType X);
void MInsert(MultiList L, MultiListPosition P, MNodeElementType X, ...);
void DestroyMList(MultiList *L);

#endif