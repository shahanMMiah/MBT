#include <object.h>
#include <utils.h>
#include<graphics.h>
#include<color.h>
#include<line2d.h>

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

Vec2D Object::checkCollision(Rectangle &boundingBox)
{
	Vec2D normal_vec = Vec2D::Zero;
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
        }
    return normal_vec;
}