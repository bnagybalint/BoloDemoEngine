
#define TEST 1

#if TEST==0
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#else
// struct Memory
// {
// // 	template<class T>
// // 	static void Swap(T& a, T& b);
// 
// 	static void Memcopy(void* dst, const void* src, size_t numBytes);
// 	static void Memset(void* dst, unsigned char data, size_t numBytes);
// 	static void Memzero(void* dst, size_t numBytes);
// };
// 
// /*static*/void Memory::Memcopy(void* dst, const void* src, size_t numBytes)
// {
// 	unsigned char* d = (unsigned char*)dst;
// 	const unsigned char* s = (const unsigned char*)src;
// 	while (numBytes--)
// 		*d++ = *s++;
// }
// /*static*/void Memory::Memset(void* dst, unsigned char data, size_t numBytes)
// {
// 	unsigned char* d = (unsigned char*)dst;
// 	while (numBytes--)
// 		*d++ = data;
// }
// /*static*/void Memory::Memzero(void* dst, size_t numBytes)
// {
// 	Memory::Memset(dst, 0x00, numBytes);
// }
#endif

//#include <stdio.h>

int main()
{
	const int N = 8;
	int arr[N] = { 10, 31, 324, 563, 3, 122, 2342, 2 };
	volatile int* arr2 = new int[N];
#if TEST==0
	memcpy((void*)arr2,arr,N*sizeof(int));
#else
	//Memory::Memcopy((void*)arr2, arr, N*sizeof(int));
#endif
	//printf("Elements: \n  ");
	for (int i = 0; i < N; i++)
	{
		//printf("%d ", arr2[i]);
	}
	//printf("\n");
	return 0;
}