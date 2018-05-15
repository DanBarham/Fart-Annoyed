#pragma once

#include "Colors.h"
#include "Vec2.h"
#include "Graphics.h"
#include "RectF.h"
#include "Ball.h"
#include "Keyboard.h"

class Paddle
{
public:
	Paddle( const Vec2& _pos,float _halfWidth,float _halfHeight );
	void Draw( Graphics& gfx ) const;
	bool BallCollision( Ball& ball );
	void WallCollision( const RectF& walls );
	void Update( const Keyboard& kbd,float dt );
	RectF GetRect() const;
	void ResetCooldown();
private:
	Color wingColor = Colors::Red;
	Color color = Colors::White;
	float speed = 300.0f;
	float halfWidth;
	float halfHeight;
	Vec2 pos;
	bool isCooldown = false;
};
