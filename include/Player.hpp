#ifndef PLAYER_HPP
# define PLAYER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector>

#include "Player.hpp"
#include "tools.hpp"
#include "TileMap.hpp"

enum Direction {DOWN, LEFT, RIGHT, UP};

class Player
{
	public:
		Player(const char *path_sprite, SDL_Renderer *renderer);
		Player();
		void setPosition(Vector2 newPos);
		bool move(Vector2 nextMove, std::vector<TileMap> *layer);
		void updateAnim(unsigned int anim);
		void setAnim(int animState);
		void display(SDL_Rect *camera);
		void LoadSprite(const char *path_sprite);
		void LoadRenderer(SDL_Renderer *renderer);
		Vector2 getPos();
		void setDir(Direction dir);
		void setCollision();
		int isJumping(unsigned int step);
		void jump();
	private:
		SDL_Rect position;
		SDL_Texture *sprite;
		SDL_Renderer *renderer;
		Direction dir;
		unsigned int animTime;
		int animState;
		std::vector<int> dur;
		int jumpTime;
};

#endif
