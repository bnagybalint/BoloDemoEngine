#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <stdint.h>

// ----- Import solution build settings ----- 

#include "Assist/SolutionBuildConfig.h"

// ----- Basic stuff ----- 

#ifndef NULL
#define NULL 0
#endif

// ----- Types ----- 

// fixed width integers
typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef int8_t  int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8 ubyte;

// ----- Assert ----- 

void RuntimeAssert(bool cond);
#ifdef BDE_GLOBAL_BUILD_DEBUG
# define Assert( cond ) RuntimeAssert( !!(cond) )
# define AssertMsg( cond, msg ) Assert( cond )
//# define AssertMsg( cond, msg ) do { String s = (msg); OutputDebugString( s.cstr() ); Assert( cond ); } while(false)
#else
# define Assert( cond )
# define AssertMsg( cond, msg )
#endif

#define Unimplemented() Assert(false);
#define Unsupported() Assert(false);

// ----- Debug mode related stuff ----- 

#ifdef BDE_GLOBAL_BUILD_DEBUG
#define IF_DEBUG(expr) expr
#else
#define IF_DEBUG(expr)
#endif

// ----- Force inline ----- 

#define ForceInline __forceinline

// ----- WINAPI related stuff ----- 

#ifdef BDE_GLOBAL_BUILD_DEBUG
# define SafeCall( call ) Assert( !FAILED(call) )
#else
# define SafeCall( call ) call
#endif

// ----- Enum class ----- 

#define EnumBegin( name, defval ) \
	struct name { \
		public:  enum enumtype_; \
		public:  typedef enumtype_ Type; \
		private: enumtype_ val_; \
		public:  name() :val_( defval ) {} \
		public:  name( enumtype_ val ) :val_(val) {} \
		public:  operator enumtype_ () const { return val_; } \
		public:  bool operator == (enumtype_ e) const { return e == val_; } \
		public:  bool operator != (enumtype_ e) const { return e != val_; } \
		public:  enum enumtype_ {
#define EnumEnd(name) \
		}; \
	};

// ----- Singleton class helper ----- 

#define DECLARE_SINGLETON_HEADER(ClassName) \
	private: static ClassName* _msInstance; \
	public:  static void createSingletonInstance(); \
	public:  static void destroySingletonInstance(); \
	public:  static ClassName* getInstance();

#define DEFINE_SINGLETON_IMPL(ClassName) \
	ClassName* ClassName::_msInstance = NULL; \
	void ClassName::createSingletonInstance() { Assert(_msInstance == NULL); _msInstance = new ClassName(); } \
	void ClassName::destroySingletonInstance() { Assert(_msInstance); delete _msInstance; _msInstance = NULL; } \
	ClassName* ClassName::getInstance() { Assert(_msInstance); return _msInstance; }

#define DISABLE_COPY(ClassName) \
	DISABLE_COPY_CONSTRUCT(ClassName); \
	DISABLE_COPY_OPERATOR(ClassName);
#define DISABLE_COPY_CONSTRUCT(ClassName) ClassName(const ClassName& other) = delete;
#define DISABLE_COPY_OPERATOR(ClassName) ClassName& operator = (const ClassName& other) = delete;
