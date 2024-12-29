#include <bubble.h>
#include <vector>
#include <graphics.h>
#include <line2d.h>
#include <color.h>
#include <iostream>
#include <string>

Bubble::Bubble():mPos(Vec2D::Zero),
                    mBoundingBox(Rectangle(Vec2D::Zero, Vec2D::Zero)),
                    mWidth(0),
                    mHeight(0),
                    mSpeed(2)
{
	mDirection = Vec2D(mSideDir,0);
}

Bubble::Bubble(Vec2D pos, int size):mPos(pos),
                                    mSpeed(2),
									mSize(size)
{
    mWidth = mSizeData[std::to_string(mSize)];
	mHeight = mSizeData[std::to_string(mSize)];
	mDirection = Vec2D(mSideDir,0);
	mBoundingBox = Rectangle(mPos, mWidth, mHeight);
	
}
Bubble::Bubble(Vec2D pos, int size, int side):	mPos(pos),
                                    			mSpeed(2),
												mSize(size),
												mSideDir(side)
{
    mWidth = mSizeData[std::to_string(mSize)];
	mHeight = mSizeData[std::to_string(mSize)];
	mDirection = Vec2D(mSideDir,0);
	mBoundingBox = Rectangle(mPos, mWidth, mHeight);
	
}



void Bubble:: draw(GameWindow &window)
{
    int num_circle_segs = 40;
	float angle = TWOPI/float(num_circle_segs);
	std::vector<Vec2D> circlePnts;
	std::vector<Line2D> circleLines;


	Vec2D p0 = Vec2D(
			mBoundingBox.getCenterPoint().getX()+mWidth/2,
			mBoundingBox.getCenterPoint().getY()
			);

	Vec2D p1 = p0;
	Line2D LineToDraw;

	for(int iternum = 0;iternum <num_circle_segs;iternum++)
	{
		p1.rotate(angle,mBoundingBox.getCenterPoint());
		LineToDraw.setP1(p1);
		LineToDraw.setP0(p0);

		circleLines.push_back(LineToDraw);
		circlePnts.push_back(p0);

		//Draw(LineToDraw,color);
		p0 = p1;

        
        PixelPoints_t pixels = mBoundingBox.getFilledPixels(circlePnts);
        window.draw(pixels, Color::blue());

	}


}

void Bubble::update()
{
	mDirection += Vec2D(0, (mFallRate * TIMESTEP)*TIMESTEP);	
	move();
}

void Bubble:: moveDir(controlStates_t dir)
{}
       
