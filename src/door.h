#ifndef SRC_DOOR_H_
#define SRC_DOOR_H_

#include <object.h>
#include <wall.h>


class Door : Object
{
    public:
        Door();
        Door(Vec2D pos, Rectangle rect, int width, int height);
        virtual void draw(GameWindow &window) override {};
        virtual void update() override {};
    private:
        sideNames_t mSide;
        Wall mTopWall;
        Wall mDoorWall;

};

#endif /* SRC_DOOR_H_ */