#include <SDL2/SDL.h>
#include <nlohmann/json.hpp>
#include<game.h>

int main()
{

	GameWindow window;
	window.init(1080,720,1);

	Game game(window);
	

	uint32_t last_tick = SDL_GetTicks();
	uint32_t current_tick = last_tick;

	uint32_t delta_amount = 5;
	uint32_t accum = 0;
	

	bool run = true;
	
	/*
	nlohmann::json levelData = {
        {"level_id", 1},
        {"name", "First Level"},
        {"player_start", {{"x", 50}, {"y", 100}}},
        {"enemies", {
            {{"type", "slime"}, {"x", 200}, {"y", 300}},
            {{"type", "bat"}, {"x", 400}, {"y", 500}}
        }}
    };
	*/

	while (run)
	{
	
		current_tick = SDL_GetTicks();
		uint32_t  from_last_tick = current_tick - last_tick;

		if (from_last_tick > delta_amount){from_last_tick = delta_amount;}

		accum += from_last_tick;
		last_tick = current_tick;

		run = game.update(delta_amount);
		while(accum >= delta_amount)
		{

			game.draw(window,delta_amount);
			
			accum -= delta_amount;
		}
		
	}
	return 0;
}


