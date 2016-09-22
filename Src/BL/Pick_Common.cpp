#include "Pick_Common.h"

bool PickResult2D::SortPredicate::operator () (const PickResult2D& r1, const PickResult2D& r2) const
{
	return r1.closestZ > r2.closestZ;
}
