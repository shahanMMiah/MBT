#ifndef SRC_OBJECT_H_
#define SRC_OBJECT_H_

#include<vector2d.h>
#include<rectangle.h>

class GameWindow;

class Object
{
    public:

    virtual void draw(GameWindow &window);
    virtual void update();

    void move(){mPos += mDirection;mBoundingBox.moveBy(mDirection);}
    inline void setMove(Vec2D pos){mPos = pos;mBoundingBox.moveTo(pos);}
    inline void setDirection(Vec2D delta){mDirection=delta;}
    
    inline Vec2D getPos(){return mPos;}
    inline Vec2D getDirection(){return mDirection;}
    inline int getWidth(){return mWidth;}
    inline int getHeight(){return mHeight;}
    inline Rectangle &getBoundingBox(){return mBoundingBox;}

    virtual void reset();
    Vec2D checkCollision(Rectangle &boundingBox);
    

    protected:
        Vec2D mPos; 
        Rectangle mBoundingBox;
        int mWidth;
        int mHeight;
        Vec2D mDirection;
        int mSpeed=10;
};

#endif /* SRC_OBJECT_H_ */