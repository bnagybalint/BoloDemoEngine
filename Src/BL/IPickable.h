#pragma once

#include "Assist/Common.h"
#include "Assist/Vector2.h"

// class IPickable
// {
// public:
// 
// 	struct PickInput
// 	{
// 		// TODO
// 	};
// 
// 	struct PickResult
// 	{
// 		// TODO
// 	};
// 
// public:
// 
// 	IPickable();
// 	~IPickable();
// 
// 	virtual bool performPick(const PickInput& input, /*out*/PickResult& result) = 0;
// };

class IPickable2D
{
public:

	EnumBegin(PickObjectType, PickAll)
		PickNone        = 0,
		SynthBackground = 1 << 0,
		SynthComponent  = 1 << 1,
		SynthWire       = 1 << 2,
		PickAll         = 0xffff,
	EnumEnd(PickObjectType);

	struct PickInput
	{
		Vector2 pickPoint;
		uint64  pickFilter;

		PickInput(const Vector2& point, uint64 filter = PickObjectType::PickNone)
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
			, type(PickObjectType::PickNone)
			, hitPart(0)
			, closestPoint(Vector2::ZERO)
			, closestDistance(-1.0f)
			, closestZ(0)
		{}
	};

public:

	IPickable2D();
	~IPickable2D();

	virtual bool performPick(const PickInput& input, /*out*/PickResult& result) = 0;
};

