#include "stdafx.h"
#include "xallocator.h"
#include "Fault.h"
#include <new>
#include <iostream>
#include <stdio.h>
#include <string.h>

// On VisualStudio, to disable the debug heap for faster performance when using
// the debugger use this option:
// Debugging > Environment _NO_DEBUG_HEAP=1

class MyClass
{
	XALLOCATOR
	// remaining class definition
};

class MyClassStatic
{
public:
	MyClassStatic() { memory = xmalloc(100); }
	~MyClassStatic() { xfree(memory); }
private:
	void* memory;
};
static MyClassStatic myClassStatic;

static void out_of_memory()
{
	// new-handler function called by Allocator when pool is out of memory
	ASSERT();
}

static const int MAX_BLOCK_SIZE = 4000;
static const int MAX_ALLOCATIONS = 10000;
static void* memoryPtrs[MAX_ALLOCATIONS];
static void* memoryPtrs2[MAX_ALLOCATIONS];

typedef void* (*AllocFunc)(size_t size);
typedef void (*DeallocFunc)(void* ptr);
void Benchmark(const char* name, AllocFunc allocFunc, DeallocFunc deallocFunc);

//------------------------------------------------------------------------------
// _tmain
//------------------------------------------------------------------------------
int xallocator_test(void)
{
	srand(1);
	std::set_new_handler(out_of_memory);

//    printf("Hier 1\n");
	xalloc_stats();
//    printf("Hier 2\n");

	// If AUTOMATIC_XALLOCATOR_INIT_DESTROY defined then XallocInitDestroy() will
	// call xalloc_init() automatically before main().
	//xalloc_init();

	// Allocate MyClass using fixed block allocator
	MyClass* myClass = new MyClass();
	delete myClass;

	void* memory1 = xmalloc(100);
	xfree(memory1);

	char* memory2 = (char*)xmalloc(24);
	strcpy(memory2, "TEST STRING");
	memory2 = (char*)xrealloc(memory2, 124);
	xfree(memory2);

	// Benchmark will cause out_of_memory to be called if STATIC_POOLS defined
	Benchmark("malloc/free (Run 1)", malloc, free);
	Benchmark("malloc/free (Run 2)", malloc, free);
	Benchmark("malloc/free (Run 3)", malloc, free);
	Benchmark("xmalloc/xfree (Run 1)", xmalloc, xfree);
	Benchmark("xmalloc/xfree (Run 2)", xmalloc, xfree);
	Benchmark("xmalloc/xfree (Run 3)", xmalloc, xfree);

//    printf("Hier 3\n");
	xalloc_stats();
//    printf("Hier 4\n");

	// If AUTOMATIC_XALLOCATOR_INIT_DESTROY is defined, ~XallocDestroy() will call
	// xalloc_destroy() automatically. Never call xalloc_destroy() manually except if
	// using xallocator in a C-only application.
	//xalloc_destroy();
	return 0;
}

//------------------------------------------------------------------------------
// Benchmark
//------------------------------------------------------------------------------
#include <winsock2.h>
#include <psapi.h>
void Benchmark(const char* name, AllocFunc allocFunc, DeallocFunc deallocFunc)
{
//#if WIN32
	LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds, TotalElapsedMicroseconds= {0};
	LARGE_INTEGER Frequency;

	SetProcessPriorityBoost(GetCurrentProcess(), true);

	QueryPerformanceFrequency(&Frequency);

	// Allocate MAX_ALLOCATIONS blocks MAX_BLOCK_SIZE / 2 sized blocks
	QueryPerformanceCounter(&StartingTime);
	for (int i=0; i<MAX_ALLOCATIONS; i++)
		memoryPtrs[i] = allocFunc(MAX_BLOCK_SIZE / 2);

	QueryPerformanceCounter(&EndingTime);
	ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
	ElapsedMicroseconds.QuadPart *= 1000000;
	ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;
	std::cout << name << " allocate time: " << ElapsedMicroseconds.QuadPart << std::endl;
	TotalElapsedMicroseconds.QuadPart += ElapsedMicroseconds.QuadPart;

	// Deallocate MAX_ALLOCATIONS blocks (every other one)
	QueryPerformanceCounter(&StartingTime);
	for (int i=0; i<MAX_ALLOCATIONS; i+=2)
		deallocFunc(memoryPtrs[i]);
	QueryPerformanceCounter(&EndingTime);
	ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
	ElapsedMicroseconds.QuadPart *= 1000000;
	ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;
	std::cout << name << " deallocate time: " << ElapsedMicroseconds.QuadPart << std::endl;
	TotalElapsedMicroseconds.QuadPart += ElapsedMicroseconds.QuadPart;

	// Allocate MAX_ALLOCATIONS blocks MAX_BLOCK_SIZE sized blocks
	QueryPerformanceCounter(&StartingTime);
	for (int i=0; i<MAX_ALLOCATIONS; i++)
		memoryPtrs2[i] = allocFunc(MAX_BLOCK_SIZE);
	QueryPerformanceCounter(&EndingTime);
	ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
	ElapsedMicroseconds.QuadPart *= 1000000;
	ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;
	std::cout << name << " allocate time: " << ElapsedMicroseconds.QuadPart << std::endl;
	TotalElapsedMicroseconds.QuadPart += ElapsedMicroseconds.QuadPart;

	// Deallocate MAX_ALLOCATIONS blocks (every other one)
	QueryPerformanceCounter(&StartingTime);
	for (int i=1; i<MAX_ALLOCATIONS; i+=2)
		deallocFunc(memoryPtrs[i]);
	QueryPerformanceCounter(&EndingTime);
	ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
	ElapsedMicroseconds.QuadPart *= 1000000;
	ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;
	std::cout << name << " deallocate time: " << ElapsedMicroseconds.QuadPart << std::endl;
	TotalElapsedMicroseconds.QuadPart += ElapsedMicroseconds.QuadPart;

	// Deallocate MAX_ALLOCATIONS blocks
	QueryPerformanceCounter(&StartingTime);
	for (int i=MAX_ALLOCATIONS-1; i>=0; i--)
		deallocFunc(memoryPtrs2[i]);
	QueryPerformanceCounter(&EndingTime);
	ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
	ElapsedMicroseconds.QuadPart *= 1000000;
	ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;
	std::cout << name << " deallocate time: " << ElapsedMicroseconds.QuadPart << std::endl;
	TotalElapsedMicroseconds.QuadPart += ElapsedMicroseconds.QuadPart;

	std::cout << name << " TOTAL TIME: " << TotalElapsedMicroseconds.QuadPart << std::endl;

	SetProcessPriorityBoost(GetCurrentProcess(), false);
//#endif
}


