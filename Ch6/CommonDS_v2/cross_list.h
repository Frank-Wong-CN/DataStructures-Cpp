#ifndef _CROSS_LIST_H
#define _CROSS_LIST_H

#include "cnode.h"

#ifndef _CNODE_IMPL_
#warning CNode definition not found before "cross_list.h". Using basic implementation.
#include "cnode_impl_basic.h"
#endif

CList CreateCList();
CList CloneCList(CList L);
CPos CFind(ElementType X, CList L);
CPos CCrossFind(ElementType X, CList L, CPos (*F)(ElementType, CList)); // BFS, DFS

void DestroyCList();

#endif