#ifndef ENTITY_MANAGER_HPP
# define ENTITY_MANAGER_HPP

#include <SDL2/SDL.h>

#include "TileMap.hpp"
#include "Player.hpp"
#include "tools.hpp"

class EntityManager
{
	public:
		EntityManager();
		void addEntity(const char *sprite, SDL_Renderer *renderer, Vector2 pos);
		void patrol(std::vector<TileMap> *layer, int step);
		bool hitting(SDL_Rect rect);
		void display(SDL_Rect *camera);
	private:
		std::vector<Player> entities;
};

#endif
