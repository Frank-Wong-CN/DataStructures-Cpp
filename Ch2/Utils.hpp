#pragma once

#ifdef __CLING__
#define RecordTime(X) { \
		Log(LOG_INFO, "{}, N: {}, Starting to demonstrate...", __FUNCTION__, (X)); \
		Timer::On(); \
		Timer::N((X)); }
#define ShowTime(X) { \
		auto __tmp = (X); \
		Timer::Lap(); \
		Log(LOG_INFO, "Execution complete. Result: {}", __tmp); \
		return __tmp; }
#else
#define RecordTime(X)
#define ShowTime(X) return X;
#endif

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
