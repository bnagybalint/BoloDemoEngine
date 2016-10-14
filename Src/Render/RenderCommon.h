#pragma once

#include "Assist/Common.h"

#include <new>

// ----- DirectX includes ----- 

// #ifndef WIN32_LEAN_AND_MEAN
// #define WIN32_LEAN_AND_MEAN
// #endif
// #include <directxmath.h>

// ----- Debug related stuff ----- 

#if BDE_RENDER_DX_DEBUG
# define DX_SafeCall( call ) Assert( !FAILED(call) )
// # define DX_SafeCall( call ) \
// 	do { \
// 		HRESULT hr = call; \
// 		if(FAILED(hr)) { \
// 			fprintf(stderr, "ERROR: ###  DX render engine call failed.\n"); \
// 			fprintf(stderr, "ERROR: # Call: %s\n", #call); \
// 			fprintf(stderr, "ERROR: # Description:\n"); \
// 			fprintf(stderr, "%s", RenderManager::getInstance()->getErrors("ERROR: #    ")); \
// 			Assert(false); \
// 		} \
// 	} while(false)
#else
# define DX_SafeCall( call ) call
#endif

// ----- Custom allocation for render ----- 

void* RenderAlloc(size_t numBytes);
void RenderDealloc(void* ptr);

#define RENDER_NEW(Type)               new (RenderAlloc(sizeof(Type))) Type
#define RENDER_NEW_ARRAY(Type)         Unimplemented()
#define RENDER_DELETE(ptr, Type)       if(ptr) { (ptr)->~Type(); RenderDealloc(ptr); }
#define RENDER_DELETE_ARRAY(ptr, Type) Unimplemented()

