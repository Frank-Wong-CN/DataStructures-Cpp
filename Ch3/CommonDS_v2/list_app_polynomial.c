#include "list_app_polynomial.h"

#ifdef _NODE_IMPL_POLYNOMIAL

void ZeroPolynomial(Polynomial Poly)
{
	List L = (List)Poly;
	Position CurP;
	
	CurP = First(L);
	while (CurP != NULL)
	{
		CurP->Coefficient = 0;
		CurP = Advance(CurP);
	}
}

Polynomial AddPolynomial(Polynomial LeftOprand, const Polynomial RightOprand)
{
	List R = RightOprand, L = LeftOprand;
	Position RP, LP;
	
	RP = First(R);
	while (RP != NULL)
	{
		LP = Find(RP->Exponent, L);
		if (LP == NULL)
		{
			Insert(RP->Exponent, L, L);
			LP = First(L);
		}
		LP->Coefficient += RP->Coefficient;
		RP = Advance(RP);
	}
	
	return LeftOprand;
}

Polynomial MultiPolynomial(const Polynomial LeftOprand, const Polynomial RightOprand)
{
	List R = RightOprand, L = LeftOprand;
	Position RP, LP, TmpCell;
	Polynomial Tmp;
		
	Tmp = (Polynomial)malloc(sizeof(Node));
	Tmp->Coefficient = 0;
	Tmp->Exponent = 0;
	Tmp->Next = NULL;

	RP = First(R);
	while (RP != NULL)
	{
		LP = First(L);
		while (LP != NULL)
		{
			Insert(LP->Exponent + RP->Exponent, Tmp, Tmp);
			TmpCell = First(Tmp);
			TmpCell->Coefficient = LP->Coefficient * RP->Coefficient;
			
			LP = Advance(LP);
		}
		RP = Advance(RP);
	}
	
	MergePolynomial(Tmp);
	
	return Tmp;
}

void MergePolynomial(Polynomial Poly)
{
	Polynomial Tmp;
		
	Tmp = (Polynomial)malloc(sizeof(Node));
	Tmp->Coefficient = 0;
	Tmp->Exponent = 0;
	Tmp->Next = NULL;
	
	AddPolynomial(Tmp, Poly);
	
	MakeEmpty(Poly);
	Poly->Next = Tmp->Next;
	free(Tmp);
}

void PrintPolynomial(Polynomial Poly)
{
	List L = Poly;
	Position P = First(L);
	
	while (P != NULL)
	{
		if (P->Coefficient != 0)
		{
			if (P->Coefficient == -1 && P == First(L))
				std::cout << "-";
			else
				if (abs(P->Coefficient) != 1)
					if (P == First(L))
						std::cout << P->Coefficient;
					else
						std::cout << abs(P->Coefficient);
			
			if (P->Exponent > 1)
				std::cout << "x^" << P->Exponent;
			else if (P->Exponent == 1)
				std::cout << "x";
			else if (P->Exponent < 0)
				std::cout << "x^(" << P->Exponent << ")";
		}
		
		if (P->Next != NULL && P->Next->Coefficient != 0)
		{
			if (P->Next->Coefficient < 0)
				std::cout << " - ";
			else std::cout << " + ";
		}
		
		P = Advance(P);
	}
	
	std::cout << std::endl;
}

#endif