#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include<vector>

const float TWOPI =  2.0f * PI;

const float GRAVITY = 9.8f;
const float TIMESTEP = 0.25f;
const float TIMESTEP2 = TIMESTEP*TIMESTEP;


const int DEFAULT_NEEDLE_AMOUNT = 2;
const int DEFAULT_NEEDLE_WIDTH = 2;
const int DEFAULT_NEEDLE_HEIGHT = 2;
const int DEFAULT_NEEDLE_SPEED = 32;

const float DEFAULT_BUBBLE_SIDE = 3.0f;
const int DEFAULT_BUBBLE_SIZE = 3;
const float DEFAULT_BUBBLE_FALLRATE = 8.0f;
const float DEFAULT_BUBBLE_OFFSET = 20.0f;

const float DEFAULT_POP_DISTANCE = 2.5f;

const int DEFAULT_WALL_THICKNESS = 30;
const int DEFAULT_DOOR_HEIGHT = 50;


typedef struct Pixel_points
{
    std::vector <int> xs;
    std::vector<int> ys;

} PixelPoints_t;

typedef enum controlStates{
UP,
DOWN,
LEFT,
RIGHT,
} controlStates_t;

typedef enum side_names {TOPSIDE,LEFTSIDE,RIGHTSIDE,BOTTOMSIDE}sideNames_t;

#endif /* SRC_UTILS_H_ */


