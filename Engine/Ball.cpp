#include "Ball.h"
#include "SpriteCodex.h"

Ball::Ball(const Vec2 & _pos, const Vec2 & _vel)
	:
	pos( _pos ),
	vel( _vel )
{
}

void Ball::Draw(Graphics & gfx) const
{
	SpriteCodex::DrawBall( pos,gfx );
}

void Ball::Update( float dt )
{
	pos += vel * dt;
}

bool Ball::WallCollision(const RectF & walls)
{
	bool collided = false;
	const RectF rect = GetRect();

	//Left / Right
	if ( rect.left < walls.left )
	{
		ReboundX();
		pos.x += walls.left - rect.left;
		collided = true;
	}
	else if ( rect.right > walls.right )
	{
		ReboundX();
		pos.x -= rect.right - walls.right;
		collided = true;
	}

	//Top / Bottom
	if (rect.top < walls.top)
	{
		ReboundY();
		pos.y += walls.top - rect.top;
		collided = true;
	}

	return collided;
}

bool Ball::CheckGameOver(const RectF & walls)
{
	if (GetRect().bottom > walls.bottom)
	{
		return true;
	}

	return false;
}

RectF Ball::GetRect() const
{
	return RectF::FromCenter( pos,radius,radius );
}

void Ball::ReboundX()
{
	vel.x *= -1;
}

void Ball::ReboundY()
{
	vel.y *= -1;
}

void Ball::Rebound(const Vec2 newDir)
{
	const float magnitude = vel.GetLength();
	vel = (pos - newDir).GetNormalized() * magnitude;
}

Vec2 Ball::GetVel() const
{
	return vel;
}

Vec2 Ball::GetPos() const
{
	return pos;
}
