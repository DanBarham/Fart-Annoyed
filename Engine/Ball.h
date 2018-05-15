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
	bool CheckGameOver( const RectF& walls );
	RectF GetRect() const;
	void ReboundX();
	void ReboundY();
	void Rebound( const Vec2 newDir );
	Vec2 GetVel() const;
	Vec2 GetPos() const;
private:
	static constexpr float radius = 7.0f;
	Vec2 pos;
	Vec2 vel;
};