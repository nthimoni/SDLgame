#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

#include "RenderWindow.hpp"
#include "Player.hpp"
#include "tools.hpp"

bool RenderWindow::Event()
{
	SDL_Event event;
	bool isRunning = true;

	while (SDL_PollEvent(&event))
		switch (event.type)
		{
			case SDL_KEYUP:
				isRunning = this->KeyUp(&event);
				break;
			case SDL_KEYDOWN:
				isRunning = this->KeyDown(&event);
				break;
			case SDL_QUIT:
				return false;
				break;
		}
	return isRunning;
}

bool RenderWindow::KeyDown(SDL_Event *event)
{
	switch (event->key.keysym.sym)
	{
		case SDLK_z:
			keys[KEY::Z] = 1;
			break;
		case SDLK_q:
			keys[KEY::Q] = 1;
			break;
		case SDLK_d:
			keys[KEY::D] = 1;
			break;
		case SDLK_s:
			keys[KEY::S] = 1;
			break;
	}
	return true;
}

bool RenderWindow::KeyUp(SDL_Event *event)
{
	switch (event->key.keysym.sym)
	{
		case SDLK_z:
			keys[KEY::Z] = 0;
			break;
		case SDLK_q:
			keys[KEY::Q] = 0;
			break;
		case SDLK_d:
			keys[KEY::D] = 0;
			break;
		case SDLK_s:
			keys[KEY::S] = 0;
			break;
		case SDLK_e:
			this->layer[0].LoadTab("assets/map1.txt");
			break;
	}
	return true;
}

bool RenderWindow::isPressed(int indice)
{
	return keys[indice];
}
