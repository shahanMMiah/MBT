
#include <shape.h>
#include<iostream>
#include<algorithm> 

void Shape:: moveBy(const Vec2D& delta)
{

	for(Vec2D & iter: this->ShapePoints){
		iter += delta;

	}
}

void Shape:: moveTo(const Vec2D& delta)
{

	for(Vec2D & iter: this->ShapePoints){
		iter = delta;

	}
}

void Shape:: rotateBy(const Vec2D& aroundPoint,const float angle)
{
	for (Vec2D & point:ShapePoints){


		point.rotate(angle,aroundPoint);

	}
}

PixelPoints_t Shape::getFilledPixels(const std:: vector<Vec2D>& points)
{   
    PixelPoints_t pixels;


	if (points.size() > 0)
	{

		// initalise most far vals
		float top = points[0].getY();
		float btm = points[0].getY();
		float lft = points[0].getX();
		float rgt = points[0].getX();

		

		for(size_t i = 0;i < points.size(); ++i)
		{
			// get the most top botomm left right points
			if(points[i].getY() < top)
			{
				top = points[i].getY();
			}
			if(points[i].getY() > btm)
			{
				btm = points[i].getY();
			}
			if(points[i].getX() > rgt)
			{
				rgt = points[i].getX();
			}
			if(points[i].getX() < lft)
			{
				lft = points[i].getX();
			}
		}



		// for pixels Y coords starting from top to bottom
		for(int pixelY=top;pixelY<btm;++pixelY)
		{
			std::vector<float> nodexVec;
			size_t j = points.size() - 1;

			// for each point in list
			for(size_t i=0; i < points.size();++i)
			{
				// current scanline point y coord  in list and top point y coord
				float pointIY = points[i].getY();
				float pointJY = points[j].getY();

				// check if pixels Y coord is inside shape
				if((pointIY <= (float)pixelY &&
						pointJY > (float)pixelY)||
						(pointJY <= (float)pixelY &&
						pointIY > (float)pixelY))
				{
					float denom = pointJY - pointIY;
					if(IsEqual(denom,0))
					{
						continue;
					}


					// find x intersection points???
					float x = points[i].getX()+
							(pixelY - pointIY)/(denom) *
							(points[j].getX() - points[i].getX());


					nodexVec.push_back(x);

				}
				j = i;
			}

			// sort them in descending orders /pairs
			std::sort(nodexVec.begin(),nodexVec.end(),std::less<>());


			for (size_t k = 0;k < nodexVec.size();k+=2)
			{

				// make sure x insterction point are in the witdth boundry of shape
				if(nodexVec[k] > rgt)
				{
					break;
				}
				if(nodexVec[k+1] > lft)
				{
					if(nodexVec[k] < lft)
						{
							nodexVec[k] = lft;
						}

					if(nodexVec[k+1] > rgt)
						{
							nodexVec[k+1] = rgt;
						}

					// iter in between the pairs of x intersects and draw
					for(int pixelX = nodexVec[k];pixelX<nodexVec[k+1];++pixelX)
					{

						//std::cout<<"x-"<< pixelX<< " y-"<<pixelY<<std::endl;
						pixels.xs.push_back(pixelX);
						pixels.ys.push_back(pixelY);
					}
				}
			}
		}
    return pixels;    
	}
    return pixels;
}



