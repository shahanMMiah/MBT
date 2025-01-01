#ifndef SRC_LEVEL_H_
#define SRC_LEVEL_H_

#include<vector>
#include <vector2d.h>
#include <nlohmann/json.hpp>
#include <string>


class Player;
class Wall;
class Bubble;
class Needle;
class Door;


class Level
{
    public:

    Level(nlohmann::json &data, int levelNum);
    
    void setPlayerPos(Player &player, Wall &wall);
    void setWalls(std::vector<Wall> &walls);
    void setDoors(std::vector<Door> &doors);
    void setBubbles(std::vector<Bubble> &bubbles);
    void setNeedles(std::vector<Needle> &needles);
    double getElapsedTime(){return (SDL_GetTicks() - mLevelTick) / 1000.0;};
    inline double getTimeLimit(){return mTimeLimit;}
    void setLevelTick(uint32_t tick){mLevelTick = tick;}

    //void setItems(std::vector<Item> &items);


    private:

    nlohmann::json mLevelData;
    std::string mLevel;
    uint32_t mLevelTick;
    double mTimeLimit;
     










    
    



};


#endif /* SRC_LEVEL_H_ */