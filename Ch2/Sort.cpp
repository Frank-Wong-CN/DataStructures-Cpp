#include "Utils.hpp"

int TestSort(int A[], int N)
{
	for (int i = 0; i < N - 1; i++)
		if (A[i] > A[i + 1])
			return 0;
	
	return 1;
}

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

int InsertionSort(int A[], int N)
{
	RecordTime(N)
	
	int curInd = 1;
	
	while (curInd != N)
	{
		int insInd = curInd, cmpInd = curInd; 	/* Take the value at insInd out as the value to compare and insert */
												/* cmpInd is the value currently comparing */
		while (--cmpInd >= 0 && A[insInd] < A[cmpInd])
		{
			Swap(A + insInd, A + cmpInd);
			insInd = cmpInd; /* Remember to change insInd as well since the swap is made */
		}
		
		curInd += 1;
	}
	
	ShowTime(1)
}

/**
 * ShellSort is primarily an insertion sort but with a more approximation approach.
 * ShellSort first assembles a better scenario for the insertion sort, each time by
 * a certain gap.
 * When gap comes down to 1, it's an insertion sort, and the array is almost sorted
 * and better than the one before the sort. Therefore reducing the average time
 * complexity of the insertion sort.
 */
int ShellSort(int A[], int N)
{
	RecordTime(N)
	
	/* Outer loop: iterate gap, from N/2 to 1 */
	int curGap = N / 2;	/* Start with a large gap, then reduce gradually later */
	while (curGap > 0)	/* Sort terminates at 0, meaning sorting complete */
	{
		/* Inner loop: iterate array, from current gap to the very last element of the array */
		int curShl = curGap;
		while (curShl < N)
		{
			/* Inner loop: take the current iterating element and compare with elements to its left, seperate by gap for each comparing elements */
			int shlInd = curShl, cmpInd = shlInd - curGap;
			while (cmpInd >= 0)
			{
				if (A[shlInd] < A[cmpInd])
				{
					Swap(A + shlInd, A + cmpInd);
					shlInd = cmpInd; /* Remember to change shlInd as well since the swap is made */
				}
				cmpInd -= curGap;
			}
			curShl += 1;
		}
		curGap /= 2;
	}
	
	ShowTime(1)
}