#include <dialog.h>
#include <graphics.h>
#include <color.h>
#include <SDL2/SDL.h>

Dialog::Dialog()
{

    mBoundingBox = Rectangle();
    mPos = Vec2D::Zero;
    mDirection = Vec2D::Zero; 
  
}
Dialog::Dialog(DialogTypes_t type, Vec2D pos, int width, int height)
{


    mPos = pos;
    mWidth = width;
    mHeight = height;
    mBoundingBox = Rectangle(mPos,mWidth,mHeight);
    mDirection = Vec2D::Zero;
   
}
void Dialog::draw(GameWindow &window)
{

    unsigned int width = window.getBacksurface()->w;
    unsigned int height = window.getBacksurface()->h;
    Rectangle dim_rect = {Vec2D::Zero, width, height};
    PixelPoints_t back_pixels = dim_rect.getFilledPixels(dim_rect.getPoints());
    window.draw(back_pixels, Color(0,0,0,150));

    PixelPoints_t pixels = mBoundingBox.getFilledPixels(mBoundingBox.getPoints());
    window.draw(pixels, Color::blue());

}
void Dialog::update()
{

}