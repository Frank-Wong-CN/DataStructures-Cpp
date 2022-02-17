#ifndef DSV2_COMMON_H
#define DSV2_COMMON_H

#ifdef _WIN64
#define CommonDS_v2_SizeType unsigned long long
#define CommonDS_v2_Pointer void *
#define CommonDS_v2_PointerSize unsigned long long
#define CommonDS_v2_PointerSize_Signed signed long long
#else
#define CommonDS_v2_SizeType unsigned int
#define CommonDS_v2_Pointer void *
#define CommonDS_v2_PointerSize unsigned int
#define CommonDS_v2_PointerSize_Signed signed int
#endif

#include <stdio.h> // printf
#include <stdlib.h> // abort
#include <string.h> // memset
#include <stddef.h> // offsetof

void FatalError(const char *error)
{
	printf("[ERROR] %s\n", error);
	abort();
}

CommonDS_v2_PointerSize_Signed Abs(CommonDS_v2_PointerSize_Signed a)
{
	return (a > 0 ? a : -a);
}

CommonDS_v2_SizeType Min(CommonDS_v2_SizeType a, CommonDS_v2_SizeType b)
{
	return (a < b ? a : b);
}

CommonDS_v2_SizeType Max(CommonDS_v2_SizeType a, CommonDS_v2_SizeType b)
{
	return (a > b ? a : b);
}

CommonDS_v2_SizeType Max3(CommonDS_v2_SizeType a, CommonDS_v2_SizeType b, CommonDS_v2_SizeType c)
{
	return (a > b ? (a > c ? a : c) : (b > c ? b : c));
}

void Swap(CommonDS_v2_SizeType *a, CommonDS_v2_SizeType *b)
{
	CommonDS_v2_SizeType tmp = *a;
	*a = *b;
	*b = tmp;
}

#endif