#include "MathCommon.h"

#include "Assist/Common.h"

// TODO Can this be avoided? As far as my research got, there is no way not 
// to use stdlib math intrinsics. Further investigation needed.
#include <cmath>

const Coordtype Math::B_PI        = Coordtype(3.141592);
const Coordtype Math::B_PI_INV    = Coordtype(0.318309);
const Coordtype Math::B_2PI       = Coordtype(6.283184);
const Coordtype Math::B_2PI_INV   = Coordtype(0.159154);
const Coordtype Math::B_E         = Coordtype(2.718281);
const Coordtype Math::B_SQRT2     = Coordtype(1.414213);
const Coordtype Math::B_SQRT2_INV = Coordtype(0.707106);
const Coordtype Math::B_SQRT3     = Coordtype(1.732051);
const Coordtype Math::B_SQRT3_INV = Coordtype(0.577350);

Coordtype Math::Interpolate(Coordtype x, Coordtype y, Coordtype t)   { return (Coordtype(1.0) - t) * x + t * y; }
Coordtype Math::Fract(Coordtype x)                                   { return x - Coordtype(int64(x)); }
Coordtype Math::Mod(Coordtype x, Coordtype y)                        { return y * Fract(x / y); }
Coordtype Math::Deg2Rad(Coordtype deg)                               { return deg * (Math::B_PI / Coordtype(180.0)); }
Coordtype Math::Rad2Deg(Coordtype rad)                               { return rad * (Coordtype(180.0) / Math::B_PI); }

Coordtype Math::Pow  (Coordtype x, Coordtype power) { return std::pow(x, power); }
Coordtype Math::Exp  (Coordtype x)                  { return std::exp(x);        }
Coordtype Math::Sqrt (Coordtype x)                  { return std::sqrt(x);       }
Coordtype Math::Log  (Coordtype x)                  { return std::log(x);        }
Coordtype Math::Sin  (Coordtype angRad)             { return std::sin(angRad);   }
Coordtype Math::Cos  (Coordtype angRad)             { return std::cos(angRad);   }
Coordtype Math::Tan  (Coordtype angRad)             { return std::cos(angRad);   }
Coordtype Math::Acos (Coordtype x)                  { return std::acos(x);       }
Coordtype Math::Atan2(Coordtype y, Coordtype x)     { return std::atan2(y, x);   }

