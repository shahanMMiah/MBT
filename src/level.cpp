#include <SDL2/SDL.h>
#include <level.h>
#include <algorithm>
#include <player.h>
#include <wall.h>
#include <bubble.h>
#include <needle.h>
#include <door.h>
#include <graphics.h>


Level::Level(nlohmann::json &data, int levelNum)
{

    mLevelData = data;
    mLevel = std::to_string(levelNum);
    mLevelTick = SDL_GetTicks();
    mTimeLimit = mLevelData[mLevel]["timeLimit"];
 
    
}

void Level::setPlayerPos(Player &player, Wall &wall)
{
    player.reset();
    player.setSize(mLevelData[mLevel]["player"]["size"]);
    player.setMove(Vec2D(mLevelData[mLevel]["player"]["x"],mLevelData[mLevel]["player"]["y"]));
    player.groundPlayer(wall.getBoundingBox());
}

void Level::setWalls(std::vector<Wall> &walls)
{
    walls.clear();
    for (auto wallData:mLevelData[mLevel]["walls"])
    {
        
        walls.push_back(
            Wall(Vec2D(wallData["x"], wallData["y"]), 
            wallData["width"], 
            wallData["height"], 
            Vec2D(wallData["directionX"],wallData["directionY"])
            )
        );
    }
}

void Level::setDoors(std::vector<Door> &doors)
{
    doors.clear();
    for (auto doorData:mLevelData[mLevel]["doors"])
    {
        doors.push_back(
            Door(
                Vec2D(doorData["x"],doorData["y"]), 
                Rectangle(
                    Vec2D(doorData["x"],doorData["y"]),
                    doorData["boundingBoxWidth"], 
                    doorData["boundingBoxHeight"] 
                ), 
                doorData["width"], 
                doorData["height"], 
                doorData["side"]
            )
        );
    }
}

void Level::setBubbles(std::vector<Bubble> &bubbles)
{
    bubbles.clear();
    for (auto bubbleData:mLevelData[mLevel]["bubbles"])
    {
        bubbles.push_back(
            Bubble(
                Vec2D(bubbleData["x"], bubbleData["y"]), 
                bubbleData["size"],
                bubbleData["side"]
            )
        );
    }

}


void Level::setNeedles(std::vector<Needle> &needles)
{
    needles.clear();
    for(int iter =0; iter < mLevelData[mLevel]["needles"]; iter++)

   {
		needles.push_back(Needle(Vec2D::Zero, DEFAULT_NEEDLE_WIDTH, DEFAULT_NEEDLE_HEIGHT));
		
	}
}

void Level::setupCutscenes()
{
    mCutScenes.clear();
    for (auto custsceneData:mLevelData[mLevel]["cutscenes"])
    {
        
        int width = custsceneData["width"];
        int height = custsceneData["height"];
        mCutScenes.push_back(
            Dialog(
                LEVEL_CUSTCENE, 
                Vec2D(
                    (int(mLevelData[mLevel]["window"]["width"])/2)-width/2,
                    (int(mLevelData[mLevel]["window"]["height"])/2)-height/2
                    ), 
                width,
                height,
                custsceneData["state"],
               custsceneData["message"]
                )
            );
    }
}

void Level::drawCutscene(GameWindow &window)
{
    if(mCutScenes.size() > mCutsceneNum )
    {
        mCutScenes[mCutsceneNum].setOn(true);
        mCutScenes[mCutsceneNum].draw(window);
    }
}

void Level::updateCutscene(uint32_t delta_num)
{
    if(mCutScenes.size() > mCutsceneNum )
    {
        getCutScene().update(delta_num);
    }
}