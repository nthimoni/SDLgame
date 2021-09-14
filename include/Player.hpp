#ifndef PLAYER_HPP
# define PLAYER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Player.hpp"
#include "tools.hpp"

enum Direction {DOWN, LEFT, RIGHT, UP};

class Player
{
	public:
		Player(const char *path_sprite, SDL_Renderer *renderer);
		Player();
		void setPosition(Vector2 newPos);
		void move(Vector2 nextMove);
		void display(SDL_Rect *camera);
		void LoadSprite(const char *path_sprite);
		void LoadRenderer(SDL_Renderer *renderer);
		Vector2 getPos();
		void setDir(Direction dir);
	private:
		SDL_Rect position;
		SDL_Texture *sprite;
		SDL_Renderer *renderer;
		Direction dir;
		int animState;
};

#endif
