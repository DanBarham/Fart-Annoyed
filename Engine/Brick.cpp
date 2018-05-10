#include "Brick.h"

Brick::Brick(const RectF & _rect, Color _color)
	:
	rect(_rect),
	color(_color)
{}

void Brick::Draw(Graphics & gfx) const
{
	gfx.DrawRect(rect, color);
}