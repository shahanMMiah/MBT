#ifndef SRC_WALL_H_
#define SRC_WALL_H_

#include <rectangle.h>
#include <vector2d.h>
#include <object.h> 
#include <color.h>

class GameWindow;
class Wall : public Object
{
    public:
    Wall();
    Wall(Vec2D pos, int width, int height);
    Wall(Vec2D pos, int width, int height, Vec2D direction);

    virtual void draw(GameWindow &window) override;
    void draw(GameWindow &window,Color col);
    
    
 

    


};


#endif /* SRC_WALL_H_ */