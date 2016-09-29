#include "MathCommon.h"

#include "Assist/Common.h"

// TODO Can this be avoided? As far as my research got, there is no way not 
// to use stdlib math intrinsics. Further investigation needed.
#include <cmath>

/*static*/const Coordtype Math::B_PI        = Coordtype(3.141592653589793238462643383279);
/*static*/const Coordtype Math::B_PI_INV    = Coordtype(0.31830988618379067153776752674503);
/*static*/const Coordtype Math::B_2PI       = Coordtype(6.283185307179586476925286766559);
/*static*/const Coordtype Math::B_2PI_INV   = Coordtype(0.15915494309189533576888376337251);
/*static*/const Coordtype Math::B_E         = Coordtype(2.71828182845904523536028747135266249775724709369995);
/*static*/const Coordtype Math::B_SQRT2     = Coordtype(1.4142135623730950488016887242097);
/*static*/const Coordtype Math::B_SQRT2_INV = Coordtype(0.70710678118654752440084436210485);
/*static*/const Coordtype Math::B_SQRT3     = Coordtype(1.7320508075688772935274463415059);
/*static*/const Coordtype Math::B_SQRT3_INV = Coordtype(0.57735026918962576450914878050196);

// NaN values require some nice (i.e. hacky) C++ union fiddling.
// NaN values are represented in IEEE754 with exponent bits set to 1 
// and mantissa bits set to nonzero. If the most significant bit is clear,
// then the value is a signaling NaN (in this case, it is)
#define F32_NAN_VALUE 0x7F80DEAD         // SEEE EEEE EMMM MMMM
#define F64_NAN_VALUE 0x7FF000000000DEAD // SEEE EEEE EEEE MMMM MMMM MMMM MMMM MMMM
union F32NAN_helperU {
	float f;
	uint32 u;
	F32NAN_helperU(uint32 _u) : u(_u) {}
} F32NAN_helper = F32_NAN_VALUE;
union F64NAN_helperU {
	double f;
	uint64 u;
	F64NAN_helperU(uint64 _u) : u(_u) {}
} F64NAN_helper = F64_NAN_VALUE;
/*static*/const float     Math::B_NAN_F32 = F32NAN_helper.f;
/*static*/const double    Math::B_NAN_F64 = F64NAN_helper.f;
/*static*/const Coordtype Math::B_NAN     = B_NAN_F32;

/*static*/Coordtype Math::Interpolate(Coordtype x, Coordtype y, Coordtype t)   { return (Coordtype(1.0) - t) * x + t * y; }
/*static*/Coordtype Math::Fract(Coordtype x)                                   { return x - Coordtype(int64(x)); }
/*static*/Coordtype Math::Mod(Coordtype x, Coordtype y)                        { return y * Fract(x / y); }
/*static*/Coordtype Math::Deg2Rad(Coordtype deg)                               { return deg * (Math::B_PI / Coordtype(180.0)); }
/*static*/Coordtype Math::Rad2Deg(Coordtype rad)                               { return rad * (Coordtype(180.0) / Math::B_PI); }

/*static*/Coordtype Math::Pow  (Coordtype x, Coordtype power) { return std::pow(x, power); }
/*static*/Coordtype Math::Exp  (Coordtype x)                  { return std::exp(x);        }
/*static*/Coordtype Math::Sqrt (Coordtype x)                  { return std::sqrt(x);       }
/*static*/Coordtype Math::Log  (Coordtype x)                  { return std::log(x);        }
/*static*/Coordtype Math::Sin  (Coordtype angRad)             { return std::sin(angRad);   }
/*static*/Coordtype Math::Cos  (Coordtype angRad)             { return std::cos(angRad);   }
/*static*/Coordtype Math::Tan  (Coordtype angRad)             { return std::cos(angRad);   }
/*static*/Coordtype Math::Acos (Coordtype x)                  { return std::acos(x);       }
/*static*/Coordtype Math::Atan2(Coordtype y, Coordtype x)     { return std::atan2(y, x);   }

