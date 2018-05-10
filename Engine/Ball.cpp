#include "Ball.h"
#include "SpriteCodex.h"

Ball::Ball(const Vec2 & _pos, const Vec2 & _vel)
	:
	pos( _pos ),
	vel( _vel )
{}

void Ball::Draw(Graphics & gfx) const
{
	SpriteCodex::DrawBall( pos,gfx );
}