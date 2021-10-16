#ifndef _MATRIX_H
#define _MATRIX_H

#include "mnode.h"

#include <stdarg.h>

Matrix CreateSingleMatrix(MatrixType T);
Matrix CreateMatrix(DimensionRange D, ...);
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

#endif