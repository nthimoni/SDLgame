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
		std::cout << "IMG_init_PNG has failed. SDL_ERROR : " << SDL_GetError() << std::endl;
	if (!IMG_Init(IMG_INIT_JPG))
		std::cout << "IMG_init_JPEG has failed. SDL_ERROR : " << SDL_GetError() << std::endl;
	RenderWindow window(TITLE, WIN_W, WIN_H);
	window.AddLayer("assets/tileset.png", "assets/map1.txt");
	window.LoadPlayer("assets/mainsheet.png");
	window.LoadBackground("assets/BG1.jpg");
	
	unsigned int previous = 0;
	unsigned int current = SDL_GetTicks();
	unsigned int step = 0;

	while (window.Event())
	{
		current = SDL_GetTicks();
		step = current - previous;
		previous = current;
		std::cout << step << std::endl;
		window.Clear();
		window.PrintBackground();
		window.PrintMap();
		window.PrintPlayer();
		window.MovePlayer(step);
		window.Render();
	}

	SDL_Quit();
	return (0);
}
