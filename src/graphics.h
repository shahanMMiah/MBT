#ifndef SRC_GRAPHICS_H_
#define SRC_GRAPHICS_H_

#include <stdint.h>
#include <vector>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>



class Color;
class Vec2D;
class Line2D;
class Rectangle;


typedef struct Pixel_points PixelPoints_t;  

class GameWindow
{
    public:

        GameWindow();
        GameWindow(Color& color);

        ~GameWindow();

        SDL_Window* init(uint32_t w, uint32_t h, uint32_t mag);
        void clear(SDL_Surface* surface);
        void clear();
        void flip();
        void setPixel(int x, int y, Color& color);
        uint32_t getIndex(int r, int c);
        inline SDL_Surface* getBacksurface() {return mBackSurface;}
        inline SDL_Surface* getSurface() {return mSurface;}
        
        void draw(PixelPoints_t &pixels, Color color);  
        void draw(int x, int y, Color color);
        void draw(Line2D line, Color color);
        void draw(std::string sentence, Rectangle& destSpace, Color color);
        void draw(std::string sentence, Vec2D pos, int width, int height, Color color);

        void resize();
        
    
    private:
        
        SDL_Window* mWindow;
        SDL_Surface* mSurface;
        SDL_Surface* mBackSurface;
        Color* mBackground;
        
        SDL_Renderer* mRenderer;
        SDL_PixelFormat* mPixelFormat;
        SDL_Texture* mTexture;
        TTF_Font* mFont;
        
        
};




#endif /* SRC_GRAPHICS_H_ */