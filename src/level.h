#ifndef SRC_LEVEL_H_
#define SRC_LEVEL_H_

#include<vector>
#include <vector2d.h>
#include <nlohmann/json.hpp>
#include <string>
#include <dialog.h>


class Player;
class Wall;
class Bubble;
class Needle;
class Door;
class GameWindow;


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
    
    inline void incrementCutscene(){mCutsceneNum++;}
    void setupCutscenes();
    void drawCutscene(GameWindow& window);
    void updateCutscene(uint32_t delta_num);

    Dialog &getCutScene(){return mCutScenes[mCutsceneNum];}
    std::vector<Dialog> &getCutScenes(){return mCutScenes;}
    int getCutsceneSize(){return mCutScenes.size();}
    int getCutsceneNum(){return mCutsceneNum;}
    
    void setLevelState(CutsceneLevelStates_t state){mLevelState = state;}
    CutsceneLevelStates_t getLevelState(){return mLevelState;}

    //void setItems(std::vector<Item> &items);


    private:

    nlohmann::json mLevelData;
    std::string mLevel;
    uint32_t mLevelTick;
    double mTimeLimit;
    std::vector<Dialog> mCutScenes;
    int mCutsceneNum = 0;
    CutsceneLevelStates_t mLevelState = LEVEL_PLAY_STATE;









    
    



};


#endif /* SRC_LEVEL_H_ */