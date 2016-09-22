#include "Picker2D.h"

#include "BL/PickObject2D.h"
#include "BL/IPickable2D.h"


// -----------------------------------

Picker2D::Picker2D()
	: mLock()
	, mPickObjects()
{
}

Picker2D::~Picker2D()
{
}

bool Picker2D::pick(const Vector2& point, uint64 filter, /*out*/Array<PickResult2D>& resultArray)
{
	resultArray.clear();

// 	PickInput2D input = PickInput2D(point, filter);
// 
// 	mLock.lock();
// 	// TODO IMPROVEMENT: implement spatial partitioning or other optimization to reduce unnecessary tests
// 	for (int i = 0; i < mPickObjects.size(); ++i)
// 	{
// 		PickResult2D result;
// 		bool hit = mPickObjects[i]->performPick(input, result);
// 
// 		if (hit)
// 		{
// 			resultArray.append(result);
// 		}
// 	}
// 	mLock.release();
// 
// 	// Sort pickables by descending z-order
// 	resultArray.eQuickSort(PickResult2D::SortPredicate());

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

