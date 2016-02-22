#pragma once

#include "Assist/Common.h"

#if BDE_RENDER_DX_DEBUG
# define D2D_SafeCall( call ) Assert( !FAILED(call) )
#else
# define D2D_SafeCall( call ) call
#endif
