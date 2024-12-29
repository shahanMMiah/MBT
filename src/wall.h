#ifndef SRC_WALL_H_
#define SRC_WALL_H_

#include <rectangle.h>
#include <vector2d.h>
#include <object.h> 

class GameWindow;
class Wall : Object
{
    public:
    Wall();
    Wall(Vec2D pos, int width, int height);

    virtual void draw(GameWindow &window) override;

    inline Rectangle &getBoundingBox(){return mBoundingBox;}
    
    private:
    Vec2D mPos;
    Rectangle mBoundingBox;

    


};


#endif /* SRC_WALL_H_ */