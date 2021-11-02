#include <SDL2/SDL.h>

#include <vector>

#include "EntityManager.hpp"
#include "Player.hpp"
#include "TileMap.hpp"
#include "tools.hpp"

EntityManager::EntityManager()
{
}
void EntityManager::addEntity(const char *sprite, SDL_Renderer *renderer, Vector2 pos)
{
	entities.emplace_back(sprite, renderer);
	entities[entities.size() - 1].setPosition(pos);
	entities[entities.size() - 1].setDir(LEFT);
	entities[entities.size() - 1].setCollision();
}
void EntityManager::patrol(std::vector<TileMap> *layer, int step)
{
	float velocity = ENNEMY_VEL * mili_to_sec_float(step);

	for (unsigned int i = 0; i < entities.size(); ++i)
	{
		if (!entities[i].fall(layer, step))
		{
			if (!entities[i].canWalk(layer))
				entities[i].reverseDir();
			if (entities[i].getDir() == RIGHT)
				entities[i].move(entities[i].add_delta(velocity, 0), layer);
			else
				entities[i].move(entities[i].add_delta(-velocity, 0), layer);
			entities[i].updateAnim(step);
		}
	}
}
void EntityManager::display(SDL_Rect *camera)
{
	for (unsigned int i = 0; i < entities.size(); i++)
		entities[i].display(camera);
}
bool EntityManager::hitting(SDL_Rect rect)
{
	for (unsigned int i = 0; i < entities.size(); i++)
	{
		SDL_Rect ent = entities[i].getRect();
		if (SDL_HasIntersection(&rect, &ent))
			return true;
	}
	return false;
}
