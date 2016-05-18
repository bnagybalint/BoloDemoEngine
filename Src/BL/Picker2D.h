#pragma once

#include "Assist/Common.h"

#include "Assist/Vector2.h"
#include "Assist/Mutex.h"
#include "Assist/Array.h"

class IPickable2D;

class Picker2D
{
public:

	// TODO it's not very nice, that this class knows every pickable type
	// maybe a runtime registering of pickable types should be implemented
	EnumBegin(ObjectType, PickAll)
		PickNone = 0,
		SynthBackground = 1 << 0,
		SynthComponent = 1 << 1,
		SynthWire = 1 << 2,
		PickAll = 0xffff,
	EnumEnd(ObjectType)

	struct PickInput
	{
		Vector2 pickPoint;
		uint64  pickFilter;

		PickInput(const Vector2& point, uint64 filter)
			: pickPoint(point)
			, pickFilter(filter)
		{}
	};

	struct PickResult
	{
		bool    hit;
		uint64  type;
		uint64  hitPart; // identifies the part of the object hit
		Vector2 closestPoint;
		float   closestDistance;
		int     closestZ;

		PickResult()
			: hit(false)
			, type(ObjectType::PickNone)
			, hitPart(0)
			, closestPoint(Vector2::ZERO)
			, closestDistance(-1.0f)
			, closestZ(0)
		{}

		// Sorts results by descending z-order, as higher z-valued objects 
		// are considered in front of lower z-valued ones.
		struct SortPredicate
		{
			bool operator () (const PickResult& r1, const PickResult& r2) const;
		};
	};

public:

	Picker2D();
	DISABLE_COPY(Picker2D);
	~Picker2D();

	bool pick(const Vector2& point, uint64 filter, /*out*/Array<PickResult>& resultArray);

	void addPickable(IPickable2D* pickable);
	void removePickable(IPickable2D* pickable);

private:

	Mutex mLock;
	Array<IPickable2D*> mPickObjects;
};

