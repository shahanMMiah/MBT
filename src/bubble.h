#ifndef SRC_BUBBLE_H_
#define SRC_BUBBLE_H_

#include <rectangle.h>
#include <utils.h>
#include <nlohmann/json.hpp>


class GameWindow;
class Object;

class Bubble: public Object
{
    public:
        Bubble();
        Bubble(Vec2D pos, int size);
        Bubble(Vec2D pos, int size, int side);
        
         
        virtual void draw(GameWindow &window) override;
        
   
        virtual void update() override;
        void checkBounce(Rectangle &boundingBox);
       
        inline void setPos(Vec2D delta){mPos=delta;}
        inline void setPopped(bool pop){mPopped = pop;} 
        inline void setSize(int size){mSize= size;}

        inline bool getPopped(){return mPopped;}
        inline int getSize(){return mSize;}
         


    private:
        
        int mSpeed;
        float mFallRate = DEFAULT_BUBBLE_FALLRATE;
        float mSideDir = DEFAULT_BUBBLE_SIDE;
        bool mPopped = false;
        int mSize = 3;
        nlohmann::json mSizeData = {{"1", 20},{"2", 40},{"3", 60},{"4", 80}};


        
 

};

#endif /* SRC_BUBBLE_H_ */