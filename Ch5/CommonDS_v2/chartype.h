#ifndef __CHARTYPE_H_
#define __CHARTYPE_H_

typedef char CharType;

size_t CharArrayLen(const CharType *Arr)
{
	if (Arr == NULL)
		return -1;
	
	size_t Size = 0;
	while (*Arr++)
		Size += 1;
	
	return Size;
}

int CharArrayCmp(const CharType *A, const CharType *B)
{
	while (*A && (*A == *B))
		A++, B++;
	
	return (*A > *B) - (*A < *B);
}

#endif