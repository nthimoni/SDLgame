#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

#include "Player.hpp"
#include "constantes.hpp"

Player::Player() 
	: sprite(NULL), renderer(NULL)
{
	position.x = 0;
	position.y = 0;
	position.w = PLAYER_W;
	position.h = PLAYER_H;
}

Player::Player(const char *path_sprite, SDL_Renderer *p_renderer) 
	: sprite(NULL), renderer(NULL)
{
	position.x = 0;
	position.y = 0;
	position.w = PLAYER_W;
	position.h = PLAYER_H;
	this->renderer = p_renderer;
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

void Player::LoadSprite(const char *path_sprite)
{
	if (sprite != NULL)
		SDL_DestroyTexture(this->sprite);
	sprite = IMG_LoadTexture(this->renderer, path_sprite);
	if (sprite == NULL && renderer == NULL)
		std::cout << "Erreur lors du chargement de " << path_sprite << '\n';
}

void Player::LoadRenderer(SDL_Renderer *renderer)
{
	this->renderer = renderer;
}

void Player::display(Direction dir, int state)
{
	SDL_Rect src;
	src.x = state * PLAYER_W;
	src.y = dir * PLAYER_H;
	src.w = PLAYER_W;
	src.h = PLAYER_H;
	SDL_RenderCopy(renderer, sprite, &src, &position);
}
