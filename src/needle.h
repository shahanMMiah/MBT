#ifndef SRC_NEEDLE_H_
#define SRC_NEEDLE_H_

#include <object.h>
#include <rectangle.h>
class Player;

class Needle : Object
{
    public:
        
        Needle();
        Needle(Vec2D pos, int width, int height);
        inline void setLoaded(bool load){mLoaded = load;}
        inline void setHit(bool hit){mHit = hit;}
        
        inline bool getHit(){return mHit;}
        inline bool getLoaded(){return mLoaded;}
        
        virtual void update() override;
        virtual void draw(GameWindow &window) override;
        bool checkCollided(const Rectangle& other);
        void setPos(Vec2D pos);
        void shoot();
        

        



    private:
        Rectangle mStringBoundingBox;
        bool mLoaded;
        bool mHit;




    
};

#endif /* SRC_NEEDLE_H_ */
