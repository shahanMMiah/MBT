#include <graphics.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <color.h>
#include <cassert>
#include <vector2d.h>
#include <line2d.h>
#include <vector>
#include <utils.h>
#include<algorithm>

GameWindow:: GameWindow():  mWindow(nullptr),
                            mSurface(nullptr),
                            mBackSurface(nullptr),
                            mBackground(nullptr)

{
   
}

GameWindow:: GameWindow(Color& color):  mWindow(nullptr),
                            mSurface(nullptr),
                            mBackSurface(nullptr),
                            mBackground(&color)

{
   
}

SDL_Window* GameWindow:: init(uint32_t w, uint32_t h, uint32_t mag)
{
    if(SDL_Init(SDL_INIT_VIDEO))
	{
		std::cout<<"Error SDL_Init failed" << std::endl;

	}
 
    mWindow = SDL_CreateWindow("MBT",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,w,h,SDL_WINDOW_RESIZABLE);

    mSurface = SDL_GetWindowSurface(mWindow);
    
    const SDL_PixelFormat* pixelFormat = mSurface-> format;
	Color::initColorFormat(pixelFormat);

    std::cout<<"using graphics class" << std::endl;
    
    mBackSurface = SDL_CreateRGBSurfaceWithFormat(0, mSurface->w,
					mSurface->h, 0 , mSurface->format->format
					);
    clear(mBackSurface);
    
    return mWindow;
}

void GameWindow:: clear(SDL_Surface* surface)
{   

    uint32_t col = mBackground == nullptr? Color::black().getPixelColor() : mBackground->getPixelColor();
    SDL_FillRect(surface, nullptr, col); 
}

void GameWindow:: flip()
{
    clear(mSurface);
    SDL_BlitScaled(mBackSurface, nullptr,mSurface,nullptr);
    SDL_UpdateWindowSurface(mWindow);
    clear(mBackSurface);
}

void GameWindow:: setPixel(int x, int y, Color& color)
{
    assert(mBackSurface);
    if(x < mBackSurface->w && x >= 0 && y < mBackSurface->h && y >= 0)
    {
        SDL_LockSurface(mBackSurface);
        uint32_t * pixels = (uint32_t*)mBackSurface->pixels;
        uint32_t index = getIndex(x,y); 
        Color surfaceColor = Color(pixels[index]);
	    
        pixels[index] = Color::eval1MinSourceAlpha(color,surfaceColor).getPixelColor();

	    SDL_UnlockSurface(mBackSurface);
	
    }
}


uint32_t GameWindow:: getIndex(int r, int c)
{

	assert(mBackSurface);

	if(mBackSurface)
	{

	return c*mBackSurface->w + r;
	}
	return 0;
}

void GameWindow:: draw(int x, int y, Color col)
{
    setPixel(x, y, col);
}

void GameWindow::draw(PixelPoints_t &pixels, Color color)
{
	assert(pixels.xs.size() == pixels.ys.size());
	
	for(size_t iter = 0; iter < pixels.xs.size(); iter++ )
	{
		draw(pixels.xs[iter],pixels.ys[iter], color);
	}

}

void GameWindow:: draw(Line2D line, const Color color)
{
	assert(mWindow);
	
	PixelPoints_t pixels = line.getPixels();	
	draw(pixels, color);

}

void GameWindow::resize()
{
    mSurface = SDL_GetWindowSurface(mWindow);
    mBackSurface = SDL_CreateRGBSurfaceWithFormat(0, mSurface->w,
					mSurface->h, 0 , mSurface->format->format
					);
    clear(mBackSurface);

}


