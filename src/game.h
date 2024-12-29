#ifndef SRC_GAME_H
#define SRC_GAME_H

#include <graphics.h>
#include <player.h>
#include <wall.h>
#include <controller.h>
#include <vector>
#include <bubble.h>
#include <needle.h>

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


    private:
    Player mPlayer;
    Controller mController;
    std::vector<Wall> mWalls;
    std::vector<Bubble> mBubbles;
    std::vector<Needle> mNeedles;
    
};


#endif /* SRC_GAME_H_ */