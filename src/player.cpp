#include <player.h>
#include <graphics.h>
#include <color.h>
#include <iostream>
#include <utils.h>



Player::Player():   mPos(Vec2D::Zero),
                    mBoundingBox(Rectangle(Vec2D::Zero, Vec2D::Zero)),
                    mWidth(0),
                    mHeight(0),
                    mDirection(Vec2D::Zero),
                    mStates{false,false,false,false}
                    
{ 
    
    
}

Player::Player(Vec2D pos, int width, int height):   mPos(pos),
                                                    mWidth(width),
                                                    mHeight(height ),
                                                    mDirection(Vec2D::Zero),
                                                    mStates{false,false,false,false}
{
    
    Vec2D topLeft = mPos-= Vec2D(width, height);
    Vec2D botRight = mPos += Vec2D(width, height);
    
    mBoundingBox = Rectangle(topLeft,botRight);
}

Player::Player(Vec2D pos, Rectangle rect):  mBoundingBox(rect),
                                            mPos(pos),
                                            mDirection(Vec2D::Zero),
                                            mStates{false,false,false,false}
{}


void Player:: draw(GameWindow &window)
{   
    PixelPoints_t pixels = mBoundingBox.getFilledPixels(mBoundingBox.getPoints());
    window.draw(pixels, Color::blue());
    window.draw(mPos.getX(),mPos.getY(), Color::red());
    
}


void Player:: moveDir(controlStates_t dir)
{   
    
    mStates[dir] = true;
    //std::cout<<mStates[0]<<mStates[1]<<mStates[2]<<mStates[3]<<std::endl;  
}


void Player::update()
{
    if (!(mStates[LEFT] && mStates[RIGHT]))
    {
        if(mStates[LEFT])
        {
            mDirection.setX(mSpeed*-1);
        }
        else if(mStates[RIGHT])
        {
            mDirection.setX(mSpeed);
        }
        
    }
    if (!(mStates[UP] && mStates[DOWN]) && mClimbing)
    {
        if(mStates[UP])
        {
            mDirection.setY(mSpeed*-1);
        }
        else if(mStates[DOWN])
        {
            mDirection.setY(mSpeed);
        } 
    }
    
    move();
    
    mDirection = Vec2D::Zero;
    for(size_t iter=0; iter < sizeof(mStates)/sizeof(mStates[0]); iter ++)
    {
        mStates[iter] = false;

    }



}

void Player::moveFromBottom(Vec2D pos)
{
    
    mDirection = pos - getBottomMid();
   //move();
}

size_t Player::shoot(std::vector<Needle>& needles)
{   
    for (size_t iter =0; iter < needles.size();iter++)
    {
        if (needles[iter].getLoaded())
        {   
            needles[iter].setPos(getBottomMid()+Vec2D(30,-10));
            needles[iter].shoot();
            return iter;
        }
        
    }
    return 0;
    
}