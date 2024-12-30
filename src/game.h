#ifndef SRC_GAME_H
#define SRC_GAME_H

#include <graphics.h>
#include <player.h>
#include <wall.h>
#include <controller.h>
#include <vector>
#include <bubble.h>
#include <needle.h>
#include <door.h>
#include <level.h>


class Game
{
    public:
        Game(GameWindow& window);
        void draw(GameWindow& window ,uint32_t delta_time);
        bool update(uint32_t delta_time);

        
        void checkWallBounce();
        void groundPlayer();
        void setupPlayerControls();
        void checkNeedleHit();
        void checkBubblePopped();
        void resizeBubbles(std::vector<Bubble>& other);
        void addNeedle();
        void popNeedle();
        void setLevel(int levelNum);

    private:
    Player mPlayer;
    Controller mController;
    std::vector<Wall> mWalls;
    std::vector<Door> mDoors;
    std::vector<Bubble> mBubbles;
    std::vector<Needle> mNeedles;
    std::vector<Level> mLevels;
    nlohmann::json mLevelData;
    int mCurrentLevel =0;



    
    
};


#endif /* SRC_GAME_H_ */