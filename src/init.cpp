#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

bool Init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{
		std::cout << "SDL_Init has failed. SDL_ERROR : " << SDL_GetError() << std::endl;
		return false;
	}
	if (!IMG_Init(IMG_INIT_PNG))
	{
		std::cout << "IMG_Init (png) has failed. SDL_ERROR : " << SDL_GetError() << std::endl;
		SDL_Quit();
		return false;
	}
	if (!IMG_Init(IMG_INIT_JPG))
	{
		std::cout << "IMG_Init (JPG) has failed. SDL_ERROR : " << SDL_GetError() << std::endl;
		IMG_Quit();
		SDL_Quit();
		return false;
	}
	if (TTF_Init() == -1)
	{
		std::cout << "TTF_Init has failed. SDL_ERROR : " << SDL_GetError() << std::endl;
		IMG_Quit();
		SDL_Quit();
		return false;
	}
	if (Mix_OpenAudio(96000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
	{
		std::cout << "TTF_Init has failed. SDL_ERROR : " << SDL_GetError() << std::endl;
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
		return false;
	}
	return true;
}

void Quit()
{
	while (Mix_Init(0))
		Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
