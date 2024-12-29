#ifndef SRC_COLOR_H_
#define SRC_COLOR_H_

#include<stdint.h>


struct SDL_PixelFormat; // foward delcare means we dont have to include SDL2.h
						// unless it needs to use the module in anyway beside knowing it exist

class Color
{
	public:

	static const SDL_PixelFormat* mformat; //get pointer to pixel format
	static void initColorFormat(const SDL_PixelFormat* format);//init pixel format
	static Color eval1MinSourceAlpha(const Color& source,const Color& dest);

	Color(): mColor(0){}
	Color(uint32_t color): mColor(color){}
	Color(uint8_t r,uint8_t g,uint8_t b,uint8_t a);


	inline bool operator==(const Color&c) const {return this->mColor == c.mColor;}
	inline bool operator!=(const Color&c) const {return this->mColor != c.mColor;}
	inline uint32_t getPixelColor() const{return this->mColor;}

	void setRGBA(uint8_t r,uint8_t g,uint8_t b,uint8_t a);

	void setRed(uint8_t r);
	void setGreen(uint8_t g);
	void setBlue(uint8_t b);
	void setAlpha(uint8_t a);

	uint8_t getRed() const;
	uint8_t getGreen() const;
	uint8_t getBlue() const;
	uint8_t getAlpha() const;

	static Color black(){return Color(0,0,0,255);}
	static Color white(){return Color(255,255,255,255);}
	static Color red(){return Color(255,0,0,255);}
	static Color green(){return Color(0,255,0,255);}
	static Color blue(){return Color(0,0,255,255);}
	static Color yellow(){return Color(255,255,0,255);}
	static Color magenta(){return Color(255,0,255,255);}
	static Color cyan(){return Color(37,240,217,255);}
	static Color pink(){return Color(245,197,224,255);}
	static Color orange(){return Color(245,190,100,255);}




	private:
	uint32_t mColor;
	float refAlpha;



};


#endif /* SRC_COLOR_H_ */
