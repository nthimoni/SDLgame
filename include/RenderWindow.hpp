#ifndef RENDERWINDOW_HPP
# define RENDERWINDOW_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector>

#include "TileMap.hpp"

class RenderWindow
{
	public:
		RenderWindow(const char *p_title, int p_w, int p_h);
		void AddLayer(const char *p_tab, const char *p_text);
		void PrintMap();
		void cleanUp();
	private:
		std::vector<TileMap> layer;
		SDL_Window *window;
		SDL_Renderer *renderer;
};

#endif
