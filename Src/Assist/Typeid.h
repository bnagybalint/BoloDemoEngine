#pragma once

#include "Assist/Common.h"
#include "Assist/UIDGenerator.h"

// NOTE:
// - not thread-safe (TODO?)
// - not type-safe (not protected against using T and T*)
template <class T>
struct Typeid
{
	static uint64 value()
	{
		static uint64 id = UIDGenerator::getInstance()->generate();
		return id;
	}
};

// Macros to define type hierarchy for runtime type ID comparisons that work across the class hierarchy
// Use:
//  SomeClass* s = new SomeDerivedClass();
//  if( s->isa<SomeDerivedClass>() ); // true
#define DECLARE_TYPE_BASETYPE(className) \
	protected: virtual bool isaVirt(uint64 tid) { return Typeid<className>::value() == tid; } \
	public: template<class T> bool isa() { return isaVirt(Typeid<T>::value()); }

#define DECLARE_TYPE_INHERITANCE(className, parentClassName) \
	protected: virtual bool isaVirt(uint64 tid) override \
		{ \
			if( Typeid<className>::value() == tid ) return true; \
			return parentClassName::isaVirt(tid); \
		}
#define DECLARE_TYPE_INHERITANCE2(className, parentClassName1, parentClassName2) \
	protected: virtual bool isaVirt(uint64 tid) override \
		{ \
			if( Typeid<className>::value() == tid ) return true; \
			return (parentClassName2::isaVirt(tid)) || (parentClassName1::isaVirt(tid)); \
		}




