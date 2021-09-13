#ifndef PLAYER_HPP
# define PLAYER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


class Player
{
	public:
		Player(const char *path_sprite)
		void setPosition(int x, int y);
		void move(int x, int y);
		void LoadSprite(*path_sprite);
	private:
		SDL_Texture *sprite;
		SDL_Rect position;
		enum Direction {DOWN, LEFT, RIGHT, UP};
};

#endif
