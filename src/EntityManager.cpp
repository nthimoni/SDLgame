#include <SDL2/SDL.h>

#include <vector>

#include "EntityManager.hpp"
#include "Player.hpp"
#include "TileMap.hpp"

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
void EntityManager::patrol(std::vector<TileMap> *layer, int step, Vec2f *delta)
{
	for (int i = 0; i < entities.size(); ++i)
	{

	}
}
bool EntityManager::hitting(SDL_Rect rect)
{
}
