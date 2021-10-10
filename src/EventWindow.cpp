#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

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
			keys[KEY::Z] = true;
			break;
		case SDLK_q:
			keys[KEY::Q] = true;
			break;
		case SDLK_d:
			keys[KEY::D] = true;
			break;
		case SDLK_s:
			keys[KEY::S] = true;
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

int RenderWindow::DefeatScreen()
{
	SDL_Event event;
	bool clicked = false;
	TTF_Font *fontwin = TTF_OpenFont(FONT_PATH, 70);
	SDL_Color Black{0, 0, 0, 255};
	SDL_Rect dst;

	SDL_SetRenderDrawColor(renderer, 150, 0, 0, 255);
	SDL_RenderClear(this->renderer);

	SDL_Surface *surface = TTF_RenderText_Blended(fontwin, "GAME OVER !", Black);
	SDL_Texture *text = SDL_CreateTextureFromSurface(this->renderer, surface);

	dst.x = (WIN_W - surface->w) / 2;
	dst.y = 200;
	dst.w = surface->w;
	dst.h = surface->h;

	SDL_RenderCopy(this->renderer, text, NULL, &dst);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(text);
	TTF_CloseFont(fontwin);
	SDL_RenderPresent(this->renderer);
	while (!clicked)
	{
		while (SDL_PollEvent(&event))
			switch (event.type)
			{
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_RETURN)
						return -1;;
					break;
				case SDL_QUIT:
					return -1;
					break;
			}
	}
	return -1;
}

int RenderWindow::WinScreen()
{
	SDL_Event event;
	bool clicked = false;
	TTF_Font *fontwin = TTF_OpenFont(FONT_PATH, 70);
	SDL_Color Black{0, 0, 0, 255};
	SDL_Rect dst;

	SDL_SetRenderDrawColor(renderer, 0, 150, 0, 255);
	SDL_RenderClear(this->renderer);

	SDL_Surface *surface = TTF_RenderText_Blended(fontwin, "VICTORY !", Black);
	SDL_Texture *text = SDL_CreateTextureFromSurface(this->renderer, surface);

	dst.x = (WIN_W - surface->w) / 2;
	dst.y = 200;
	dst.w = surface->w;
	dst.h = surface->h;

	SDL_RenderCopy(this->renderer, text, NULL, &dst);
	
	std::string temp = "SCORE : ";
	temp += std::to_string(player.getScore());
	surface = TTF_RenderText_Blended(fontwin, temp.c_str(), Black);
	text = SDL_CreateTextureFromSurface(this->renderer, surface);

	dst.x = (WIN_W - surface->w) / 2;
	dst.y = 350;
	dst.w = surface->w;
	dst.h = surface->h;

	SDL_RenderCopy(this->renderer, text, NULL, &dst);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(text);
	TTF_CloseFont(fontwin);
	SDL_RenderPresent(this->renderer);
	while (!clicked)
	{
		while (SDL_PollEvent(&event))
			switch (event.type)
			{
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_RETURN)
						return -1;;
					break;
				case SDL_QUIT:
					return -1;
					break;
			}
	}
	return -1;
}
