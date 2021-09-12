#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>

#include <iostream>
#include <vector>

#include "RenderWindow.hpp"
#include "TileMap.hpp"

RenderWindow::RenderWindow(const char *p_title, int p_w, int p_h)
	: window(NULL), renderer(NULL), layer(std::vector<TileMap>())
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
	if (!window)
		std::cout << "Window failed to init. SDL_ERROR : " << SDL_GetError() << std::endl;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void AddLayer(const char *p_tab, const char *p_text)
{
	layer.push_back(TileMap(p_text, p_tab, this->renderer));
}

void RenderWindow::PrintMap()
{
	for (int i = 0; i < layer.size(); i++)
		layer[i].Display();
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(this->window);
}
