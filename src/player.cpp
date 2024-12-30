#include <player.h>
#include <graphics.h>
#include <color.h>
#include <iostream>
#include <utils.h>



Player::Player():mStates{false,false,false,false}
                    
{ 
    mPos= Vec2D::Zero;
    mPos = Vec2D::Zero;
    mBoundingBox = Rectangle(Vec2D::Zero, Vec2D::Zero);
    mWidth = 0;
    mHeight= 0;
    mDirection = Vec2D::Zero;
    
}

Player::Player(Vec2D pos, int width, int height):mStates{false,false,false,false}
{
    
    mPos= pos;  
    mWidth = width;
    mHeight= height;
    mDirection = Vec2D::Zero;
    
    Vec2D topLeft = mPos-= Vec2D(width, height);
    Vec2D botRight = mPos += Vec2D(width, height);
    
    mBoundingBox = Rectangle(topLeft,botRight);
}

Player::Player(Vec2D pos, Rectangle rect):mStates{false,false,false,false}
{

    mPos= pos;
    mBoundingBox = rect;     
    mWidth = mBoundingBox.getWidth() ;
    mHeight= mBoundingBox.getHeight() ;
    mDirection = Vec2D::Zero;
    
}


void Player:: draw(GameWindow &window)
{   
    PixelPoints_t pixels = mBoundingBox.getFilledPixels(mBoundingBox.getPoints());
    window.draw(pixels, Color::blue());
    window.draw(mPos.getX(),mPos.getY(), Color::red());
    
}


void Player:: moveDir(controlStates_t dir)
{      
    mStates[dir] = true;
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
    reset();
    
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

void Player::reset()
{
    
    //setMove(Vec2D::Zero);
    mDirection = Vec2D::Zero;
    for(size_t iter=0; iter < sizeof(mStates)/sizeof(mStates[0]); iter ++)
    {
        mStates[iter] = false;
    }
}

void::Player::setSize(int size)
{
    mWidth = size;
    mHeight = size;
    mBoundingBox = Rectangle(mPos, mWidth, mHeight);
}