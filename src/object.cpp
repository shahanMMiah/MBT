#include <object.h>
#include <utils.h>
#include<graphics.h>
#include<color.h>

void Object::draw(GameWindow &window)
{
    PixelPoints_t pixels = mBoundingBox.getFilledPixels(mBoundingBox.getPoints());
    window.draw(pixels, Color::blue());
}

void Object::update()
{
    	move();
}

void Object::reset()
{
    setMove(Vec2D::Zero);
    mDirection = Vec2D::Zero;
}
