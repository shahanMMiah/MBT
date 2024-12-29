#include <door.h>
#include <bubble.h>

Door::Door()
{
    
    int mWidth =0;
    int mHeight=0;
    mDirection = Vec2D(0,-3);
    mSpeed=10;
}

Door::Door(Vec2D pos, Rectangle rect, int doorWidth, int doorHeight, sideNames_t mSide)
{
    mPos = pos; 
    mBoundingBox = rect;
    
    mDirection = Vec2D(0,-3);
    mSpeed=10;

    switch(mSide)
    {
        case RIGHTSIDE:
        {
            mDoorWall = Wall(mBoundingBox.getBottomRight()-Vec2D(0,doorHeight*2),doorWidth, doorHeight*2,mDirection);
            mTopWall = Wall(mBoundingBox.getTopRight(),doorWidth, mBoundingBox.getHeight() - mDoorWall.getBoundingBox().getHeight(),mDirection);
            break;
        }
        case LEFTSIDE:
        {
            mDoorWall = Wall(mBoundingBox.getBottomLeft()-Vec2D(0,doorHeight*2),doorWidth, doorHeight*2,mDirection);
            mTopWall = Wall(mBoundingBox.getTopLeft(),doorWidth, mBoundingBox.getHeight() - mDoorWall.getBoundingBox().getHeight(),mDirection);
            break;
        }
    }
    

}
void Door::checkIfOpen(std::vector<Bubble> &bubbles)
{
       bool found_bubbles = false;
       if (!mOpen)
       {
        for (auto &bubble:bubbles)
        {
            if (mBoundingBox.intersects(bubble.getBoundingBox()))
            {
                found_bubbles = true;
                break;
            }
            
        }

        if(!found_bubbles)
        {
            std::cout<<"opening door!"<<std::endl;
            mOpen = true;
        }
       }

}

void Door::update()
{
    if (mOpen && mDoorWall.getBoundingBox().getBottomLeft().getY() > mTopWall.getBoundingBox().getBottomLeft().getY())
    {  
        mDoorWall.move();
    }
}

void Door::draw(GameWindow &window)
{   
   
    mDoorWall.draw(window,Color::green());
    mTopWall.draw(window);
    

    


}