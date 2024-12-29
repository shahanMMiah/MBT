#ifndef SRC_DOOR_H_
#define SRC_DOOR_H_

#include <object.h>
#include <wall.h>

class Bubble;

class Door : public Object
{
    public:
        Door();
        Door(Vec2D pos, Rectangle rect, int doorWidth, int doorHeight, sideNames_t mSide);
        virtual void draw(GameWindow &window) override;
        virtual void update() override;
        inline bool getOpen(){return mOpen;}
        inline void setOpen(bool open){mOpen = open;}

        Rectangle &getTopBoundingBox(){return mTopWall.getBoundingBox();}
        Rectangle &getDoorBoundingBox(){return mDoorWall.getBoundingBox();}
        
        void checkIfOpen(std::vector<Bubble> &bubbles);
        
    
    private:
        sideNames_t mSide;
        Wall mTopWall;
        Wall mDoorWall;
        bool mOpen = false;
        

};

#endif /* SRC_DOOR_H_ */