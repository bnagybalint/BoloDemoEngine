#pragma once

#include "Assist/Common.h"
#include "Assist/UIDGenerator.h"

typedef uint64 TypeID;
const TypeID INVALID_TYPEID = 0;

// NOTE: not thread-safe (TODO?)
// NOTE: T and T* are different types
template <class T>
TypeID GetTypeId()
{
	static TypeID id = UIDGenerator::getInstance()->generate();
	return id;
}
template <class T>
TypeID GetTypeId(const T& item)
{
	return GetTypeId<T>();
}

// Macros to define type hierarchy for runtime type ID comparisons that work across the class hierarchy
// Use:
//  SomeClass* s = new SomeDerivedClass();
//  if( s->isa<SomeDerivedClass>() ); // true
#define DECLARE_TYPE_BASETYPE(className) \
	protected: virtual bool isaVirt(TypeID tid) { return GetTypeId<className>() == tid; } \
	public: template<class T> bool isa() { return isaVirt(GetTypeId<T>()); } \
	public: virtual bool isa(const char* typeString) { return strcmp(typeString, STRINGIFY(className)) == 0; }

#define DECLARE_TYPE_INHERITANCE(className, parentClassName) \
	protected: virtual bool isaVirt(TypeID tid) override \
		{ \
			if( GetTypeId<className>() == tid ) return true; \
			return parentClassName::isaVirt(tid); \
		} \
	public: virtual bool isa(const char* typeString) override { return strcmp(typeString, STRINGIFY(className)) == 0 || parentClassName::isa(typeString); }
#define DECLARE_TYPE_INHERITANCE2(className, parentClassName1, parentClassName2) \
	protected: virtual bool isaVirt(TypeID tid) override \
		{ \
			if( GetTypeId<className>() == tid ) return true; \
			return (parentClassName2::isaVirt(tid)) || (parentClassName1::isaVirt(tid)); \
		} \
	public: virtual bool isa(const char* typeString) override { return strcmp(typeString, STRINGIFY(className)) == 0 || parentClassName1::isa(typeString) || parentClassName2::isa(typeString); }




