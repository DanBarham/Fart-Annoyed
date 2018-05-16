#pragma once

#include "Graphics.h"
#include "Vec2.h"

class SpriteCodex
{
public:
	static void DrawBall( const Vec2& center,Graphics& gfx ); // centered drawing of 14x14 sprite
	static void DrawGameStart( int x,int y,Graphics& gfx );
	static void DrawGameOver( int x,int y,Graphics& gfx );
};