#include "list_app_radix_sort.h"

#ifdef _NODE_IMPL_RADIX

#include <cmath>
#include "common.h"

void RadixSort(IntType *A, const int S)
{
	if (S < 1 || A == NULL)
		return;
	
	// This radix sort assumes base 10
	int i, j;
	IntType HighestDigit, CurDigit;
	Radix R;
	Position D, N, PrevN, M;
	
	R = (Radix)malloc(sizeof(Node));
	R->Index = -1;
	R->Numbers = NULL;
	R->Next = NULL;
	
	// Initialize barrels
	for (i = 10 /* Base 10 */; i > 0; i--)
	{
		Insert(i - 1, R, R);
		D = First(R);
		D->Numbers = (List)malloc(sizeof(Node));
		D->Numbers->Index = -1;
		D->Numbers->Numbers = D->Numbers; // The last element
		D->Numbers->Next = NULL;
	}

	// Calculate the highest digit
	for (i = 0; i < S; i++)
		HighestDigit |= A[i];
	HighestDigit |= 1;
	HighestDigit = (IntType)ceil(log10(HighestDigit));
	if (HighestDigit == 0)
		HighestDigit = 1;
	
	j = 1;
	while (HighestDigit > 0)
	{
		// Put everything into the barrels
		for (i = 0; i < S; i++)
		{
			CurDigit = (A[i] / j) % 10;
			D = Find(CurDigit, R);
			Insert(A[i], D->Numbers, D->Numbers->Numbers);
			D->Numbers->Numbers = D->Numbers->Numbers->Next;
		}
		
		// Put everything back to the array
		i = 0;
		for (D = First(R); D != NULL; D = Advance(D))
		for (N = First(D->Numbers); N != NULL; N = Advance(N))
			A[i++] = N->Index;
		
		// Initialize the barrels
		for (D = First(R); D != NULL; D = Advance(D))
		{
			MakeEmpty(D->Numbers);
			D->Numbers->Numbers = D->Numbers;
		}
		
		j *= 10;
		HighestDigit -= 1;
	}
}

#endif