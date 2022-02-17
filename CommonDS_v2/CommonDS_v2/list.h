#ifndef DSV2_LIST_H
#define DSV2_LIST_H

#include "node.h"

#ifndef DSV2_NODE_IMPL_
#include "node_impl_basic.h"
#ifndef _MSC_VER
#warning List node definition not found, basic implementation included.
#endif
#endif

CommonDS_v2_List CommonDS_v2_List_CreateList();
CommonDS_v2_List CommonDS_v2_List_CloneList(CommonDS_v2_List L);
int CommonDS_v2_List_IsEmpty(CommonDS_v2_List L);
int CommonDS_v2_List_IsLast(CommonDS_v2_List_Position P, CommonDS_v2_List L);
CommonDS_v2_List_Position CommonDS_v2_List_Find(CommonDS_v2_List_ElementType X, CommonDS_v2_List L);
CommonDS_v2_List_Position CommonDS_v2_List_FindPrevious(CommonDS_v2_List_ElementType X, CommonDS_v2_List L);
CommonDS_v2_List_Position CommonDS_v2_List_Header(CommonDS_v2_List L);
CommonDS_v2_List_Position CommonDS_v2_List_First(CommonDS_v2_List L);
CommonDS_v2_List_Position CommonDS_v2_List_Last(CommonDS_v2_List L);
CommonDS_v2_List_Position CommonDS_v2_List_Advance(CommonDS_v2_List_Position P);
CommonDS_v2_List_Position CommonDS_v2_List_At(CommonDS_v2_List L, unsigned int Index);
CommonDS_v2_List_ElementType CommonDS_v2_List_Retrieve(CommonDS_v2_List_Position P);
CommonDS_v2_SizeType CommonDS_v2_List_Size(CommonDS_v2_List L);

void CommonDS_v2_List_Delete(CommonDS_v2_List_ElementType X, CommonDS_v2_List L);
CommonDS_v2_List_Position CommonDS_v2_List_Insert(CommonDS_v2_List_ElementType X, CommonDS_v2_List L, CommonDS_v2_List_Position P);
void CommonDS_v2_List_Swap(CommonDS_v2_List_Position A, CommonDS_v2_List_Position B);
void CommonDS_v2_List_MakeEmpty(CommonDS_v2_List L);
void CommonDS_v2_List_DeleteList(CommonDS_v2_List *L);

#endif