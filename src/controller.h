#ifndef SRC_CONTROLLER_H_
#define SRC_CONTROLLER_H_

#include<cmath>
#include<SDL2/SDL.h>
#include<vector>
#include <functional>

typedef std::function<void(uint32_t delta_time)> inputFunction_t;


typedef struct ControlInput
{
    SDL_Keycode sym;
    inputFunction_t func;

} controlInput_t;

class Controller
{
    public:
    
    std::vector<controlInput_t> mControlInputs;

    Controller();

    bool update(uint32_t delta_time);
    inputFunction_t getKeyFunc(SDL_Keycode key);
    void clearInputs(){mControlInputs.clear();}
        

    
        
};

#endif /* SRC_CONTROLLER_H_ */


