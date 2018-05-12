/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	ball ( Vec2( 300.0f,300.0f ),Vec2( 450.0f,300.0f ) ),
	walls( 0.0f, float( gfx.ScreenWidth ),0.0f, float( gfx.ScreenHeight ) ),
	soundPad( L"Sounds\\arkpad.wav" ),
	soundBrick( L"Sounds\\arkbrick.wav" ),
	paddle( Vec2( float( gfx.ScreenWidth / 2 ),500.0f ),60.0f,6.0f )
{
	const Color colors[4] = { Colors::Red,Colors::Green,Colors::Blue,Colors::Cyan };
	const Vec2 topLeft( Graphics::ScreenWidth / 2 - brickWidth*nBricksAcross/2.0f,100.0f );

	int i = 0;
	for ( int y = 0; y < nBricksDown; ++y )
	{
		for ( int x = 0; x < nBricksAcross; ++x )
		{
			bricks[i] = Brick
			( RectF ( topLeft + Vec2( float(x) * brickWidth,float(y) * brickHeight ),brickWidth,brickHeight ),
				colors[y] );
			++i;
		}
	}

}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dt = ft.Mark();
	ball.Update( dt );
	paddle.Update( wnd.kbd,dt );
	paddle.WallCollision( walls );

	if ( paddle.BallCollision( ball ) )
	{
		soundPad.Play();
	}
	for (Brick& b : bricks)
	{
		if ( b.BallCollision( ball ) )
		{
			soundBrick.Play();
			break;
		}
	}
	if ( ball.WallCollision( walls ) )
	{
		soundPad.Play();
	}
}

void Game::ComposeFrame()
{
	ball.Draw( gfx );
	for (const Brick& b : bricks)
	{
		b.Draw(gfx);
	}
	paddle.Draw( gfx );
}
