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
		void LoadTexture(const char *p_path);
		void LoadRenderer(SDL_Renderer *p_renderer);
		void Display();
	private:
		SDL_Texture *text;
		SDL_Renderer *renderer;
		std::vector<std::vector<tile_id>> tab;
		void ParseLine(std::string line);
};

#endif
