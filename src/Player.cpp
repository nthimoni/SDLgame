#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <limits>
#include <array>

#include "Player.hpp"
#include "TileMap.hpp"
#include "tools.hpp"
#include "constantes.hpp"

Player::Player() 
	: sprite(NULL), renderer(NULL), dir(UP), animState(0), dur(MAX_TILE, false), jumpTime(-1)
{
	position.x = 0;
	position.y = 0;
	position.w = PLAYER_W;
	position.h = PLAYER_H;
}

Player::Player(const char *path_sprite, SDL_Renderer *p_renderer) 
	: sprite(NULL), renderer(NULL), dir(UP), animState(0), dur(MAX_TILE, false), jumpTime(-1)
{
	position.x = 0;
	position.y = 0;
	position.w = PLAYER_W;
	position.h = PLAYER_H;
	this->renderer = p_renderer;
	this->LoadSprite(path_sprite);
}

void Player::setCollision()
{
	std::array<tile_id, 3> tiles = {1, 2, 3};

	for (unsigned int i = 0; i < tiles.size(); i++)
		dur[tiles[i]] = true;
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

bool Player::move(Vector2 nextMove, std::vector<TileMap> *layer)
{
	position.x += nextMove.x;
	position.y += nextMove.y;
	int MinX = position.x / TILE_W;
	int MinY = position.y / TILE_H;
	int MaxX = (position.x + PLAYER_W) / TILE_W;
	int MaxY = (position.y + PLAYER_H) / TILE_W;
	for (int i = MinX; i <= MaxX; i++)
		for (int u = MinY; u <= MaxY; u++)
		{
			SDL_Rect tile{i * TILE_W, u * TILE_H, TILE_W, TILE_H};
			for (unsigned int x = 0; x < (*layer).size(); x++)
			if (SDL_HasIntersection(&position, &tile) && dur[(*layer)[x].Get(i, u)])
			{
				position.x -= nextMove.x;
				position.y -= nextMove.y;
				return false;
			}
		}
	return true;
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

int Player::isJumping(unsigned int step)
{
	if (jumpTime > -1 && jumpTime < JUMP_TIME_MAX)
	{
		jumpTime += step;
		return JUMP_TIME_MAX - jumpTime;
	}
	else if (jumpTime >= JUMP_TIME_MAX)
		jumpTime = -1;
	return 0;
}

void Player::jump()
{
	if (jumpTime < 0)
		jumpTime = 0;
}
void Player::display(SDL_Rect *camera)
{
	SDL_Rect src;
	src.x = animState * (PLAYER_W + 40) + 20;
	src.y = dir * (PLAYER_H + 15) + 15;
	src.w = PLAYER_W;
	src.h = PLAYER_H;
	SDL_Rect dst;
	dst.x = position.x - camera->x;
	dst.y = position.y - camera->y;
	dst.w = PLAYER_W;
	dst.h = PLAYER_H;
	SDL_RenderCopy(renderer, sprite, &src, &dst);
}
