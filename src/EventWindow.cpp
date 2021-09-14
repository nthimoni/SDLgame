#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

#include "RenderWindow.hpp"

bool RenderWindow::Event()
{
	SDL_Event event;
	bool isRunning = true;

	while (SDL_PollEvent(&event))
		switch (event.type)
		{
			case SDL_KEYUP:
				std::cout << "UP\n";
				break;
			case SDL_KEYDOWN:
				std::cout << "DOWN\n";
				break;
			case SDL_QUIT:
				isRunning = false;
				break;
		}
	return isRunning;
} 
