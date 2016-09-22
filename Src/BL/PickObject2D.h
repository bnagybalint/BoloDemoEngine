#pragma once

#include "Assist/Common.h"

#include "Assist/Mutex.h"
#include "Assist/String.h"

class PickObjectPart2D;
struct PickInput2D;

class PickObject2D
{
private:

	struct ObjectPartDesc
	{
		String            name;
		PickObjectPart2D* part;
		uint64            region;
	};

public:

	PickObject2D();
	virtual ~PickObject2D();

	// Note: customizable by derived class, if needed.
	virtual bool performPick(const PickInput2D& input, /*out*/PickResult2D& result) const;

	//void addObjectPart(PickObjectPart2D* objectPart, uint64 objectRegion);
	//void removeObjectPart(PickObjectPart2D* part);

private:

	Mutex mObjectLock;
	Array<ObjectPartDesc> mParts;
};

