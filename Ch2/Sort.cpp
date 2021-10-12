#include "Utils.hpp"

int BubbleSort(int A[], int N)
{
	RecordTime(N)
	
	int i, j;
	
	for (i = 0; i < N; i++)
		for (j = i; j < N; j++)
			if (A[j] < A[i])
				Swap(A + j, A + i);
			
	ShowTime(1)
}