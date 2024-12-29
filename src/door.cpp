#include <door.h>

Door::Door()
{
    
    int mWidth =0;
    int mHeight=0;
    mDirection = Vec2D(0,1);
    mSpeed=10;
}

Door::Door(Vec2D pos, Rectangle rect, int width, int height)
{
    mPos = pos; 
    mBoundingBox = rect;
    int mWidth = width;
    int mHeight=height;
    mDirection = Vec2D(0,1);
    mSpeed=10;

    switch(mSide)
    {
        case TOPSIDE:
        {
            mTopWall = Wall(mBoundingBox.getTopLeft(),width, height);
        }
    }
    

}