#pragma once

#include <ctime>
#include <climits>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>
#include <string>

#include <fmt/core.h>
#include <fmt/color.h>
#include <fmt/format.h>
#include <fmt/printf.h>

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

#if __cplusplus > 201907L
#define RequireArthimetic(T) requires std::is_arithmetic_v<T>
#else
#define RequireArthimetic(T)
#endif

inline void Mem16(void *addr, int len)
{
    int i;
    unsigned char buff[17];
    unsigned char *pc = (unsigned char*)addr;

    for (i = 0; i < len; i++) {
        if ((i % 16) == 0) {
            if (i != 0)
                fmt::print("  {}\n", buff);
            fmt::print("  {:04x} ", i);
        }
		
        fmt::print(" {:02x}", pc[i]);

        if ((pc[i] < 0x20) || (pc[i] > 0x7e)) {
            buff[i % 16] = '.';
        } else {
            buff[i % 16] = pc[i];
        }

        buff[(i % 16) + 1] = '\0';
    }

    while ((i % 16) != 0) {
        fmt::print("   ");
        i++;
    }

    fmt::print("  {}\n", buff);
}

struct __memBinRepresentationLittleEndian
{
	unsigned lower: 4;
	unsigned upper: 4;
};

inline void Mem2(void *addr, int len)
{
    int i;
    unsigned char buff[17];
    unsigned char *pc = (unsigned char*)addr;
	__memBinRepresentationLittleEndian rep;

    for (i = 0; i < len; i++) {
        if ((i % 4) == 0) {
            if (i != 0)
                fmt::print("  {}\n", buff);
            fmt::print("  {:04x} ", i);
        }
		
		memcpy(&rep, pc + i, 1);
        fmt::print(" {:04b} {:04b} ", ((unsigned char)rep.upper), ((unsigned char)rep.lower));

        if ((pc[i] < 0x20) || (pc[i] > 0x7e)) {
            buff[i % 4] = '.';
        } else {
            buff[i % 4] = pc[i];
        }

        buff[(i % 4) + 1] = '\0';
    }
	/*
    while ((i % 16) != 0) {
        fmt::print("   ");
        i++;
    }
	*/
    fmt::print("  {}\n", buff);
}

enum ErrorLevel {
	LOG_FATAL,
	LOG_ERROR,
	LOG_WARNING,
	LOG_INFO,
	LOG_DEBUG
};

template <typename S, typename... Args>
void __Log(const char *file, int line, ErrorLevel lv, const S& str, Args&&... args)
{
	switch (lv)
	{
	case LOG_FATAL:
		fmt::print(fg(fmt::rgb(255, 24, 24)), "[FATAL] ");
		break;
	case LOG_ERROR:
		fmt::print(fg(fmt::rgb(255, 24, 24)), "[ERROR] ");
		break;
	case LOG_WARNING:
		fmt::print(fg(fmt::color::yellow), "[WARNING] ");
		break;
	case LOG_INFO:
		fmt::print("[INFO] ");
		break;
	case LOG_DEBUG:
		fmt::print(fg(fmt::color::aqua), "[DEBUG] ");
		break;
	}
	
	fmt::print("{}, {}: ", file, line);
	fmt::vprint(str, fmt::make_args_checked<Args...>(str, args...));
	fmt::print("\n");
	
	if (lv == LOG_FATAL)
		exit(0);
}

#define Log(lv, str, ...) \
	__Log(__FILE__, __LINE__, lv, FMT_STRING(str), __VA_ARGS__)

namespace Timer
{
	struct __algorithmTimeRecord
	{
		std::chrono::time_point<std::chrono::steady_clock> start;
		long N = 0; // Manually set
		
		__algorithmTimeRecord() : start(std::chrono::steady_clock::now()), N(0) {}
	};

	static __algorithmTimeRecord *__execTimer;

	inline void On(__algorithmTimeRecord **timer = &__execTimer)
	{
		if (*timer != nullptr)
			delete *timer;
		
		*timer = new __algorithmTimeRecord();
	}

	inline void Lap(__algorithmTimeRecord *timer = __execTimer)
	{
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - timer->start).count();
		std::cout << "???????????????????????????????????????????????????????????????????????????????????????????????????????????????\n";
		std::cout << "???" << std::setw(10) << "Time" << "???" << std::setw(24) << std::fixed << duration << "???\n";
		
		long N = timer->N;
		if (N > 0)
		{
			std::cout	<< "???????????????????????????????????????????????????????????????????????????????????????????????????????????????\n"
						<< std::setprecision(18)
				<< "???" << std::setw(10) << "T/LogN"		<< "???" << std::setw(24) << std::fixed << (double)duration / log(N)				<< "???\n"
				<< "???" << std::setw(10) << "T/N" 		<< "???" << std::setw(24) << std::fixed << (double)duration / (double)N			<< "???\n"
				<< "???" << std::setw(10) << "T/NLogN"	<< "???" << std::setw(24) << std::fixed << (double)duration / (double)N / log(N)	<< "???\n"
				<< "???" << std::setw(10) << "T/N^2"		<< "???" << std::setw(24) << std::fixed << (double)duration / pow(N, 2)			<< "???\n"
				<< "???" << std::setw(10) << "T/N^3"		<< "???" << std::setw(24) << std::fixed << (double)duration / pow(N, 3)			<< "???\n"
				<< "???" << std::setw(10) << "T/2^N"		<< "???" << std::setw(24) << std::fixed << (double)duration / pow(2, N)			<< "???\n";
		}
		
		std::cout << "???????????????????????????????????????????????????????????????????????????????????????????????????????????????\n";
	}

	inline void N(int n, __algorithmTimeRecord *timer = __execTimer)
	{
		timer->N = n;
	}
}

namespace RdGen
{
	static std::random_device __rd;
	static std::mt19937 __rdEngine(__rd());
	
	template <typename T> RequireArthimetic(T)
	T Random(T min, T max)
	{
		if (std::is_integral_v<T>)
		{
			std::uniform_int_distribution<> rd(min, max);
			return rd(__rdEngine);
		}
		if (std::is_floating_point_v<T>)
		{
			std::uniform_real_distribution<> rd(min, max);
			return rd(__rdEngine);
		}
	}
	
	template <typename T> RequireArthimetic(T)
	T *ArrGen(size_t size, T min, T max)
	{
		T *arr = (T *)malloc(sizeof(T) * size);
		for (size_t i = 0; i < size; i++)
			arr[i] = Random(min, max);
		
		return arr; // Remember to free tho
	}
	
	template <typename T>
	void SaveArray(std::string fname, T *arr, size_t size)
	{	
		std::ofstream txtFile(fname, std::ios_base::out);
		for (int i = 0; i < size; i++)
			txtFile << arr[i] << "\n";
		txtFile.close();
	}
	
	template <typename T>
	void LoadArray(std::string fname, T *arr, size_t size)
	{	
		std::ifstream txtFile(fname, std::ios_base::in);
		for (int i = 0; i < size; i++)
			txtFile >> arr[i];
		txtFile.close();
	}
}
