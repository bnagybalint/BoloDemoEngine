#pragma once

#include "Assist/Common.h"

#include "Assist/Tuple.h"

// Delegate class
//
// Class to store a callback function. Delegates can hold any function, whose 
// signature (return value and parameter list) matches that of the delegate.
//
// Syntax: Delegate<R(T1,T2)> can hold a function that takes arguments with 
// type T1 and T2 and returns an a value of type R.
//
// The same delegates can hold a global function or a class member method 
// with the same signature.
//
// Usage example:
//
//    void globalFunc() {...}
//    float globalFunc2(int a) {...}
//    class SomeClass { void memberFunc(int a) {...} };
//
//    // ...
//
//    // Definition:
//    SomeClass* s;
//    Delegate<void()>     d1 = Delegate<void()>( &globalFunc );
//    Delegate<float(int)> d2 = Delegate<float(int)>( &globalFunc2 );
//    Delegate<float(int)> d3 = Delegate<float(int)>( s, &SomeClass::memberFunc );
// 
//    // Invocation:
//    d1();
//    d2(42);
//    float r3 = d3(1);
// 
// -------------------------------


// Forward declare empty templates
template<typename>          class AbstractCallback;
template<typename>          class StaticCallback;
template<typename,typename> class MethodCallback;
template<typename>          class Delegate;
template<typename>          class Callback;

// ----------------
// Class: CallbackBase
// Template-free base class for Callback, to be able to store them in heterogeneous containers.
//
class CallbackBase {
public:
	virtual ~CallbackBase() {}

	// Invoke callback.
	// Note: Return type is inaccessible.
	virtual void call() = 0;
};

#define DLG_TEMPLATE_LIST             
#define DLG_PARAMETER_LIST            
#define DLG_TYPE_LIST                 
#define DLG_ARGUMENT_LIST             
#define DLG_PARAMETER_LIST_WITH_COMMA 
#define DLG_ARGUMENT_LIST_TUPLE(var)  
#include "Assist/impl/delegate/DelegateImpl.h"
#undef  DLG_TEMPLATE_LIST             
#undef  DLG_TYPE_LIST                 
#undef  DLG_PARAMETER_LIST            
#undef  DLG_ARGUMENT_LIST             
#undef  DLG_PARAMETER_LIST_WITH_COMMA 
#undef  DLG_ARGUMENT_LIST_TUPLE       

#define DLG_TEMPLATE_LIST             , typename ArgType1
#define DLG_PARAMETER_LIST            ArgType1 a1
#define DLG_TYPE_LIST                 ArgType1
#define DLG_ARGUMENT_LIST             a1
#define DLG_PARAMETER_LIST_WITH_COMMA , ArgType1 a1
#define DLG_ARGUMENT_LIST_TUPLE(var)  std::get<0>(var)
#include "Assist/impl/delegate/DelegateImpl.h"
#undef  DLG_TEMPLATE_LIST             
#undef  DLG_TYPE_LIST                 
#undef  DLG_PARAMETER_LIST            
#undef  DLG_ARGUMENT_LIST              
#undef  DLG_PARAMETER_LIST_WITH_COMMA 
#undef  DLG_ARGUMENT_LIST_TUPLE       

#define DLG_TEMPLATE_LIST             , typename ArgType1, typename ArgType2
#define DLG_PARAMETER_LIST            ArgType1 a1, ArgType2 a2
#define DLG_TYPE_LIST                 ArgType1, ArgType2
#define DLG_ARGUMENT_LIST             a1, a2
#define DLG_PARAMETER_LIST_WITH_COMMA , ArgType1 a1, ArgType2 a2
#define DLG_ARGUMENT_LIST_TUPLE(var)  std::get<0>(var), std::get<1>(var)
#include "Assist/impl/delegate/DelegateImpl.h"
#undef  DLG_TEMPLATE_LIST             
#undef  DLG_TYPE_LIST                 
#undef  DLG_PARAMETER_LIST            
#undef  DLG_ARGUMENT_LIST             
#undef  DLG_PARAMETER_LIST_WITH_COMMA 
#undef  DLG_ARGUMENT_LIST_TUPLE       

#define DLG_TEMPLATE_LIST             , typename ArgType1, typename ArgType2, typename ArgType3
#define DLG_PARAMETER_LIST            ArgType1 a1, ArgType2 a2, ArgType3 a3
#define DLG_TYPE_LIST                 ArgType1, ArgType2, ArgType3
#define DLG_ARGUMENT_LIST             a1, a2, a3
#define DLG_PARAMETER_LIST_WITH_COMMA , ArgType1 a1, ArgType2 a2, ArgType3 a3
#define DLG_ARGUMENT_LIST_TUPLE(var)  std::get<0>(var), std::get<1>(var), std::get<3>(var)
#include "Assist/impl/delegate/DelegateImpl.h"
#undef  DLG_TEMPLATE_LIST             
#undef  DLG_TYPE_LIST                 
#undef  DLG_PARAMETER_LIST            
#undef  DLG_ARGUMENT_LIST             
#undef  DLG_PARAMETER_LIST_WITH_COMMA 
#undef  DLG_ARGUMENT_LIST_TUPLE       

#define DLG_TEMPLATE_LIST             , typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4
#define DLG_PARAMETER_LIST            ArgType1 a1, ArgType2 a2, ArgType3 a3, ArgType4 a4
#define DLG_TYPE_LIST                 ArgType1, ArgType2, ArgType3, ArgType4
#define DLG_ARGUMENT_LIST             a1, a2, a3, a4
#define DLG_PARAMETER_LIST_WITH_COMMA , ArgType1 a1, ArgType2 a2
#define DLG_ARGUMENT_LIST_TUPLE(var)  std::get<0>(var), std::get<1>(var), std::get<2>(var), std::get<3>(var)
#include "Assist/impl/delegate/DelegateImpl.h"
#undef  DLG_TEMPLATE_LIST             
#undef  DLG_TYPE_LIST                 
#undef  DLG_PARAMETER_LIST            
#undef  DLG_ARGUMENT_LIST             
#undef  DLG_PARAMETER_LIST_WITH_COMMA 
#undef  DLG_ARGUMENT_LIST_TUPLE       
