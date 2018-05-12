#include "Brick.h"

Brick::Brick(const RectF & _rect, Color _color)
	:
	rect(_rect),
	color(_color)
{
}

void Brick::Draw(Graphics & gfx) const
{
	if (!destroyed)
	{
		gfx.DrawRect(rect.GetExpanded( padding ), color);
	}
}

bool Brick::BallCollision(Ball & ball)
{
	if (!destroyed && rect.IsOverlappingWith(ball.GetRect()))
	{
		if (ball.GetRect().right > rect.left
			|| ball.GetRect().left < rect.left)
		{
			ball.ReboundX();
		}

		if (ball.GetRect().top < rect.bottom
			|| ball.GetRect().bottom > rect.top)
		{
			ball.ReboundY();
		}
		destroyed = true;
		return true;
	}

	return false;
}