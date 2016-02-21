#include "RenderCommon.h"

void* RenderAlloc(size_t numBytes) {
	return _aligned_malloc(numBytes, 16);
}

void RenderDealloc(void* ptr) {
	return _aligned_free(ptr);
}
