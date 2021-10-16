#ifndef _MNODE_H
#define _MNODE_H

#define SizeType unsigned int
#define DimensionRange unsigned int

struct _MatrixData;
typedef _MatrixData MatrixData, *PMatrixData;

typedef List Matrix;
typedef PMatrixData MatrixHeader;

enum MatrixType
{
	King, // The head of the Matrix
	Queen, // Header which was a king, but became an reflection of another dimension
	Rook, // Header of a single dimension
	Pawn // Actual data, but should not be used
};

struct _MatrixData
{
	MatrixType Type;
	List NextInDimension; // At least 2 rooks and many queens
	SizeType Size[3]; // Pawn, Rook, Queen
};

#endif