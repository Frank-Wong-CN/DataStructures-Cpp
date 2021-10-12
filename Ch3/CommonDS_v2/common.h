#ifndef _COMMON_H
#define _COMMON_H

void FatalError(const char *error)
{
	printf("[ERROR] %s\n", error);
	abort();
}

int MaxI32(int a, int b)
{
	return (a > b ? a : b);
}

#endif