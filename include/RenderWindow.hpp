#ifndef RENDERWINDOW_HPP
# define RENDERWINDOW_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector>

#include "TileMap.hpp"
#include "Player.hpp"

class RenderWindow
{
	public:
		RenderWindow(const char *p_title, int p_w, int p_h);
		void AddLayer(const char *p_text, const char *p_tab);
		void LoadPlayer(const char *player_text);
		void PrintMap();
		void PrintPlayer();
		void MovePlayer(int x, int y);
		bool Event();
		void Clear();
		void Render();
		~RenderWindow();
	private:
		SDL_Window *window;
		SDL_Renderer *renderer;
		std::vector<TileMap> layer;
		Player player;
	private:
		bool KeyDown(SDL_Event *event);
		bool KeyUp(SDL_Event *event);
};

#endif
