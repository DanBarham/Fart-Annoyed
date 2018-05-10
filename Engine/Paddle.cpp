#include "Paddle.h"

Paddle::Paddle(const Vec2 & _pos, float _halfWidth, float _halfHeight)
	:
	pos( _pos ),
	halfWidth( _halfWidth ),
	halfHeight( _halfHeight )
{
}

void Paddle::Draw( Graphics & gfx ) const
{
	gfx.DrawRect(GetRect(), color);
}

bool Paddle::BallCollision( Ball & ball ) const
{
	if ( ball.GetVel().y > 0.0f && GetRect().IsOverlappingWith(ball.GetRect()))
	{
		ball.ReboundY();
		return true;
	}

	return false;
}

void Paddle::WallCollision( const RectF & walls )
{
	const RectF rect = GetRect();

	if (rect.left < walls.left)
	{
		pos.x += walls.left - rect.left;
	}
	else if (rect.right > walls.right)
	{
		pos.x -= rect.right - walls.right;
	}
}

void Paddle::Update( const Keyboard& kbd,float dt )
{
	if ( kbd.KeyIsPressed( VK_RIGHT ) )
	{
		pos.x += speed * dt;
	}
	else if (kbd.KeyIsPressed( VK_LEFT ))
	{
		pos.x -= speed * dt;
	}
}

RectF Paddle::GetRect() const
{
	return RectF::FromCenter( pos,halfWidth,halfHeight );
}
