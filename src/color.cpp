#include <graphics.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <color.h>

const SDL_PixelFormat* Color::mformat= nullptr;


Color:: Color(uint8_t r,uint8_t g,uint8_t b,uint8_t a)
{

	setRGBA(r,g,b,a);
	refAlpha = a;

}
void Color::initColorFormat(const SDL_PixelFormat* format)
{
	Color::mformat = format;
}

void Color:: setRGBA(uint8_t r,uint8_t g,uint8_t b,uint8_t a)
	{
	mColor = SDL_MapRGBA(Color::mformat, r,g,b,127);
	refAlpha= a;
	}

void Color:: setRed(uint8_t r)
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha;
	SDL_GetRGBA(mColor,Color::mformat, &red,&green,&blue,&alpha);
	setRGBA(r,blue,green,alpha);


}
void Color:: setGreen(uint8_t g)
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha;
	SDL_GetRGBA(mColor,Color::mformat, &red,&green,&blue,&alpha);
	setRGBA(red,blue,g,alpha);
}
void Color:: setBlue(uint8_t b)
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha;
	SDL_GetRGBA(mColor,Color::mformat, &red,&green,&blue,&alpha);
	setRGBA(red,b,green,alpha);
}
void Color:: setAlpha(uint8_t a)
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha;
	SDL_GetRGBA(mColor,Color::mformat, &red,&green,&blue,&alpha);
	setRGBA(red,blue,green,a);
	refAlpha= a;
}

uint8_t Color:: getRed() const
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha;
	SDL_GetRGBA(mColor,Color::mformat, &red,&green,&blue,&alpha);
	return(red);
}
uint8_t Color:: getGreen() const
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha;
	SDL_GetRGBA(mColor,Color::mformat, &red,&green,&blue,&alpha);
	return(green);
}
uint8_t Color:: getBlue() const
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha;
	SDL_GetRGBA(mColor,Color::mformat, &red,&green,&blue,&alpha);
	return(blue);
}
uint8_t Color:: getAlpha() const
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha;
	SDL_GetRGBA(mColor,Color::mformat, &red,&green,&blue,&alpha);
	return(refAlpha);
}

Color Color:: eval1MinSourceAlpha(const Color& source,const Color& dest)
{

	// formula new color = source color * source alpha + dest color * (1-dest alpha)

	float sourceAlpha = source.getAlpha()/255.0f;
	float destAlpha = 1.0f - sourceAlpha;
	Color outColor;

	uint8_t alpha = 255;
	uint8_t red = float(source.getRed()) * sourceAlpha + dest.getRed()*destAlpha;
	uint8_t green = float(source.getGreen()) * sourceAlpha + dest.getGreen()*destAlpha;
	uint8_t blue = float(source.getBlue()) * sourceAlpha + dest.getBlue()*destAlpha;
	outColor.setRGBA(red,green,blue,alpha);

	return outColor;

}
