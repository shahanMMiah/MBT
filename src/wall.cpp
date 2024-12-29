#include <wall.h>
#include <color.h>
#include <graphics.h>

Wall:: Wall(): mPos(Vec2D::Zero),
                mBoundingBox(Rectangle())
                
{
    mWidth = mBoundingBox.getWidth();
    mHeight = mBoundingBox.getHeight();
    mDirection = Vec2D::Zero;
    mSpeed=4;
}

Wall::Wall(Vec2D pos, int width, int height)
{
    mPos = pos;
    mBoundingBox = Rectangle(pos,width,height);
    mWidth = mBoundingBox.getWidth();
    mHeight = mBoundingBox.getHeight();
    mDirection = Vec2D::Zero;
    mSpeed=4;

}

void Wall::draw(GameWindow &window)
{
    PixelPoints_t pixels = mBoundingBox.getFilledPixels(mBoundingBox.getPoints());
    window.draw(pixels, Color::red());
    
}
