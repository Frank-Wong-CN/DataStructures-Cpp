#ifndef DSV2_LIST_SORT_H
#define DSV2_LIST_SORT_H

#include "list.h"

void CommonDS_v2_List_BubbleSort(CommonDS_v2_List L)
{
	CommonDS_v2_List_Position i, j;
	for (i = CommonDS_v2_List_First(L); i != NULL; i = CommonDS_v2_List_Advance(i))
		for (j = i; j != NULL; j = CommonDS_v2_List_Advance(j))
			if (i->Element > j->Element)
				CommonDS_v2_List_Swap(i, j);
}

#endif