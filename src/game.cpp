#include<game.h>
#include <utils.h>
#include<line2d.h>
#include <algorithm>


Game::Game(GameWindow& window)
{
    Vec2D point1(window.getBacksurface()->w/2 - 20, window.getBacksurface()->h/2 + 20);
	Vec2D point2(window.getBacksurface()->w/2 + 20, window.getBacksurface()->h/2 + 20);
	//Rectangle rect(point1, point2);
	mPlayer = Player(point1, 30, 30);

	mWalls.push_back(Wall(Vec2D(0, window.getBacksurface()->h  - 40), window.getBacksurface()->w, 40 ));
	mWalls.push_back(Wall(Vec2D(0,0), 10, window.getBacksurface()->h ));
	mWalls.push_back(Wall(Vec2D(window.getBacksurface()->w -10,0), 10, window.getBacksurface()->h ));
	mWalls.push_back(Wall(Vec2D(0,0), window.getBacksurface()->w, 50 ));
	
	
	mBubbles.push_back(Bubble(point1+Vec2D(-120,0), DEFAULT_BUBBLE_SIZE, DEFAULT_BUBBLE_SIDE*-1));
	for(int iter =0;iter<DEFAULT_NEEDLE_AMOUNT;iter++)
	{
		mNeedles.push_back(Needle(mPlayer.getPos(), DEFAULT_NEEDLE_WIDTH, DEFAULT_NEEDLE_HEIGHT));
	}

	setupPlayerControls();
	groundPlayer();

}

void Game:: setupPlayerControls()
{
	mController = Controller();

	auto left_func = [this](uint32_t delta_amount)
	{
		mPlayer.moveDir(LEFT);
	};
	controlInput_t left = {.sym=SDLK_LEFT, .func=left_func};
	mController.mControlInputs.push_back(left);


	auto right_func = [this](uint32_t delta_amount)
	{
		mPlayer.moveDir(RIGHT);
	};
	controlInput_t right = {.sym=SDLK_RIGHT, .func=right_func};
	mController.mControlInputs.push_back(right);
	

	auto up_func = [this](uint32_t delta_amount)
	{
		mPlayer.moveDir(UP);
	};
	controlInput_t up = {.sym=SDLK_UP, .func=up_func};
	mController.mControlInputs.push_back(up);

	auto down_func = [this](uint32_t delta_amount)
	{
		mPlayer.moveDir(DOWN);
	};
	controlInput_t down = {.sym=SDLK_DOWN, .func=down_func};
	mController.mControlInputs.push_back(down);
	

	auto shoot_func = [this](uint32_t delta_amount)
	{
		mPlayer.shoot(mNeedles);
	};
	controlInput_t shoot = {.sym=SDLK_SPACE, .func=shoot_func};
	mController.mControlInputs.push_back(shoot);
}

void Game:: draw(GameWindow& window ,uint32_t delta_time)
{
	//window.resize();
    mPlayer.draw(window);
	
	
	for (auto &wall : mWalls)
	{
		wall.draw(window);
	}

	for (auto &bubble : mBubbles)
	{

		bubble.draw(window);
	}

	for (auto &needle: mNeedles)
	{
		needle.draw(window);
	}

    window.flip();
}

bool Game:: update(uint32_t delta_time)
{   
    bool quit = mController.update(delta_time);
    
	mPlayer.update();
	
	std::vector<Bubble> bubbleDest;
	resizeBubbles(bubbleDest);

	
	
	for (auto &bubble : mBubbles)
	{
		bubble.update();
		
	}

	for (auto &needle: mNeedles)
	{
		needle.update();
	}

	
	checkWallBounce();
	checkNeedleHit();
	checkBubblePopped();
    return(quit);
}

