#ifndef TILEMAP_HPP
# define TILEMAP_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <vector>

#include "constantes.hpp"

class TileMap
{
	public:
		TileMap(const char *text_path, const char *tab_path, SDL_Renderer *p_renderer);
		void LoadTab(const char *p_path);
		void LoadTexture(const char *p_path, SDL_Renderer *p_renderer);
		int GetNum(unsigned int i, unsigned int j);
	private:
		SDL_Texture *text;
		std::vector<std::vector<tile_id>> tab;
		void ParseLine(std::string line);
};

#endif
