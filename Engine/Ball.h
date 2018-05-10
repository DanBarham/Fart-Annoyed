#pragma once

#include "Vec2.h"
#include "Graphics.h"

class Ball
{
public:
	Ball( const Vec2& _pos,const Vec2& _vel );
	void Draw( Graphics& gfx ) const;
	void Update( float dt );
	bool WallCollision( const RectF& walls );
	RectF GetRect() const;
private:
	void ReboundX();
	void ReboundY();
	static constexpr float radius = 7.0f;
	Vec2 pos;
	Vec2 vel;
};