#include <game.h>
#include <utils.h>
#include <line2d.h>
#include <algorithm>
#include <string>


Game::Game(GameWindow& window)
{
	
	mPlayer = Player(Vec2D::Zero, DEFAULT_PLAYER_SIZE,DEFAULT_PLAYER_SIZE);
	mLevelData = DEFAULT_LEVEL_DATA;
	addLevel(mCurrentLevel);
	setupPlayerControls();
	mPlayer.groundPlayer(mWalls[0].getBoundingBox());
	


	mPauseScreen = Dialog(LEVEL_PAUSE,Vec2D((window.getBacksurface()->w/2)-250,(window.getBacksurface()->h/2)-125), 500,250);
	
	mState = PLAY;


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
		//std::cout<<"shot"<<std::endl;
	};
	controlInput_t shoot = {.sym=SDLK_SPACE, .func=shoot_func};
	mController.mControlInputs.push_back(shoot);


	auto pause_func = [this](uint32_t delta_amount)
	{
		
		switch(mState)
		{
			case PLAY:
				
				mState = PAUSE;
				
				break;
			case PAUSE:
				mState = PLAY;
				break;
		}
		
	};
	controlInput_t pause = {.sym=SDLK_ESCAPE, .func=pause_func};
	mController.mControlInputs.push_back(pause);
}

void Game:: draw(GameWindow& window ,uint32_t delta_time)
{
	//window.resize();
	if(mState == SETUP)
	{
		mState = PLAY;
		
	}

	else if(mState == PLAY || PAUSE)
	{
		
		mPlayer.draw(window);
		
		for (auto &door : mDoors)
		{
			door.draw(window);
		}

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

		if(mState == PAUSE)
		{
			
			mPauseScreen.draw(window);
		}

		window.flip();
	}
	
	

}

bool Game:: update(uint32_t delta_time)
{   
    bool quit = mController.update(delta_time);
    
	if (mState == PLAY)
	{
		
		mPlayer.update();
		
		std::vector<Bubble> bubbleDest;
		resizeBubbles(bubbleDest);

		for (auto &door: mDoors)
		{
			door.checkIfOpen(mBubbles);
			door.update();
		}
		
		for (auto &bubble : mBubbles)
		{
			bubble.update();
			
		}

		for (auto &needle: mNeedles)
		{
			needle.update();
		}
		

		checkPlayerHit();
		checkLives();
		checkWallBounce();
		checkBubblePopped();
		checkPlayerWalls();
		checkLevelTime();
		checkWin();		
		checkNeedleHit();
		
		
	}
	
    return(quit);
}

void Game:: checkWallBounce()
{
	for (auto &bubble : mBubbles)
	{
		int iter =0;
		for (auto &wall : mWalls)
		{
			bubble.checkBounce(wall.getBoundingBox());
		}

		for (auto &door : mDoors)
		{
			if (!door.getOpen())
			{
			bubble.checkBounce(door.getDoorBoundingBox());
			}
			bubble.checkBounce(door.getTopBoundingBox());
		}
	}
}

void Game::checkNeedleHit()
{
	for (auto &needle : mNeedles)
	{
		for (auto &wall : mWalls)
		{
			if (!needle.getHit() && !needle.getLoaded() && needle.checkCollided(wall.getBoundingBox()))
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

void Game::addNeedle()
{
	mNeedles.push_back(Needle(mPlayer.getPos(), DEFAULT_NEEDLE_WIDTH, DEFAULT_NEEDLE_HEIGHT));
}

void Game::popNeedle()
{
	mNeedles.pop_back();

}

void Game::addLevel(int levelNum)
{
	mLevels.push_back(Level(mLevelData, levelNum));
	mCurrentLevel = levelNum;
	setLevel(mCurrentLevel);
}

void Game::setLevel(int levelNum)
{	
	mState = SETUP;
	std::cout << "lives: " << mLives << std::endl;
	mLevels.back().setLevelTick(SDL_GetTicks());
	mLevels.back().setWalls(mWalls);
	mLevels.back().setDoors(mDoors);
	mLevels.back().setPlayerPos(mPlayer, mWalls[0]);
	mLevels.back().setBubbles(mBubbles);
	mLevels.back().setNeedles(mNeedles);
	
}

void Game::checkPlayerWalls()
{
	for (auto &wall: mWalls)
	{
		mPlayer.checkCollision(wall.getBoundingBox());
	}
	for (auto &door: mDoors)
	{
		mPlayer.checkCollision(door.getDoorBoundingBox());
		mPlayer.checkCollision(door.getTopBoundingBox());
	}
}       

void Game::checkPlayerHit()
{
	
	for (auto &bubble: mBubbles)
	{
		if(mPlayer.getBoundingBox().intersects(bubble.getBoundingBox()) && mState == PLAY)
		{
			mLives --;
			std::cout << "got hit" << std::endl;
			setLevel(mCurrentLevel);
		}
	}	
}

void Game::checkLives()
{
	if (mLives < 0)
	{
		std::cout << "lives: " << mLives << std::endl;
	}
}

void Game::checkWin()
{
	if (mBubbles.size() == 0)
	{
		std::cout << "passed level" << mCurrentLevel << std::endl;
		mCurrentLevel ++;
		addLevel(mCurrentLevel);

	}

}

void Game::checkLevelTime()
{
	double time = mLevels.back().getElapsedTime();
	if(time >  mLevels.back().getTimeLimit())
	{
		mLives --;
		std::cout << "ran out of time" << std::endl;
		
		setLevel(mCurrentLevel);
		
		
	}

	else 
	{
		//std::cout << "current Time is"<< time<< std::endl;
	}

}

