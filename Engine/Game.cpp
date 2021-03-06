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
#include "SpriteCodex.h"

/*
TODO::
Adjust wall dimensions / paddle / size of bricks
Draw border to show walls
Implement lives system
Title screen / game over screen
Paddle sprite (not shown in solution video) / brick shading
*/

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	ball ( Vec2( 300.0f,300.0f ),Vec2( 350.0f,350.0f ) ),
	walls( 125.0f,float( gfx.ScreenWidth ) - 125.0f,25.0f,float( gfx.ScreenHeight ) ),
	soundPad( L"Sounds\\arkpad.wav" ),
	soundBrick( L"Sounds\\arkbrick.wav" ),
	paddle( Vec2( float( gfx.ScreenWidth / 2 ),500.0f ),50.0f,8.0f )
{
	const Color colors[4] = { Colors::Red,Colors::Green,Colors::Blue,Colors::Cyan };
	const Vec2 topLeft( Graphics::ScreenWidth / 2 - brickWidth*nBricksAcross/2.0f,100.0f );

	for ( int y = 0; y < nBricksDown; ++y )
	{
		for ( int x = 0; x < nBricksAcross; ++x )
		{
			bricks[(y * nBricksAcross) + x] = Brick(
				RectF ( topLeft + Vec2( float(x) * brickWidth,float(y) * brickHeight ),brickWidth,brickHeight ),
				colors[y] );
		}
	}
}

void Game::Go()
{
	gfx.BeginFrame();

	float elapsedTime = ft.Mark();
	while ( elapsedTime > 0.0f )
	{
		const float dt = std::min( .0025f,elapsedTime );
		UpdateModel( dt );
		elapsedTime -= dt;
	}

	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel( float dt )
{
	
	if( !gameStarted )
	{
		if( wnd.kbd.KeyIsPressed( VK_RETURN ) )
		{
			gameStarted = true;
		}
	}
	else if (gameStarted)
	{
		if (!gameOver)
		{
			paddle.Update(wnd.kbd, dt);
			paddle.WallCollision(walls);

			ball.Update(dt);

			if (paddle.BallCollision(ball))
			{
				soundPad.Play();
			}

			bool collisionHappened = false;
			float curColDistSq;
			int curColIndex;
			for (int i = 0; i < nBricks; ++i)
			{
				if (bricks[i].CheckBallCollision(ball))
				{
					const float newColDistSq = (ball.GetPos() - bricks[i].GetCenter()).GetLengthSq();
					if (collisionHappened)
					{
						if (newColDistSq < curColDistSq)
						{
							curColDistSq = newColDistSq;
							curColIndex = i;
						}
					}
					else
					{
						curColDistSq = newColDistSq;
						curColIndex = i;
						collisionHappened = true;
					}
				}
			}
			if( collisionHappened )
			{
				paddle.ResetCooldown();
				bricks[curColIndex].ExecuteBallCollision( ball );
				soundBrick.Play();
			}

			if( ball.WallCollision( walls ) )
			{
				paddle.ResetCooldown();
				soundPad.Play();
			}

			gameOver = ball.CheckGameOver( walls );
		}
	}
}

void Game::DrawWall()
{
	const int padding = 10;
	const Color wallColor = Colors::Gray;
	for(int y = int(walls.top) - padding; y < int(walls.bottom); ++y)
	{
		for(int x = int(walls.left) - padding; x < int(walls.right) + padding; ++x)
		{
			if( y < int(walls.top) )
			{
				gfx.PutPixel( x,y,wallColor );
			}
			else if( x < int(walls.left) || x > int(walls.right) )
			{
				gfx.PutPixel( x,y,wallColor );
			}
		}
	}
}

void Game::ComposeFrame()
{
	if ( gameStarted )
	{
		DrawWall();
		ball.Draw( gfx );
		for ( const Brick& b : bricks )
		{
			b.Draw( gfx );
		}
		paddle.Draw( gfx );
		if ( gameOver )
		{
			SpriteCodex::DrawGameOver( 358,268,gfx );
		}
	}
	else
	{
		SpriteCodex::DrawGameStart( 300,200,gfx );
	}
}
