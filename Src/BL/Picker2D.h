#pragma once

#include "Assist/Common.h"

#include "BL/Pick_Common.h"

#include "Assist/Vector2.h"
#include "Assist/Mutex.h"
#include "Assist/Array.h"

class IPickable2D;

class Picker2D
{
public:

public:

	Picker2D();
	DISABLE_COPY(Picker2D);
	~Picker2D();

	bool pick(const Vector2& point, uint64 filter, /*out*/Array<PickResult2D>& resultArray);

	void addPickable(IPickable2D* pickable);
	void removePickable(IPickable2D* pickable);

private:

	Mutex mLock;
	Array<IPickable2D*> mPickObjects;
};

