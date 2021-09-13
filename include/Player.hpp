#ifndef PLAYER_HPP
# define PLAYER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Player.hpp"

enum Direction {DOWN, LEFT, RIGHT, UP};

class Player
{
	public:
		Player(const char *path_sprite, SDL_Renderer *renderer);
		Player();
		void setPosition(int x, int y);
		void move(int x, int y);
		void display(Direction dir, int anim);
		void LoadSprite(const char *path_sprite);
		void LoadRenderer(SDL_Renderer *renderer);
	private:
		SDL_Texture *sprite;
		SDL_Renderer *renderer;
		SDL_Rect position;
};

#endif
