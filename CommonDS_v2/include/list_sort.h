#ifndef _LIST_SORT_H_
#define _LIST_SORT_H_

#include "list.h"

inline void BubbleSort(List L)
{
	Position i, j;
	for (i = First(L); i != NULL; i = Advance(i))
		for (j = i; j != NULL; j = Advance(j))
			if (i->Element > j->Element)
				Swap(i, j);
}

#endif