#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include<vector>
#include <nlohmann/json.hpp>
#include <filesystem>

const std::filesystem::path assetsPath = ASSETS_PATH;
const std::filesystem::path fontPath = FONT_PATH;

const int DEFAULT_WINDOW_WIDTH = 1080;
const int DEFAULT_WINDOW_HEIGHT = 720;

const float TWOPI =  2.0f * PI;
const float GRAVITY = 9.8f;
const float TIMESTEP = 0.25f;
const float TIMESTEP2 = TIMESTEP*TIMESTEP;

const int DEFAULT_PLAYER_SIZE = 30;

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


const int DEFAULT_DIALOG_WIDTH = 500;
const int DEFAULT_DIALOG_HEIGHT = 250;

const int FONTSIZE = 200;


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

typedef enum cutsceneLevelStates{
LEVEL_START_STATE,
LEVEL_PLAY_STATE,
LEVEL_END_STATE,
LEVEL_PAUSE_STATE
} CutsceneLevelStates_t;



typedef enum side_names {TOPSIDE,LEFTSIDE,RIGHTSIDE,BOTTOMSIDE}sideNames_t;

const nlohmann::json DEFAULT_LEVEL_DATA = {
    {
        "0", {
                {"player", {{"x", 50}, {"y", 500},{"size", DEFAULT_PLAYER_SIZE}}},
                {"bubbles", {
                        {{"size", 2}, {"x", DEFAULT_WINDOW_WIDTH/2 + 250}, {"y", DEFAULT_WINDOW_HEIGHT/2}, {"size", DEFAULT_BUBBLE_SIZE}, {"side", DEFAULT_BUBBLE_SIDE}},
                        
                        }},
                {"doors",{
                     
                }},
                {"walls",{
                        {
                        // base bottom
                        {"width",DEFAULT_WINDOW_WIDTH},{"height",DEFAULT_WALL_THICKNESS }, {"x", 0}, {"y", DEFAULT_WINDOW_HEIGHT-DEFAULT_WALL_THICKNESS}, {"directionX",3},{"directionY",0},
                        },
                        // base left
                        {
                        {"width",DEFAULT_WALL_THICKNESS},{"height",DEFAULT_WINDOW_HEIGHT }, {"x", 0}, {"y",0}, {"directionX",3},{"directionY",0},
                        },
                        // base right
                        {
                        {"width",DEFAULT_WALL_THICKNESS},{"height",DEFAULT_WINDOW_HEIGHT }, {"x", DEFAULT_WINDOW_WIDTH-DEFAULT_WALL_THICKNESS}, {"y",0}, {"directionX",3},{"directionY",0},
                        },
                        // base top
                        {
                        {"width",DEFAULT_WINDOW_WIDTH},{"height",DEFAULT_WALL_THICKNESS }, {"x", 0}, {"y",0}, {"directionX",3},{"directionY",0},
                        }
                    }
                },
                {"needles",1},
                {"timeLimit", 30},    
                {"items",{{"type", "extraNeedle"}, {"x", 50}, {"y", 50}}},
                {"cutscenes",{
                    {{"message","SOME DIALOG"}, {"width", DEFAULT_DIALOG_WIDTH+100},{"height", DEFAULT_DIALOG_HEIGHT+100},{"state",LEVEL_START_STATE}},
                    {{"message","press space to play"}, {"width", DEFAULT_DIALOG_WIDTH-100},{"height", DEFAULT_DIALOG_HEIGHT-100},{"state",LEVEL_START_STATE}},
                    {{"message", "well done"}, {"width", DEFAULT_DIALOG_WIDTH},{"height", DEFAULT_DIALOG_HEIGHT},{"state",LEVEL_END_STATE}}
                    }},

                {"window", {{"width",DEFAULT_WINDOW_WIDTH}, {"height", DEFAULT_WINDOW_HEIGHT}}}    
        },
        
        
    },
    {
        "1", {
                {"player", {{"x", 50}, {"y", 500},{"size", DEFAULT_PLAYER_SIZE}}},
                {"bubbles", {
                        {{"size", 3}, {"x", DEFAULT_WINDOW_WIDTH/2 + 250}, {"y", DEFAULT_WINDOW_HEIGHT/2}, {"size", DEFAULT_BUBBLE_SIZE}, {"side", DEFAULT_BUBBLE_SIDE}},
                        {{"size", 2}, {"x", DEFAULT_WINDOW_WIDTH/2 - 250}, {"y", DEFAULT_WINDOW_HEIGHT/2}, {"size", DEFAULT_BUBBLE_SIZE}, {"side", DEFAULT_BUBBLE_SIDE*-1}},
                        }},
                {"doors",{
                        {
                            {"boundingBoxWidth",DEFAULT_WINDOW_WIDTH/2},
                            {"boundingBoxHeight",DEFAULT_WINDOW_HEIGHT },
                            {"width",DEFAULT_WALL_THICKNESS},
                            {"height",DEFAULT_DOOR_HEIGHT}, {"x", 0}, {"y", 0}, {"side",RIGHTSIDE}
                        }
                }},
                {"walls",{
                        {
                        // base bottom
                        {"width",DEFAULT_WINDOW_WIDTH},{"height",DEFAULT_WALL_THICKNESS }, {"x", 0}, {"y", DEFAULT_WINDOW_HEIGHT-DEFAULT_WALL_THICKNESS}, {"directionX",3},{"directionY",0},
                        },
                        // base left
                        {
                        {"width",DEFAULT_WALL_THICKNESS},{"height",DEFAULT_WINDOW_HEIGHT }, {"x", 0}, {"y",0}, {"directionX",3},{"directionY",0},
                        },
                        // base right
                        {
                        {"width",DEFAULT_WALL_THICKNESS},{"height",DEFAULT_WINDOW_HEIGHT }, {"x", DEFAULT_WINDOW_WIDTH-DEFAULT_WALL_THICKNESS}, {"y",0}, {"directionX",3},{"directionY",0},
                        },
                        // base top
                        {
                        {"width",DEFAULT_WINDOW_WIDTH},{"height",DEFAULT_WALL_THICKNESS }, {"x", 0}, {"y",0}, {"directionX",3},{"directionY",0},
                        }
                    }
                },
                {"needles",1},
                {"timeLimit", 60},    
                {"items",{{"type", "extraNeedle"}, {"x", 50}, {"y", 50}}},
                {"cutscenes",{
                    {{"message","get ready"}, {"width", DEFAULT_DIALOG_WIDTH},{"height", DEFAULT_DIALOG_HEIGHT},{"state",LEVEL_START_STATE}},
                }},
                {"window", {{"width",DEFAULT_WINDOW_WIDTH}, {"height", DEFAULT_WINDOW_HEIGHT}}}

              
        }
        
    }    
    
};
	

#endif /* SRC_UTILS_H_ */




