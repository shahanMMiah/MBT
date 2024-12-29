#ifndef SRC_SHAPE_H_
#define SRC_SHAPE_H_

#include <vector2d.h>
#include <utils.h>
#include <vector>


class Shape
{
public:
	virtual Vec2D getCenterPoint() const = 0;
	inline virtual std::vector<Vec2D> getPoints() const {return ShapePoints;}

	virtual void moveBy(const Vec2D& delta);
	virtual void moveTo(const Vec2D& delta);
	virtual void rotateBy(const Vec2D& aroundPoint,const float angle);
    PixelPoints_t getFilledPixels(const std:: vector<Vec2D>& points);


	virtual ~Shape() {}

protected:
	std:: vector<Vec2D> ShapePoints;

};



#endif /* SRC_SHAPE_H_ */
