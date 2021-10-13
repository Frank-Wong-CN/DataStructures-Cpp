#ifndef _LIST_H
#define _LIST_H

#include "node.h"

#ifndef _NODE_IMPL_
#error Include a node definition before "list.h"!
#endif

List CreateList();
List CloneList(List L);
int IsEmpty(List L);
int IsLast(Position P, List L);
Position Find(ElementType X, List L);
Position FindPrevious(ElementType X, List L);
Position Header(List L);
Position First(List L);
Position Last(List L);
Position Advance(Position P);
Position At(List L, unsigned int Index);
ElementType Retrieve(Position P);
size_t Size(List L);

void Delete(ElementType X, List L);
void Insert(ElementType X, List L, Position P);
void Swap(Position A, Position B);
void MakeEmpty(List L);
void DeleteList(List *L);

#endif