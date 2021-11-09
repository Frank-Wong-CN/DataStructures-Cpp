#ifndef _COMMON_H
#define _COMMON_H

//#ifdef __CLING__
//	#define __StrClingOutput(PrintfVer, FmtVer, ...) fmt::print(FmtVer, __VA_ARGS__)
//	#ifdef __STR_OUTPUT__
//		#define D(...) fmt::print(__VA_ARGS__)
//	#else
//		#define D(...)
//	#endif
//#else
	#define __StrClingOutput(PrintfVer, FmtVer, ...) printf(PrintfVer, __VA_ARGS__)
	#define D(...)
//#endif

void FatalError(const char *error)
{
	printf("[ERROR] %s\n", error);
	abort();
}

int MaxI32(int a, int b)
{
	return (a > b ? a : b);
}

inline int Min(int a, int b)
{
	return (a < b ? a : b);
}

inline int Max(int a, int b)
{
	return (a > b ? a : b);
}

inline int Max3(int a, int b, int c)
{
	return (a > b ? (a > c ? a : c) : (b > c ? b : c));
}

inline void Swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

#endif