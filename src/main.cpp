#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

int	main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		std::cout << "SDL_init has failed. SDL_ERROR : " << SDL_GetError() << std::endl;
	if (!IMG_Init(IMG_INIT_PNG))
		std::cout << "IMG_init has failed. SDL_ERROR : " << SDL_GetError() << std::endl;

	return (0);
}
