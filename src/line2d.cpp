/*
 * Line2D.cpp
 *
 *  Created on: 25 Jul 2021
 *      Author: sha
 */


#include <line2d.h>
#include<vector2d.h>
#include <cmath>
#include <utils.h>

Line2D::Line2D():Line2D(Vec2D::Zero,Vec2D::Zero)
{}

Line2D::Line2D(const Vec2D vec0,const Vec2D vec1):mPoint0(vec0),mPoint1(vec1)
{}


Line2D:: Line2D(float x0, float x1, float y0, float y1):Line2D(Vec2D(x0,y0),Vec2D(x1,y1))
{

}

bool Line2D:: operator == (const Line2D & otherLine)
{return this->getP0() == otherLine.getP0() && this->getP1() == otherLine.getP1();}

float Line2D::minDistanceFrom(const Vec2D& p,bool limiToSegment) const
{
	return(p.distance(closestPoint(p)));
}
Vec2D Line2D::closestPoint(const Vec2D& p,bool limitToSegment) const
{
	// need to dot the point to the vector them times the scale values to vector, scale val = (v1 dot v2)/v2mag2

	Vec2D line = this->mPoint1 - this->mPoint0;
	Vec2D point = p -this->mPoint0;

	float scale = point.dot(line) / line.mag2();

	if(limitToSegment)
	{
		scale = std::fmax(0,std::fmin(1,scale));

	}
	return this->mPoint0+line*scale;
}
Vec2D Line2D::midPoint() const
{
	return (Vec2D((mPoint1.getX() + mPoint0.getX())/2.0f,
			(mPoint1.getY() +  mPoint0.getY())/2.0f));

}

float Line2D::slope() const
{
	float subX = mPoint0.getX() -mPoint1.getX();
	float subY = mPoint0.getY()-mPoint1.getY();
	if(fabsf(subX) > EPSILON and fabsf(subY) > EPSILON)
	{
		return(subX/subY);
	}
	return(0);
}

float Line2D::length() const
{return(mPoint1 - mPoint0).mag();}


PixelPoints_t Line2D::getPixels() const
{
	int x0 = roundf(getP0().getX());
	int x1 = roundf(getP1().getX());
	int y0 = roundf(getP0().getY());
	int y1 = roundf(getP1().getY());

	int dx = x1-x0; // line run
	int dy = y1-y0; // line rise


	signed const char ix((dx>0)-(dx<0)); // either 1 or - 1
	signed const char iy((dy>0)-(dy<0)); // either 1 or - 1

	dx = abs(dx) * 2;
	dy = abs(dy) * 2;

	PixelPoints_t pixels;
	
	
	if (dx >= dy) //if run len is longer than rise, (under halfway)
	{


		int d = dy - dx/2;

		while(x0 != x1)
		{
			if(d >= 0)
			{

				d -= dx;
				y0 += iy;
			}

			d+= dy;
			x0 += ix;

			pixels.xs.push_back(x0);
			pixels.ys.push_back(y0);
	
		}
	}
	else
	{

		int d = dx - dy/2;
		while(y0 != y1)
		{
			if(d >= 0)
			{
				d -= dy;
				x0 += ix;
			}
			d+= dx;
			y0 += iy;
			
			pixels.xs.push_back(x0);
			pixels.ys.push_back(y0);
		}
	}
	return pixels;
}
