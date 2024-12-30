#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_

#include <rectangle.h>
#include <vector2d.h>
#include <vector> 
#include <needle.h>
#include <object.h>

class GameWindow;

class Player: public Object
{
    public:
        Player();
        Player(Vec2D pos, int width, int height);
        Player(Vec2D pos, Rectangle rect);    
        
        virtual void draw(GameWindow &window) override;
        virtual void update() override;

        void moveDir(controlStates_t dir);
      
        void setPos(Vec2D pos) {mPos = pos;mBoundingBox.moveTo(pos);}
        void moveFromBottom(Vec2D pos);
        size_t shoot(std::vector<Needle>& needles);

        Vec2D getBottomMid() {return (((mBoundingBox.getBottomLeft() - mBoundingBox.getBottomRight())/2) + mBoundingBox.getBottomLeft());}
        virtual void reset() override;
        void setSize(int size); 
        

    private:

     
        bool mStates[4]; //Forward,Backward,Left,Right
        bool mClimbing =false;
        
};



#endif /* SRC_PLAYER_H_ */
