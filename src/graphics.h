#ifndef SRC_GRAPHICS_H_
#define SRC_GRAPHICS_H_

#include <stdint.h>
#include <vector>


class SDL_Window;
class SDL_Surface;
class Color;
class Vec2D;
class Line2D;


typedef struct Pixel_points PixelPoints_t;  

class GameWindow
{
    public:

        GameWindow();
        GameWindow(Color& color);

        SDL_Window* init(uint32_t w, uint32_t h, uint32_t mag);
        void clear(SDL_Surface* surface);
        void flip();
        void setPixel(int x, int y, Color& color);
        uint32_t getIndex(int r, int c);
        inline SDL_Surface* getBacksurface() {return mBackSurface;}
        inline SDL_Surface* getSurface() {return mSurface;}
        
        void draw(PixelPoints_t &pixels, Color color);  
        void draw(int x, int y, Color color);
        void draw(Line2D line, Color color); 
        void resize();
        
    
    private:
        
        SDL_Window* mWindow;
        SDL_Surface* mSurface;
        SDL_Surface* mBackSurface;
        Color* mBackground;
        
        
};




#endif /* SRC_GRAPHICS_H_ */