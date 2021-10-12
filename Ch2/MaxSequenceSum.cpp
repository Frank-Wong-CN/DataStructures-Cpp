#include "Utils.hpp"

int MSS_N3(const int A[], int N)
{
	RecordTime(N)
	
	int ThisSum, MaxSum, i, j, k;
	
	MaxSum = 0;
	for (i = 0; i < N; i++)
		for (j = i; j < N; j++)
		{
			ThisSum = 0;
			for (k = i; k <= j; k++)	// As analyzed, this loop is unnecessary and it's causing a tremendous amount of redundant calculations
				ThisSum += A[k];
			
			if (ThisSum > MaxSum)
				MaxSum = ThisSum;
		}
	
	ShowTime(MaxSum)
}

int MSS_N2(const int A[], int N)
{
	RecordTime(N)
	
	int ThisSum, MaxSum, i, j;
	
	MaxSum = 0;
	for (i = 0; i < N; i++)
	{
		ThisSum = 0;	
		for (j = i; j < N; j++)
		{
			ThisSum += A[j];
			
			if (ThisSum > MaxSum)
				MaxSum = ThisSum;
		}
	}
	
	ShowTime(MaxSum)
}

int MSS_NLogN_Recursive(const int A[], int Left, int Right)
{
	int MaxLSum, MaxRSum;
	int MaxLBSum, MaxRBSum; // B means Border
	int LBSum, RBSum;
	int Center, i;
	
	if (Left == Right)
		if (A[Left] > 0)
			return A[Left];
		else
			return 0;
		
	Center = (Left + Right) / 2;
	MaxLSum = MSS_NLogN_Recursive(A, Left, Center);
	MaxRSum = MSS_NLogN_Recursive(A, Center + 1, Right);
	
	MaxLBSum = 0;
	LBSum = 0;
	for (i = Center; i >= Left; i--)
	{
		LBSum += A[i];
		if (LBSum > MaxLBSum)
			MaxLBSum = LBSum;
	}
	
	MaxRBSum = 0;
	RBSum = 0;
	for (i = Center + 1; i <= Right; i++)
	{
		RBSum += A[i];
		if (RBSum > MaxRBSum)
			MaxRBSum = RBSum;
	}
	
	return Max3(MaxLSum, MaxRSum, MaxLBSum + MaxRBSum);
}

int MSS_NLogN(const int A[], int N)
{
	RecordTime(N)
	ShowTime(MSS_NLogN_Recursive(A, 0, N - 1))
}

int MSS_N(const int A[], int N)
{
	RecordTime(N)
	
	int ThisSum, MaxSum, j;
	
	ThisSum = MaxSum = 0;
	for (j = 0; j < N; j++)
	{
		ThisSum += A[j];
		
		if (ThisSum > MaxSum)
			MaxSum = ThisSum;
		else if (ThisSum < 0)
			ThisSum = 0;
	}
	
	ShowTime(MaxSum)
}
