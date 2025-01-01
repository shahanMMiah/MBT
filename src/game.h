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
#include <dialog.h>


typedef enum gamesStates{
    PLAY,
    PAUSE,
    DIED,
    SETUP,
    CUSTCENE

    

} GameStates_t; 

class Game
{
    public:
        Game(GameWindow& window);
        void draw(GameWindow& window ,uint32_t delta_time);
        bool update(uint32_t delta_time);

        
        void checkWallBounce();
        void checkWin();
        void setupPlayerControls();
        void checkNeedleHit();
        void checkBubblePopped();
        void resizeBubbles(std::vector<Bubble>& other);
        void addNeedle();
        void popNeedle();
        void addLevel(int levelNum);
        void setLevel(int levelNum);
        void checkPlayerWalls();
        void checkPlayerHit();
        void checkLives();
        void checkLevelTime();
        


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
    int mLives = 3;
    GameStates_t mState;
    Dialog mPauseScreen;



    
    
};


#endif /* SRC_GAME_H_ */