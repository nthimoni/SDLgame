#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

#include "constantes.hpp"
#include "TileMap.hpp"

TileMap::TileMap(const char *text_path, const char *tab_path, SDL_Renderer *p_renderer)
	:text(NULL), renderer(p_renderer)
{
	this->LoadTab(tab_path);
	this->LoadTexture(text_path);
}

void TileMap::LoadTab(const char *p_path)
{
	std::fstream file(p_path);
	std::string buffer;

	if (!file.is_open())
		std::cout << "(LoadTab) Erreur lors de l'ouverture de : " << p_path << '\n';
	else
		while (std::getline(file, buffer))
			this->ParseLine(buffer);
	file.close();
}

void TileMap::LoadTexture(const char *p_path)
{
	if (this->text != NULL)
		SDL_DestroyTexture(this->text);
	this->text = IMG_LoadTexture(this->renderer, p_path);
	if (this->text == NULL)
		std::cout << "(LoadText) Erreur lors du chargement de : " << p_path << std::endl;
}

void TileMap::LoadRenderer(SDL_Renderer *p_renderer)
{
	this->renderer = p_renderer;
}

void TileMap::ParseLine(std::string line)
{
	tile_id a = 0;
	std::string buffer;
	std::istringstream s_line(line);

	tab.push_back(std::vector<tile_id>());
	while (std::getline(s_line, buffer, '\t'))
	{
		a = (tile_id)std::atoi(buffer.c_str());
		tab[tab.size() - 1].push_back(a);
	}
}

void TileMap::Display()
{
	SDL_Rect src;
	SDL_Rect dst;

	src.w = TILE_W;
	src.h = TILE_H;
	dst.w = TILE_W;
	dst.h = TILE_H;

	for (unsigned int i = 0 ; i < tab.size() ; i++)
		for(unsigned int a = 0 ; a < tab[i].size() ; a++)
		{

			src.x = (tab[i][a] % NB_TILE) * TILE_W;
			src.y = (tab[i][a] / NB_TILE) * TILE_H;
			dst.x = a * TILE_W;
			dst.y = i * TILE_H;
			SDL_RenderCopy(renderer, text, &src, &dst);
		}
}
