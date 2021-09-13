#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Player.hpp"
#include "constantes.hpp"

void Player::Player(const char *path_sprite) 
	: sprite(NULL),position.x(0), position.y(0), position.w(SPRITE_W), position.h(SPRITE_H);
{
	this->LoadSprite(path_sprite);
}

void Player::setPosition(int x, int y)
{
	position.x = x;
	position.y = y;
}

void Player::move(int x, int y)
{
	position.x += x;
	position.y += y;
}

void Player::LoadSprite(*path_sprite)
{
	if (sprite != NULL)
		SDL_DestroyTexture(this->sprite);
	sprite = IMG_LoadTexture(path_sprite);
}


