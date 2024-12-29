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

void Bubble::checkBounce(Rectangle &boundingBox)
{
	if(getBoundingBox().intersects(boundingBox))
			{
				std::vector<Line2D> lines = {
					Line2D(boundingBox.getTopLeft(),boundingBox.getTopRight()),
					Line2D(boundingBox.getTopLeft(),boundingBox.getBottomLeft()),
					Line2D(boundingBox.getTopRight(),boundingBox.getBottomRight()),
					Line2D(boundingBox.getBottomLeft(),boundingBox.getBottomRight()),
				};

				float distance = 0.0f;
				size_t line_iter; 

				for(size_t iter=0; iter < lines.size();iter++)
				{
					float dist = lines[iter].closestPoint(
						getBoundingBox().getCenterPoint()).distance(getBoundingBox().getCenterPoint());
					
					if(dist < distance || distance == 0.0f)
					{
						distance = dist;
						line_iter = iter;
					}

				}
				
				Vec2D normal_vec;
				switch (line_iter)
				{
				case TOPSIDE:
					setMove(
						lines[0].closestPoint(
							getBoundingBox().getBottomLeft()
						)+Vec2D(0,getBoundingBox().getHeight()*-1));
					normal_vec = Vec2D(0,1);
					break;

				case LEFTSIDE:
					setMove(
						lines[1].closestPoint(
							getBoundingBox().getTopLeft()
						)+Vec2D(getBoundingBox().getWidth()*-1, 0));
					normal_vec = Vec2D(-1,0);
					break;
					
				case RIGHTSIDE:
					setMove(
						lines[2].closestPoint(
							getBoundingBox().getTopRight()
						));
					normal_vec = Vec2D(1,0);
					break;
					
				case BOTTOMSIDE:
					setMove(
						lines[3].closestPoint(
							getBoundingBox().getTopLeft()
						)+Vec2D(0,getBoundingBox().getHeight()));
					normal_vec = Vec2D(0,-1);
					break;				
	
				default:
					break;
				}
				
				setDirection(getDirection().reflect(normal_vec));
		
			}
}

