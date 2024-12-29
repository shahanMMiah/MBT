#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_

#include <rectangle.h>
#include <vector2d.h>
#include <vector> 
#include <needle.h>

class GameWindow;

class Player
{
    public:
        Player();
        Player(Vec2D pos, int width, int height);
        Player(Vec2D pos, Rectangle rect);    
        void draw(GameWindow &window);
        void update();

        void moveDir(controlStates_t dir);
        inline void move(){mPos += mDirection;mBoundingBox.moveBy(mDirection);}
        inline Vec2D getPos(){return mPos;}
        void setPos(Vec2D pos) {mPos = pos;mBoundingBox.moveTo(pos);}
        void moveFromBottom(Vec2D pos);
        size_t shoot(std::vector<Needle>& needles);

        inline int getWidth(){return mWidth;}
        inline int getHeight(){return mHeight;}
        Vec2D getBottomMid() {return (((mBoundingBox.getBottomLeft() - mBoundingBox.getBottomRight())/2) + mBoundingBox.getBottomLeft());}

    private:

        Vec2D mPos; 
        Rectangle mBoundingBox;
        int mWidth;
        int mHeight;
        Vec2D mDirection;
        int mSpeed=10;
        bool mStates[4]; //Forward,Backward,Left,Right
        bool mClimbing =false;
        
};



#endif /* SRC_PLAYER_H_ */
