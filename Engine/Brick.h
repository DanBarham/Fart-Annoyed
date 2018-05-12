#pragma once

#include "RectF.h"
#include "Colors.h"
#include "Graphics.h"
#include "Ball.h"

class Brick
{
public:
	Brick() = default;
	Brick( const RectF & _rect,Color _color );
	void Draw( Graphics & gfx ) const;
	bool BallCollision( Ball& ball );
private:
	static constexpr float padding = -1.0f;
	RectF rect;
	Color color;
	bool destroyed = false;
};