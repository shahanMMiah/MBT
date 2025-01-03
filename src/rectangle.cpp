/*
 * Rectangle.cpp
 *
 *  Created on: 28 Jun 2023
 *      Author: sha
 */


#include <rectangle.h>
#include <utils.h>
#include <cmath>
#include <vector>
#include <SDL2/SDL.h>


Rectangle::Rectangle():Rectangle(Vec2D::Zero,Vec2D::Zero)
{}

Rectangle::Rectangle(const Vec2D& topLeft, unsigned int width, unsigned int height)
{
	ShapePoints.push_back(topLeft); // top left
	ShapePoints.push_back(Vec2D(topLeft.getX()+width-1,topLeft.getY()+height-1)); // bot right
	ShapePoints.push_back(Vec2D(ShapePoints[1].getX(),ShapePoints[0].getY())); // top right
	ShapePoints.push_back(Vec2D(ShapePoints[0].getX(),ShapePoints[1].getY())); // bot left
	

}

Rectangle::Rectangle(const Vec2D& topLeft,const Vec2D& bottomRight)
{
	ShapePoints.push_back(topLeft);
	ShapePoints.push_back(bottomRight);
	ShapePoints.push_back(Vec2D(ShapePoints[1].getX(),ShapePoints[0].getY())); // top right
	ShapePoints.push_back(Vec2D(ShapePoints[0].getX(),ShapePoints[1].getY())); // bot left right
	
}




float Rectangle::getWidth() const
{
	return getBottomRight().getX() - getTopLeft().getX() + 1;

}
float Rectangle::getHeight() const
{
	return getBottomRight().getY() - getTopLeft().getY() + 1;
}


void Rectangle::moveBy(const Vec2D& delta)
{

	float width = getWidth();
	float height = getHeight();


	setTopLeft(getTopLeft()+delta);
	
	setBottomRight(
			Vec2D((getTopLeft().getX()+width-1),
			(getTopLeft().getY())+height-1));
	
	setTopRight(
			Vec2D((getTopLeft().getX()+width-1),
			(getTopLeft().getY())));
	
	setBottomLeft(
			Vec2D((getTopLeft().getX()),
			(getTopLeft().getY())+height-1));
}

void Rectangle::moveBy(size_t vert_ind, const Vec2D& delta)
{	
	ShapePoints[vert_ind] += delta;
}


void Rectangle::moveTo(const Vec2D& delta)
{

	float width = getWidth();
	float height = getHeight();


	setTopLeft(delta);


	setBottomRight(
			Vec2D((getTopLeft().getX()+width-1),
			(getTopLeft().getY())+height-1));
	
	setTopRight(
			Vec2D((getTopLeft().getX()+width-1),
			(getTopLeft().getY())));
	
	setBottomLeft(
			Vec2D((getTopLeft().getX()),
			(getTopLeft().getY())+height-1));

}




Vec2D Rectangle::getCenterPoint() const
{

	float add_x =  (getTopLeft().getX() * 2) + (getBottomRight().getX()*2);
	float add_y = (getTopLeft().getY() * 2) + (getBottomRight().getY()*2);

	return(Vec2D(add_x/4.0f,add_y/4.0f));



}

bool Rectangle::intersects(const Rectangle& otherRect) const
{
	return !(otherRect.getBottomRight().getX() < getTopLeft().getX() ||
			otherRect.getTopLeft().getX() > getBottomRight().getX()||
			otherRect.getBottomRight().getY() < getTopLeft().getY() ||
			otherRect.getTopLeft().getY() > getBottomRight().getY());
}

bool Rectangle::containsPoint(const Vec2D& pnt) const
{
	bool withinX = pnt.getX() >= getTopLeft().getX() && pnt.getX() <= getBottomRight().getX();
	bool withinY = pnt.getY() >= getTopLeft().getY() && pnt.getY() <= getBottomRight().getY();
	return withinX && withinY;

}

Rectangle Rectangle::inset(const Rectangle& rect,Vec2D &inset)
{
	return Rectangle(
			rect.getTopLeft()+inset,
			rect.getWidth() - 2*inset.getX(),
			rect.getHeight() - 2*inset.getY());
}
std::vector<Vec2D> Rectangle::getPoints() const
{
	std::vector<Vec2D> newVecArray;
	newVecArray.push_back(getBottomRight());
	newVecArray.push_back(getBottomLeft());
	newVecArray.push_back(getTopLeft());
	newVecArray.push_back(getTopRight());
	

	return newVecArray;

}


SDL_Rect* Rectangle::getSDLRect()
{
	SDL_Rect* rectPtr = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	rectPtr->x = int(getTopLeft().getX());
	rectPtr->y = int(getTopLeft().getY());
	rectPtr->w = int(getWidth());
	rectPtr->h = int(getHeight());
	
	return rectPtr;
}

SDL_Rect* Rectangle::getSDLRect(Vec2D pos, int width, int height)
{
	SDL_Rect* rectPtr = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	rectPtr->x = int(pos.getX());
	rectPtr->y = int(pos.getY());
	rectPtr->w = int(width);
	rectPtr->h = int(height);
	
	return rectPtr;
}


