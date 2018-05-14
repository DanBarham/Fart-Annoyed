#include "Brick.h"
#include <assert.h>

Brick::Brick(const RectF & _rect, Color _color)
	:
	rect(_rect),
	color(_color),
	destroyed( false )
{
}

void Brick::Draw(Graphics & gfx) const
{
	if (!destroyed)
	{
		gfx.DrawRect(rect.GetExpanded( padding ), color);
	}
}

bool Brick::CheckBallCollision(const Ball & ball) const
{
	return !destroyed && rect.IsOverlappingWith( ball.GetRect() );
}

void Brick::ExecuteBallCollision(Ball & ball)
{
	assert( CheckBallCollision( ball ) );
	const Vec2 ballPos = ball.GetPos();
	const Vec2 ballVel = ball.GetVel();

	if( std::signbit( ballVel.x ) == std::signbit( (ballPos - GetCenter()).x ) )
	{
		ball.ReboundY();
	}
	else if( ballPos.x >= rect.left  && ballPos.x <= rect.right )
	{
		ball.ReboundY();
	}
	else
	{
		ball.ReboundX();
	}				

	destroyed = true;
}

Vec2 Brick::GetCenter() const
{
	return rect.GetCenter();
}
