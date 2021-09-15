#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

#include "Player.hpp"
#include "tools.hpp"
#include "constantes.hpp"

Player::Player() 
	: sprite(NULL), renderer(NULL), dir(UP), animState(0)
{
	position.x = 0;
	position.y = 0;
	position.w = PLAYER_W;
	position.h = PLAYER_H;
}

Player::Player(const char *path_sprite, SDL_Renderer *p_renderer) 
	: sprite(NULL), renderer(NULL), dir(UP), animState(0)
{
	position.x = 0;
	position.y = 0;
	position.w = PLAYER_W;
	position.h = PLAYER_H;
	this->renderer = p_renderer;
	this->LoadSprite(path_sprite);
}

void Player::setPosition(Vector2 newPos)
{
	position.x = newPos.x;
	position.y = newPos.y;
}

Vector2 Player::getPos()
{
	return Vector2(position.x, position.y);
}

void Player::move(Vector2 nextMove)
{
	position.x += nextMove.x;
	position.y += nextMove.y;
}

void Player::updateAnim(unsigned int step)
{
	animTime += step;
	if (animTime >= STEP_ANIM)
	{
		animState++;
		animTime = 0;
	}
	if (animState == NB_SPRITE_LINE)
		animState = 0;

}

void Player::setAnim(int animState)
{
	this->animState = animState;
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

void Player::setDir(Direction dir)
{
	 this->dir = dir;
}

void Player::display(SDL_Rect *camera)
{
	(void)camera;
	SDL_Rect src;
	src.x = animState * PLAYER_W;
	src.y = dir * PLAYER_H;
	src.w = PLAYER_W;
	src.h = PLAYER_H;
	SDL_Rect dst;
	dst.x = position.x - camera->x;
	dst.y = position.y - camera->y;
	dst.w = PLAYER_W;
	dst.h = PLAYER_H;
	SDL_RenderCopy(renderer, sprite, &src, &dst);
}
