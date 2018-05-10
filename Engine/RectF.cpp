#include "RectF.h"

RectF::RectF(float _left, float _right, float _top, float _bottom)
	:
	left( _left ),
	right( _right ),
	top( _top ),
	bottom( _bottom )

{}

RectF::RectF(const Vec2 & topLeft, const Vec2 & bottomRight)
	:
	RectF(topLeft.x, bottomRight.x, topLeft.y, bottomRight.y)
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

RectF RectF::FromCenter(const Vec2 & center, float halfWidth, float halfHeight)
{
	const Vec2 half( halfWidth,halfHeight );
	return RectF(center - half, center + half);
}
