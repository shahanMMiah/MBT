#include <dialog.h>
#include <graphics.h>
#include <color.h>
#include <SDL2/SDL.h>

Dialog::Dialog()
{

    mType = LEVEL_PAUSE;
    mBoundingBox = Rectangle();
    mPos = Vec2D::Zero;
    mDirection = Vec2D::Zero;
    mOn = false;
    mState = LEVEL_PAUSE_STATE;

}
Dialog::Dialog(DialogTypes_t type, Vec2D pos, int width, int height)
{
    mType = type;
    mPos = pos;
    mWidth = width;
    mHeight = height;
    mBoundingBox = Rectangle(mPos,mWidth,mHeight);
    mDirection = Vec2D::Zero;
    mOn = false;
    mState = LEVEL_PAUSE_STATE;
    
    
    mMessage = "";
    if (mType == LEVEL_PAUSE)
    {
        mMessage = "Game is Paused";
    }
   
}
Dialog::Dialog(DialogTypes_t type, Vec2D pos, int width, int height,CutsceneLevelStates_t state)
{
    mType = type;
    mPos = pos;
    mWidth = width;
    mHeight = height;
    mBoundingBox = Rectangle(mPos,mWidth,mHeight);
    mDirection = Vec2D::Zero;
    mOn = false;
    mState = state;
    
    
    mMessage = "";
    if (mType == LEVEL_PAUSE)
    {
        mMessage = "Game is Paused";
    }
   
}

void Dialog::draw(GameWindow &window)
{

    if(mOn)
    {
        unsigned int width = window.getBacksurface()->w;
        unsigned int height = window.getBacksurface()->h;
        Rectangle dim_rect = {Vec2D::Zero, width, height};
        PixelPoints_t back_pixels = dim_rect.getFilledPixels(dim_rect.getPoints());
        window.draw(back_pixels, Color(0,0,0,150));

        PixelPoints_t pixels = mBoundingBox.getFilledPixels(mBoundingBox.getPoints());
        window.draw(pixels, Color::blue());

        for (auto &boxes: mExtraBoxes)
        {
            PixelPoints_t box_pixels = mBoundingBox.getFilledPixels(boxes.getPoints());
            window.draw(box_pixels, Color::green());
        
        }

        //std::cout<< mMessage << std::endl;// TODO: add text to window 
    }


}

void Dialog::update(uint32_t delta_num)
{
    mDialogControl.update(delta_num);
    

}


void Dialog::addExtraBoxes(Rectangle & rect)
{
    mExtraBoxes.push_back(std::move(rect));
}