#ifndef _MNODE_IMPL_
#define _MNODE_IMPL_
#define _MNODE_IMPL_BASIC

struct _MatrixElement
{
	ElementType Element;
	Matrix Next; // Matrices should at least be 1-dimensional
};

#endif