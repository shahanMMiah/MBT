#ifndef SRC_LINE2D_H_
#define SRC_LINE2D_H_


#include <vector2d.h>

typedef struct Pixel_points PixelPoints_t;  


class Line2D
{
public:

	Line2D();
	Line2D(const Vec2D vec0,const Vec2D vec1);
	Line2D(float x0, float x1, float y0, float y1);

	inline const Vec2D& getP0() const {return mPoint0;}
	inline const Vec2D& getP1()const {return mPoint1;}

	inline void setP0(const Vec2D& p0){mPoint0 = p0;}
	inline void setP1(const Vec2D& p1){mPoint1 = p1;}

	bool operator == (const Line2D & otherLine);
	float minDistanceFrom(const Vec2D& p,bool limiToSegment = false) const;
	Vec2D closestPoint(const Vec2D& p,bool limiToSegment = false) const;

	Vec2D midPoint() const;
	float slope() const;
	float length() const;

	PixelPoints_t getPixels() const;









private:
	Vec2D mPoint0;
	Vec2D mPoint1;

};


#endif /* SRC_LINE2D_H_ */
