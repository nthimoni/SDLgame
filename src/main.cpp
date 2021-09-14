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

	while (window.Event())
	{
		window.Clear();
		window.PrintMap();
		window.PrintPlayer();
		window.MovePlayer();
		window.Render();
	}

	SDL_Quit();
	return (0);
}
