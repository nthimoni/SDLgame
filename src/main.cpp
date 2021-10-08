#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <fstream>

#include "RenderWindow.hpp"
#include "Player.hpp"
#include "constantes.hpp"

int	main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		std::cout << "SDL_init has failed. SDL_ERROR : " << SDL_GetError() << std::endl;
	if (!IMG_Init(IMG_INIT_PNG))
		std::cout << "IMG_init_PNG has failed. SDL_ERROR : " << SDL_GetError() << std::endl;
	if (!IMG_Init(IMG_INIT_JPG))
		std::cout << "IMG_init_JPEG has failed. SDL_ERROR : " << SDL_GetError() << std::endl;
	if (TTF_Init() == -1)
		std::cout << "Erreur lors de TTF_INIT() " << TTF_GetError() << std::endl;
	if (Mix_OpenAudio(96000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0)
		std::cout << "Erreur initialisation SDL_mixer : " <<  Mix_GetError() << std::endl;

	RenderWindow window(TITLE, WIN_W, WIN_H);
	window.AddLayer("assets/tileset.png", "assets/map1.txt");
	window.LoadPlayer("assets/mainsheet.png");
	window.LoadBackground("assets/BG1.jpg");	
	window.LoadBurgers("assets/burger.png", "assets/BurgerTab.txt");
	window.LoadBurgerSound("assets/borgir.wav");
	window.LoadFont("assets/HighMan.ttf", 40);
	unsigned int previous = 0;
	unsigned int current = SDL_GetTicks();
	unsigned int step = 0;
	unsigned int fps = 0;
	unsigned int fps_time = 0;
	int compt_rebours = MAX_LVL_TIME;

	while (window.Event())
	{
		current = SDL_GetTicks();
		step = current - previous;
		previous = current;
		compt_rebours -= step;
		if (compt_rebours <= 0)
			break;
		window.Clear();
		window.PrintBackground();
		window.PrintMap();
		window.PrintBurgers();
		window.MovePlayer(step);
		window.PickBurgers(&compt_rebours);
		window.PrintPlayer();
		window.PrintTimer(compt_rebours);
		window.Render();
		fps++;
		fps_time += step;
		if (fps_time > 1000)
		{
			std::cout << fps << std::endl;
			fps = 0;
			fps_time = 0;
		}

	}
	TTF_Quit();
	SDL_Quit();
	return (0);
}
