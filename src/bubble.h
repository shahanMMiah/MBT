#ifndef SRC_BUBBLE_H_
#define SRC_BUBBLE_H_

#include <rectangle.h>
#include <utils.h>
#include <nlohmann/json.hpp>

class GameWindow;

class Bubble
{
    public:
        Bubble();
        Bubble(Vec2D pos, int size);
        Bubble(Vec2D pos, int size, int side);
        
        
        void draw(GameWindow &window);
        
        void moveDir(controlStates_t dir);
        void update();
        void checkBounce(Rectangle &boundingBox);
        
        inline Rectangle &getBoundingBox(){return mBoundingBox;}
        inline Vec2D getPos(){return mPos;}
        inline Vec2D getDirection(){return mDirection;}
        inline void move(){mPos += mDirection;mBoundingBox.moveBy(mDirection);}
        inline void setMove(Vec2D pos){mPos = pos;mBoundingBox.moveTo(pos);}

        inline void setDirection(Vec2D delta){mDirection=delta;}
        inline void setPos(Vec2D delta){mPos=delta;}
        inline void setPopped(bool pop){mPopped = pop;} 
        inline void setSize(int size){mSize= size;}

        inline bool getPopped(){return mPopped;}
        inline int getSize(){return mSize;}
         


    private:
        Vec2D mPos; 
        Rectangle mBoundingBox;
        int mWidth;
        int mHeight;
        Vec2D mDirection;
        int mSpeed;
        float mFallRate = DEFAULT_BUBBLE_FALLRATE;
        float mSideDir = DEFAULT_BUBBLE_SIDE;
        bool mPopped = false;
        int mSize = 3;
        nlohmann::json mSizeData = {{"1", 20},{"2", 40},{"3", 60},{"4", 80}};


        
 

};

#endif /* SRC_BUBBLE_H_ */