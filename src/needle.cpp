#include <needle.h>
#include <player.h>
#include <color.h>
#include <graphics.h>


Needle::Needle()  
{
    mPos = Vec2D::Zero;
    mWidth = 0;
    mHeight = 0;
    mSpeed = DEFAULT_NEEDLE_SPEED*-1;
    mDirection = Vec2D(0,mSpeed);
    mBoundingBox = Rectangle(Vec2D::Zero, Vec2D::Zero); 
    mStringBoundingBox = Rectangle(Vec2D::Zero, Vec2D::Zero);
    mHit = false;
    mLoaded = true;
}


Needle::Needle(Vec2D pos, int width, int height)
{
    mPos = pos;
    mWidth = width;
    mHeight = height;

    mSpeed = DEFAULT_NEEDLE_SPEED*-1;
    mDirection = Vec2D(0,mSpeed);
    mBoundingBox = Rectangle(mPos, mWidth, mHeight);
    mStringBoundingBox = Rectangle(mPos, mWidth, mHeight);
    mHit = false;
    mLoaded = true;


}

void Needle::shoot()
{
    setLoaded(false);

   
}

void Needle::update()
{
    
    
    if (!mHit && !mLoaded)
    {   
        
        move(); 
        mStringBoundingBox.moveBy(0, mDirection);
        mStringBoundingBox.moveBy(2, mDirection);
           
    }
    
    if(mHit)
    {
        setLoaded(true);
        setHit(false);
    }



}

void Needle::setPos(Vec2D pos)
{
    mPos = pos;
    mBoundingBox.moveTo(mPos);
    
    mStringBoundingBox.setTopLeft(mPos);
    
    mStringBoundingBox.setTopRight(
			Vec2D((mStringBoundingBox.getTopLeft().getX()+mWidth-1),
			(mStringBoundingBox.getTopLeft().getY())));

    mStringBoundingBox.setBottomRight(
			Vec2D((mStringBoundingBox.getTopLeft().getX()+mWidth-1),
			(mStringBoundingBox.getTopLeft().getY())+mHeight-1));
	
	mStringBoundingBox.setTopRight(
			Vec2D((mStringBoundingBox.getTopLeft().getX()+mWidth-1),
			(mStringBoundingBox.getTopLeft().getY())));
	
	mStringBoundingBox.setBottomLeft(
			Vec2D((mStringBoundingBox.getTopLeft().getX()),
			(mStringBoundingBox.getTopLeft().getY())+mHeight-1));
        
}

void Needle::draw(GameWindow& window)
{
    if (!mHit && !mLoaded)
    {
    PixelPoints_t pixels = mBoundingBox.getFilledPixels(mBoundingBox.getPoints());
    window.draw(pixels, Color::pink());

    PixelPoints_t string_pixels = mStringBoundingBox.getFilledPixels(mStringBoundingBox.getPoints());
    window.draw(string_pixels, Color::pink());

    }
}

bool Needle::checkCollided(const Rectangle& other)
{
    if(mBoundingBox.intersects(other)|| mStringBoundingBox.intersects(other))
    {
        return true;
    }
    return false;
}





