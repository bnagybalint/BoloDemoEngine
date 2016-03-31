#pragma once

#include "Assist/Common.h"

typedef uint64 ObjectUID;
const ObjectUID INVALID_UID = 0;

ObjectUID GenerateObjectUID();
