#pragma once

#include "Assist/Common.h"

#include <tuple>

template <class... Params>
class Tuple : public std::tuple<Params...> {
public:
	Tuple(Params... params) :std::tuple<Params...>(std::make_tuple(params...)) {}
};
