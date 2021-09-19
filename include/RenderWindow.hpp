#ifndef RENDERWINDOW_HPP
# define RENDERWINDOW_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector>

#include "TileMap.hpp"
#include "Player.hpp"

namespace KEY
{
	enum
	{
		Z = 0,
		Q,
		S,
		D
	};
};

class RenderWindow
{
	public:
		RenderWindow(const char *p_title, int p_w, int p_h);
		void AddLayer(const char *p_text, const char *p_tab);
		void LoadPlayer(const char *player_text);
		void PrintMap();
		void PrintPlayer();
		void MovePlayer(unsigned int step);
		bool Event();
		bool isPressed(int indice);
		void Clear();
		void Render();
		void setCamera(Vector2 *pos);
		void setCameraX(int x);
		void setCameraY(int y);
		void LoadBackground(const char *bgtext);
		void PrintBackground();
		~RenderWindow();
	private:
		SDL_Rect camera;
		SDL_Window *window;
		SDL_Renderer *renderer;
		SDL_Texture *background;
		std::vector<TileMap> layer;
		Player player;
		std::vector<bool> keys;
	private:
		bool KeyDown(SDL_Event *event);
		bool KeyUp(SDL_Event *event);
};

#endif
