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
	const float wingWidth = .15f;  //Percentage of the width that each wing takes up
	RectF leftWing = GetRect();
	leftWing.right = leftWing.left + (wingWidth * 2.0f * halfWidth); 
	RectF rightWing = GetRect();
	rightWing.left = rightWing.right - (wingWidth * 2.0f * halfWidth);
	RectF center = GetRect();
	center.left = leftWing.right;
	center.right = rightWing.left;
	gfx.DrawRect(center, color);
	gfx.DrawRect(leftWing, wingColor);
	gfx.DrawRect(rightWing, wingColor);
}

bool Paddle::BallCollision( Ball & ball )
{
	const RectF rect = GetRect();
	if( !isCooldown )
	{
		if (rect.IsOverlappingWith(ball.GetRect()))
		{
			ball.Rebound( pos );

			isCooldown = true;
			return true;
		}
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

void Paddle::ResetCooldown()
{
	isCooldown = false;
}
