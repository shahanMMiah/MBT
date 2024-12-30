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
    inline Vec2D getPos(){return mPos;}

    inline int getWidth(){return mWidth;}
    inline int getHeight(){return mHeight;}

    virtual void reset();
    inline Rectangle &getBoundingBox(){return mBoundingBox;}
    

    protected:
        Vec2D mPos; 
        Rectangle mBoundingBox;
        int mWidth;
        int mHeight;
        Vec2D mDirection;
        int mSpeed=10;
};

#endif /* SRC_OBJECT_H_ */