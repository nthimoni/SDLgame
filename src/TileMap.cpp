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
	:text(NULL)
{
	this->LoadTab(text_path);
	this->LoadTexture(tab_path, p_renderer);
}

void TileMap::LoadTab(const char *p_path)
{
	std::ifstream file;
	std::string buffer;

	file.open(p_path);
	if (!file)
	{
		std::cout << "Erreur lors de l'ouverture de : " << p_path << '\n';
	}
	else
	{
		while (std::getline(file, buffer))
		{
			this->ParseLine(buffer);
		}
	}
}

void TileMap::LoadTexture(const char *p_path, SDL_Renderer *p_renderer)
{
	if (this->text != NULL)
		SDL_DestroyTexture(this->text);
	this->text = IMG_LoadTexture(p_renderer, p_path);
}

int TileMap::GetNum(unsigned int i, unsigned int j)
{
	if (i > (tab.size() - 1))
		return (-1);
	if (j > (tab[i].size() - 1))
		return (-1);
	return (this->tab[i][j]);
}

void TileMap::ParseLine(std::string line)
{
	tile_id a = 0;
	std::string buffer;
	std::istringstream s_line(line);

	tab.push_back(std::vector<tile_id>());
	while (std::getline(s_line, buffer, '\t'))
	{
		a = (tile_id)std::atoi(line.c_str());
		tab[tab.size() - 1].push_back(a);
	}
}