void Game:: checkWallBounce()
{
	for (auto &bubble : mBubbles)
	{
		int iter =0;
		for (auto &wall : mWalls)
		{
			if(bubble.getBoundingBox().intersects(wall.getBoundingBox()))
			{
				std::vector<Line2D> lines = {
					Line2D(wall.getBoundingBox().getTopLeft(),wall.getBoundingBox().getTopRight()),
					Line2D(wall.getBoundingBox().getTopLeft(),wall.getBoundingBox().getBottomLeft()),
					Line2D(wall.getBoundingBox().getTopRight(),wall.getBoundingBox().getBottomRight()),
					Line2D(wall.getBoundingBox().getBottomLeft(),wall.getBoundingBox().getBottomRight()),
				};

				float distance = 0.0f;
				size_t line_iter; 

				for(size_t iter=0; iter < lines.size();iter++)
				{
					float dist = lines[iter].closestPoint(
						bubble.getBoundingBox().getCenterPoint()).distance(bubble.getBoundingBox().getCenterPoint());
					
					if(dist < distance || distance == 0.0f)
					{
						distance = dist;
						line_iter = iter;
					}

				}
				
				Vec2D normal_vec;
				switch (line_iter)
				{
				case TOPSIDE:
					bubble.setMove(
						lines[0].closestPoint(
							bubble.getBoundingBox().getBottomLeft()
						)+Vec2D(0,bubble.getBoundingBox().getHeight()*-1));
					normal_vec = Vec2D(0,1);
					break;

				case LEFTSIDE:
					bubble.setMove(
						lines[1].closestPoint(
							bubble.getBoundingBox().getTopLeft()
						)+Vec2D(bubble.getBoundingBox().getWidth()*-1, 0));
					normal_vec = Vec2D(-1,0);
					break;
					
				case RIGHTSIDE:
					bubble.setMove(
						lines[2].closestPoint(
							bubble.getBoundingBox().getTopRight()
						));
					normal_vec = Vec2D(1,0);
					break;
					
				case BOTTOMSIDE:
					bubble.setMove(
						lines[3].closestPoint(
							bubble.getBoundingBox().getTopLeft()
						)+Vec2D(0,bubble.getBoundingBox().getHeight()));
					normal_vec = Vec2D(0,-1);
					break;				
	
				default:
					break;
				}
				
				bubble.setDirection(bubble.getDirection().reflect(normal_vec));
		
			}
		}
	}
}

void Game::groundPlayer()
{
	Line2D line(mWalls[0].getBoundingBox().getTopLeft(),mWalls[0].getBoundingBox().getTopRight());
	mPlayer.moveFromBottom(line.closestPoint(mPlayer.getPos()));
	
	
}

void Game::checkNeedleHit()
{
	for (auto &needle : mNeedles)
	{
		for (auto &wall : mWalls)
		{
			if (!needle.getHit() && needle.checkCollided(wall.getBoundingBox()))
			{
				needle.setHit(true);

			}
		}
	}
}

void Game::checkBubblePopped()
{
	for(auto &bubble: mBubbles)
	{
		for(auto &needle: mNeedles)
		{
			if(needle.getHit() || needle.getLoaded())
			{
				continue;
			}
			if (needle.checkCollided(bubble.getBoundingBox()))
			{
				needle.setHit(true);
				bubble.setPopped(true);
				break;
			}
		}
	}
}

void Game:: resizeBubbles(std::vector<Bubble>& other)
{
	for (size_t iter =0;iter < mBubbles.size(); iter++)
	{
		if (!mBubbles[iter].getPopped())
			{
				other.push_back(std::move(mBubbles[iter])); 
			}

		else if(mBubbles[iter].getSize() > 1)
		{
			Vec2D popped_pos = mBubbles[iter].getPos();
			if(int(mPlayer.getPos().distance(popped_pos)) < mPlayer.getHeight() * DEFAULT_POP_DISTANCE+1 )
			{
				popped_pos = mBubbles[iter].getPos() -  Vec2D(0, mPlayer.getHeight() * DEFAULT_POP_DISTANCE );
			} 
			other.push_back(
				Bubble(
					popped_pos-Vec2D(0,DEFAULT_BUBBLE_OFFSET),
					mBubbles[iter].getSize()-1, 
					DEFAULT_BUBBLE_SIDE
					)
			);

			other.push_back(
				Bubble(
					popped_pos-Vec2D(0,DEFAULT_BUBBLE_OFFSET), 
					mBubbles[iter].getSize()-1, 
					DEFAULT_BUBBLE_SIDE*-1)
			);
		}
		
	}

	mBubbles = std::move(other);
	other.clear();
	
}
