#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "tools.hpp"
#include "constantes.hpp"
#include "Pickable.hpp"

Pickable::Pickable()
{
	entity = SDL_Rect{0, 0, 0, 0};
}

Pickable::Pickable(SDL_Rect *rect) : entity(*rect)
{
}

SDL_Rect *Pickable::getRect()
{
	return (&entity);
}

Vector2 Pickable::getPosition()
{
	return Vector2(entity.x, entity.y);
}

void Pickable::setPosition(Vector2 newPosition)
{
	entity.x = newPosition.x;
	entity.y = newPosition.y;
}

void Pickable::setRect(SDL_Rect *rect)
{
	entity.x = rect->x;
	entity.y = rect->y;
	entity.w = rect->w;
	entity.h = rect->h;
}

void Pickable::display(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *camera)
{
	SDL_Rect src{0, 0, BURGER_W, BURGER_H};
	SDL_Rect dst{entity};
	dst.x -= camera->x;
	dst.y -= camera->y;
	SDL_RenderCopy(renderer, texture, &src, &dst);
}
