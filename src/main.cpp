#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <fstream>

#include "RenderWindow.hpp"
#include "Player.hpp"
#include "constantes.hpp"

int	main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		std::cout << "SDL_init has failed. SDL_ERROR : " << SDL_GetError() << std::endl;
	if (!IMG_Init(IMG_INIT_PNG))
		std::cout << "IMG_init has failed. SDL_ERROR : " << SDL_GetError() << std::endl;

	RenderWindow window(TITLE, WIN_W, WIN_H);
	window.AddLayer("assets/tileset.png", "assets/map1.txt");
	window.LoadPlayer("assets/mainsheet.png");

	bool isRunning = true;
	SDL_Event event;

	while (isRunning)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				isRunning = 0;
		}
		window.Clear();
		window.PrintMap();
		window.PrintPlayer();
		window.Render();
	}

	SDL_Quit();
	return (0);
}
