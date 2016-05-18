#include "Picker2D.h"

#include "BL/IPickable2D.h"


bool Picker2D::PickResult::SortPredicate::operator () (const Picker2D::PickResult& r1, const Picker2D::PickResult& r2) const
{
	return r1.closestZ > r2.closestZ;
}

// -----------------------------------

Picker2D::Picker2D()
	: mLock()
	, mPickObjects()
{
}

Picker2D::~Picker2D()
{
}

bool Picker2D::pick(const Vector2& point, uint64 filter, /*out*/Array<PickResult>& resultArray)
{
	resultArray.clear();

	PickInput input = PickInput(point, filter);

	mLock.lock();
	// TODO IMPROVEMENT: implement spatial partitioning or other optimization to reduce unnecessary tests
	for (int i = 0; i < mPickObjects.size(); ++i)
	{
		IPickable2D* pickObject = mPickObjects[i];

		PickResult result;
		bool hit = pickObject->performPick(input, result);

		if (hit)
		{
			resultArray.append(result);
		}
	}
	mLock.release();

	// Sort pickables by descending z-order
	resultArray.eQuickSort(PickResult::SortPredicate());

	return resultArray.size() > 0;
}

void Picker2D::addPickable(IPickable2D* pickable)
{
	mLock.lock();
	mPickObjects.append(pickable);
	mLock.release();
}

void Picker2D::removePickable(IPickable2D* pickable)
{
	mLock.lock();
	mPickObjects.eRemoveItemUnordered(pickable);
	mLock.release();
}

