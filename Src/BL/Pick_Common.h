#pragma once

#include "Assist/Common.h"

#include "Assist/Vector2.h"

// TODO maybe a runtime registering of pickable types should be implemented
EnumBegin(PickObjectType2D, PickAll)
	PickNone = 0,
	SynthBackground = 1 << 0,
	SynthComponent = 1 << 1,
	SynthWire = 1 << 2,
	PickAll = 0xffff,
EnumEnd(PickObjectType2D)

struct PickInput2D
{
	Vector2 pickPoint;
	uint64  pickFilter;

	PickInput2D(const Vector2& point, uint64 filter)
		: pickPoint(point)
		, pickFilter(filter)
	{}
};

struct PickResult2D
{
	bool    hit;
	uint64  type;
	uint64  hitPart; // identifies the part of the object hit
	Vector2 closestPoint;
	float   closestDistance;
	int     closestZ;

	PickResult2D()
		: hit(false)
		, type(PickObjectType2D::PickNone)
		, hitPart(0)
		, closestPoint(Vector2::ZERO)
		, closestDistance(-1.0f)
		, closestZ(0)
	{}

	// Sorts results by descending z-order, as higher z-valued objects 
	// are considered in front of lower z-valued ones.
	struct SortPredicate
	{
		bool operator () (const PickResult2D& r1, const PickResult2D& r2) const;
	};
};

