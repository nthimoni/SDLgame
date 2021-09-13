#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>

#include <iostream>
#include <vector>

#include "RenderWindow.hpp"
#include "TileMap.hpp"
#include "Player.hpp"

RenderWindow::RenderWindow(const char *p_title, int p_w, int p_h)
	: window(NULL), renderer(NULL), layer(std::vector<TileMap>())
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
	if (!window)
		std::cout << "Window failed to init. SDL_ERROR : " << SDL_GetError() << std::endl;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	player.LoadRenderer(renderer);
}

void RenderWindow::AddLayer(const char *p_text, const char *p_tab)
{
	layer.emplace_back(p_text, p_tab, this->renderer);
}

void RenderWindow::PrintMap()
{
	for (unsigned int i = 0; i < layer.size(); i++)
		layer[i].Display();
}

void RenderWindow::LoadPlayer(const char *sprite)
{
	player.LoadSprite(sprite);
}

void RenderWindow::PrintPlayer()
{
	player.display(DOWN, 0);
}

void RenderWindow::Clear()
{
	SDL_RenderClear(this->renderer);
}

void RenderWindow::Render()
{
	SDL_RenderPresent(this->renderer);
}

RenderWindow::~RenderWindow()
{
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
}
