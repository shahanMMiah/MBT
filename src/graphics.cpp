


#include <iostream>
#include <color.h>
#include <cassert>
#include <vector2d.h>
#include <line2d.h>
#include <vector>
#include <utils.h>
#include<algorithm>
#include <graphics.h>
#include <rectangle.h>



GameWindow:: GameWindow():  mWindow(nullptr),
                            mSurface(nullptr),
                            mBackSurface(nullptr),
                            mBackground(nullptr),
                            mRenderer(nullptr),
                            mPixelFormat(nullptr),
                            mTexture(nullptr)

{    
}

GameWindow:: GameWindow(Color& color):  mWindow(nullptr),
                            mSurface(nullptr),
                            mBackSurface(nullptr),
                            mBackground(&color),
                            mRenderer(nullptr),
                            mPixelFormat(nullptr),
                            mTexture(nullptr)


{
}

GameWindow::~GameWindow()
{
    
    if (mPixelFormat)
    {
        SDL_FreeFormat(mPixelFormat);
        
    }

    if (mTexture)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
        
    }
    if (mRenderer)
    {
        SDL_DestroyRenderer(mRenderer);
        mRenderer =nullptr;
    }

    if(mWindow)
    {
        SDL_DestroyWindow(mWindow);
        mWindow = nullptr;

    }

    if (TTF_WasInit())
    {
        TTF_CloseFont(mFont);
        mFont = nullptr;
    }
    TTF_Quit();
    SDL_Quit();

}

SDL_Window* GameWindow:: init(uint32_t w, uint32_t h, uint32_t mag)
{
    
    // sdl init
    if(SDL_Init(SDL_INIT_VIDEO))
	{
		std::cout<<"Error SDL_Init failed" << std::endl;

	}

    // font init
    if (TTF_Init() < 0) {
    std::cout << "Error initializing SDL_ttf: " << SDL_GetError();
}   
    
    mFont = TTF_OpenFont(FONT_PATH, FONTSIZE);
    if( mFont == NULL )
    {
        std::cout << ("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError()) << std::endl;
       
    }

    // png init
    int imgFormat = IMG_INIT_PNG;
    if(!(IMG_Init(imgFormat) & imgFormat))
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    }


    mWindow = SDL_CreateWindow("MBT",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,w,h,SDL_WINDOW_RESIZABLE);

    mRenderer = SDL_CreateRenderer(mWindow,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    uint8_t clearCol = 0;
    uint8_t alphaCol = 0;
    
    SDL_SetRenderDrawColor(mRenderer,clearCol,clearCol,clearCol,alphaCol);

    mPixelFormat = SDL_AllocFormat(SDL_GetWindowPixelFormat(mWindow));
    mTexture = SDL_CreateTexture(mRenderer,mPixelFormat->format,SDL_TEXTUREACCESS_STREAMING, w, h);

	Color::initColorFormat(mPixelFormat);
    
    mBackSurface = SDL_ConvertSurface(
        SDL_CreateRGBSurfaceWithFormat(0, w,
					h, 0 , mPixelFormat->format
					),mPixelFormat,0);
    
    clear(mBackSurface);
    
    return mWindow;
}

void GameWindow:: clear(SDL_Surface* surface)
{   

    uint32_t col = mBackground == nullptr? Color::black().getPixelColor() : mBackground->getPixelColor();
    SDL_FillRect(surface, nullptr, col); 
}

void GameWindow:: clear()
{   

    SDL_RenderClear(mRenderer);
}

void GameWindow:: flip()
{
    clear();
    mTexture = SDL_CreateTextureFromSurface(mRenderer,mBackSurface);
    SDL_RenderCopy(mRenderer,mTexture,nullptr,nullptr);
    SDL_RenderPresent(mRenderer);
    
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

void GameWindow::draw(SDL_Surface* surface, SDL_Rect* src_rect,SDL_Rect* trg_rect)
{
    
    surface = SDL_ConvertSurface(surface, mPixelFormat, 0);
    SDL_BlitScaled(surface,src_rect,mBackSurface, trg_rect);

    if (src_rect != nullptr)
    {
        free(src_rect);
    }
    if (trg_rect != nullptr)
    {
        free(trg_rect);
    }

    SDL_FreeSurface(surface);


}

void GameWindow::draw(std::string sentence, Rectangle&  destSpace,Color color)
{
    
    SDL_Color textColor = {color.getRed(),color.getBlue(),color.getGreen()};
    SDL_Surface* textSurface = TTF_RenderText_Solid( mFont, sentence.c_str(),textColor);
    SDL_Rect* ownRectPtr = destSpace.getSDLRect();
    draw(textSurface,nullptr, ownRectPtr);
    textSurface = nullptr;
    ownRectPtr = nullptr;

}

void GameWindow::draw(std::string sentence, Vec2D pos, int width, int height, Color color)
{
    SDL_Color textColor = {color.getRed(),color.getBlue(),color.getGreen()};
    SDL_Surface* textSurface = TTF_RenderText_Solid( mFont, sentence.c_str(),textColor);
    SDL_Rect* ownRectPtr = Rectangle(pos,width,height).getSDLRect();

    draw(textSurface,nullptr, ownRectPtr);
    textSurface = nullptr;
    ownRectPtr = nullptr;
    

}

void GameWindow::draw(std::filesystem::path img, Rectangle& srcSpace, Rectangle& destSpace)
{
    SDL_Surface * imgSurface = IMG_Load(img.c_str());
    SDL_Rect* src_rect = srcSpace.getSDLRect();
    SDL_Rect* dst_rect = destSpace.getSDLRect();

    draw(imgSurface, src_rect, dst_rect);

    imgSurface = nullptr;
    src_rect = nullptr;
    dst_rect = nullptr;

}
        

void GameWindow::resize()
{
    mSurface = SDL_GetWindowSurface(mWindow);
    mBackSurface = SDL_CreateRGBSurfaceWithFormat(0, mSurface->w,
					mSurface->h, 0 , mSurface->format->format
					);
    clear(mBackSurface);

}


