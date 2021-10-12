/*
namespace DSv1
{
	#include "CommonDS_v1/common_ds.h"

	#include "CommonDS_v1/elem_functions.c"
	#include "CommonDS_v1/linked_list.c"
	#include "CommonDS_v1/stack.c"
	#include "CommonDS_v1/queue.c"
}
*/

// -- Option 1: Basic List
#include "CommonDS_v2/node_impl_basic.h"
// -- Option 2: Polynomial
//#include "CommonDS_v2/list_app_polynomial.h"
// -- Option 3: Radix Sort
//#include "CommonDS_v2/list_app_radix_sort.h"

#include "CommonDS_v2/list.h"
#include "CommonDS_v2/list.c"

#include "CommonDS_v2/list_app_polynomial.c"
#include "CommonDS_v2/list_app_radix_sort.c"

#include "CommonDS_v2/stack.c"
#include "CommonDS_v2/queue.c"

#ifdef _NODE_IMPL_RADIX

int RadixSort_Test(IntType *arr, const int N)
{
	RecordTime(N);
	RadixSort(arr, N);
	ShowTime(0);
}

#endif