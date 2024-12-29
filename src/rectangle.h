#ifndef SRC_RECTANGLE_H_
#define SRC_RECTANGLE_H_

#include <shape.h>

class Rectangle: public Shape
{
public:
	Rectangle();
	Rectangle(const Vec2D& topLeft, unsigned int width, unsigned int height);
	Rectangle(const Vec2D& topLeft,const Vec2D& bottomRight);

	Vec2D getTopLeft() const {return ShapePoints[0];}
	Vec2D getBottomRight() const {return ShapePoints[1];}
	Vec2D getTopRight() const  {return ShapePoints[2];}
	Vec2D getBottomLeft() const   {return ShapePoints[3];}

	inline void setTopLeft(const Vec2D& topLeft) {ShapePoints[0] = topLeft;}
	inline void setBottomRight(const Vec2D& bottomRight) {ShapePoints[1] = bottomRight;}
	inline void setTopRight(const Vec2D& topRight) {ShapePoints[2] = topRight;}
	inline void setBottomLeft(const Vec2D& bottomLeft) {ShapePoints[3] = bottomLeft;}
	

	float getWidth() const;
	float getHeight() const;


	virtual void moveBy(const Vec2D& delta) override;
	void moveBy(size_t vert_ind, const Vec2D& delta);
	virtual void moveTo(const Vec2D& delta) override;
	virtual Vec2D getCenterPoint() const override;



	bool intersects(const Rectangle& otherRect) const;
	bool containsPoint(const Vec2D& pnt) const;

	static Rectangle inset(const Rectangle& rect,Vec2D &inset);
	virtual std::vector<Vec2D> getPoints() const override;
};


#endif /* SRC_RECTANGLE_H_ */
