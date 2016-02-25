#pragma once

#include "Assist/Common.h"

// Forward declare empty templates
template<typename>          class AbstractCallback;
template<typename>          class StaticCallback;
template<typename,typename> class MethodCallback;
template<typename>          class Delegate;

#define DLG_TEMPLATE_LIST  
#define DLG_PARAMETER_LIST 
#define DLG_TYPE_LIST      
#define DLG_ARGUMENT_LIST  
#include "Assist/impl/delegate/DelegateImpl.h"
#undef  DLG_TEMPLATE_LIST 
#undef  DLG_TYPE_LIST     
#undef  DLG_PARAMETER_LIST
#undef  DLG_ARGUMENT_LIST 

#define DLG_TEMPLATE_LIST  , typename ArgType1
#define DLG_PARAMETER_LIST ArgType1 a1
#define DLG_TYPE_LIST      ArgType1
#define DLG_ARGUMENT_LIST  a1
#include "Assist/impl/delegate/DelegateImpl.h"
#undef  DLG_TEMPLATE_LIST 
#undef  DLG_TYPE_LIST     
#undef  DLG_PARAMETER_LIST
#undef  DLG_ARGUMENT_LIST 

#define DLG_TEMPLATE_LIST  , typename ArgType1, typename ArgType2
#define DLG_PARAMETER_LIST ArgType1 a1, ArgType2 a2
#define DLG_TYPE_LIST      ArgType1, ArgType2
#define DLG_ARGUMENT_LIST  a1, a2
#include "Assist/impl/delegate/DelegateImpl.h"
#undef  DLG_TEMPLATE_LIST 
#undef  DLG_TYPE_LIST     
#undef  DLG_PARAMETER_LIST
#undef  DLG_ARGUMENT_LIST 

#define DLG_TEMPLATE_LIST  , typename ArgType1, typename ArgType2, typename ArgType3
#define DLG_PARAMETER_LIST ArgType1 a1, ArgType2 a2, ArgType3 a3
#define DLG_TYPE_LIST      ArgType1, ArgType2, ArgType3
#define DLG_ARGUMENT_LIST  a1, a2, a3
#include "Assist/impl/delegate/DelegateImpl.h"
#undef  DLG_TEMPLATE_LIST 
#undef  DLG_TYPE_LIST     
#undef  DLG_PARAMETER_LIST
#undef  DLG_ARGUMENT_LIST 

#define DLG_TEMPLATE_LIST  , typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4
#define DLG_PARAMETER_LIST ArgType1 a1, ArgType2 a2, ArgType3 a3, ArgType4 a4
#define DLG_TYPE_LIST      ArgType1, ArgType2, ArgType3, ArgType4
#define DLG_ARGUMENT_LIST  a1, a2, a3, a4
#include "Assist/impl/delegate/DelegateImpl.h"
#undef  DLG_TEMPLATE_LIST 
#undef  DLG_TYPE_LIST     
#undef  DLG_PARAMETER_LIST
#undef  DLG_ARGUMENT_LIST 
