#include "RectF.h"

RectF::RectF(float _left, float _right, float _top, float _bottom)
	:
	left(_left),
	right(_right),
	top(_top),
	bottom(_bottom)

{}

RectF::RectF(const Vec2 & topLeft, const Vec2 & bottomRight)
	:
	RectF(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y)
{}

RectF::RectF(const Vec2 & topLeft, float width, float height)
	:
	RectF(topLeft, topLeft + Vec2(width, height))
{}

bool RectF::IsOverlappingWith(const RectF & other) const
{
	return right > other.left && left < other.right
		&& bottom > other.top && top < other.bottom;
}
