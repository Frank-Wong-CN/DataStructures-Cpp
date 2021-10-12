#include "Utils.hpp"

unsigned int Gcd(unsigned int M, unsigned int N)
{
	RecordTime(N)
	
	unsigned int Rem;
	while (N > 0)
	{
		Rem = M % N;
		M = N;
		N = Rem;
	}
	
	ShowTime(M)
}

long Pow_Recursive(long X, unsigned int N)
{
	if (N == 0)
		return 1;
	if (N == 1)
		return X;
	if (N % 2 == 0)
		return Pow_Recursive(X * X, N / 2);
	else
		return Pow_Recursive(X * X, N / 2) * X;
}

long Pow(long X, unsigned int N)
{
	RecordTime(N)
	ShowTime(Pow_Recursive(X, N));
}
