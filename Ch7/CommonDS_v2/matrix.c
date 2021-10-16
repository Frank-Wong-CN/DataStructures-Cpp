#include "matrix.h"

MatrixHeader __MatData(Matrix M)
{
	return (MatrixHeader)M->Element;
}

void __Matrix_DestroyDimension(Matrix M, DimensionRange D);
int __Matrix_EnforceConnection(Matrix M);
Matrix __Matrix_CheckMissingConnection(Matrix M);

Matrix __Matrix_InsertSingle(Matrix M, Matrix N)
{
	MatrixType *Type = &(__MatData(N)->Type);
	MatrixHeader Head = __MatData(M);
	
	if (*Type == Pawn)
	{}
	else
	{
		if (Head->Size[1] < 2)
			*Type = Rook;
		// ?
	}
}

Matrix CreateSingleMatrix(MatrixType T)
{
	Matrix M = (Matrix)CreateList();
	
	if (T != Pawn)
	{
		MatrixHeader H = (MatrixHeader)malloc(sizeof(MatrixData));
		memset(H, 0, sizeof(MatrixData))
		H->Type = T;
		M->Element = (void *)H;
	}
	
	return M;
}

Matrix CreateMatrix(DimensionRange D, ...)
{
	Matrix N, M = CreateSingleMatrix(King);
	List NextArray = NULL;
	int i = 0, DSize = 0;
	
	if (DimensionRange <= 1)
		return M;
	else
	{
		NextArray = CreateList();
		__MatData(M)->NextInDimension = NextArray;
		
		va_list Args;
		va_start(Args, D);
		
		for (i = 0; i < D; i++)
		{
			if (i < 2)
				N = CreateSingleMatrix(Rook);
			else
			{
				N = CloneMatrix(M, 0);
				__MatData(N)->Type = Queen;
			}
			
			__Matrix_InsertSingle(M, N);
		}
	}
}

Matrix CloneMatrix(Matrix M, DimensionRange D, ...);
Matrix Find(ElementType X, Matrix M);
Matrix MatrixAt(Matrix M, ...);
SizeType MatrixWidth(Matrix M);
SizeType MatrixHeight(Matrix M);
int IsSquareMatrix(Matrix M);
Matrix MatrixYield(Matrix M, DimensionRange X, ...);

Matrix MatrixResize(Matrix M, ...);
Matrix MatrixInsert(Matrix M, ElementType X, ...);
Matrix MatrixAppend(Matrix M, ElementType X, DimensionRange D);
void MatrixRemoveByValue(Matrix M, ElementType X);
void MatrixRemoveByElement(Matrix M, Matrix X);
void ClearMatrix(Matrix X);
void DestroyMatrix(Matrix *M);