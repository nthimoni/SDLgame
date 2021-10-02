#ifndef PICKABLE_HPP
# define PICKABLE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "tools.hpp"

class Pickable
{
	public:
		Pickable();
		Pickable(SDL_Rect *rect);
		SDL_Rect *getRect();
		Vector2 getPosition();
		void setPosition(Vector2 newPosition);
		void setRect(SDL_Rect *rect);
		void display(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *camera);
	private:
		SDL_Rect entity;
};

#endif
