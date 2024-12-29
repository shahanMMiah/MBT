#include <controller.h>
#include <SDL2/SDL.h>

Controller::Controller()
{}

bool Controller::update(uint32_t delta_time)
{
    SDL_Event SDLEvent;
    while(SDL_PollEvent(&SDLEvent))
    {
        switch (SDLEvent.type)
        {
        case SDL_QUIT:
            return false;
            
        case SDL_KEYUP:
        case SDL_KEYDOWN:
            inputFunction_t func = getKeyFunc(SDLEvent.key.keysym.sym);
            func(delta_time);
            
        }
    
    }
		
    return true;
}

inputFunction_t Controller::getKeyFunc(SDL_Keycode key)
{
    for(auto iter:mControlInputs)
    {
        if (key == iter.sym)
        {
            return iter.func;
        }
    }
    return [](uint32_t delta_time){}; // empty labmda    
}    
