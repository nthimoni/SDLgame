#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <limits>
#include <array>
#include <math.h>
#include <stdlib.h>

#include "Player.hpp"
#include "TileMap.hpp"
#include "tools.hpp"
#include "constantes.hpp"

Player::Player() 
	: sprite(NULL), renderer(NULL), dir(UP), animState(0),
   	dur(MAX_TILE, false), ladder(MAX_TILE, false), jumpTime(-1)
{
	position.x = 0;
	position.y = 0;
	position.w = PLAYER_W;
	position.h = PLAYER_H;
}

Player::Player(const char *path_sprite, SDL_Renderer *p_renderer) 
	: sprite(NULL), renderer(NULL), dir(UP), animState(0),
   	dur(MAX_TILE, false), ladder(MAX_TILE, false), jumpTime(-1)
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
	std::array<tile_id, 3> dures = {1, 2, 3};

	for (unsigned int i = 0; i < dures.size(); i++)
		dur[dures[i]] = true;

	std::array<tile_id, 14> ladders = {4, 5, 47, 48, 57, 58, 67, 68, 77, 78, 87, 88, 97, 98};

	for (unsigned int u = 0; u < ladders.size(); u++)
		ladder[ladders[u]] = true;
}

bool Player::isOnLadder(std::vector<TileMap> *layer)
{
	int MinX = position.x / TILE_W;
	int MinY = position.y / TILE_H;
	int MaxX = (position.x + PLAYER_W) / TILE_W;
	int MaxY = (position.y + PLAYER_H) / TILE_W;

	for (int i = MinX; i <= MaxX; i++)
		for (int u = MinY; u <= MaxY; u++)
		{
			for (unsigned int e = 0; e < (*layer).size(); e++)
				if (ladder[(*layer)[e].Get(i, u)])
					return true;
		}
	return false;
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
	if (nextMove.x == 0)
		return this->moveY(nextMove.y, layer);
	if (nextMove.y == 0)
		return this->moveX(nextMove.x, layer);
	int x = 0;
	int y = 0;
	int MinX = 0;
	int MinY = 0;
	int MaxX = 0;
	int MaxY = 0;
	char signX = 0;
	char signY = 0;
	nextMove.x < 0 ? signX-- : signX++;
	nextMove.y < 0 ? signY-- : signY++;
	nextMove.x = abs(nextMove.x);
	nextMove.y = abs(nextMove.y);
	if (nextMove.x > nextMove.y)
	{
		for (int r = 1; r <= nextMove.x; r++)
		{
			x = position.x + r * signX;
			y = position.y + ((int)round((float)r/(nextMove.x/nextMove.y))) * signY;
			MinX = x / TILE_W;
			MinY = y / TILE_H;
			MaxX = (x + PLAYER_W) / TILE_W;
			MaxY = (y + PLAYER_H) / TILE_W;
			for (int i = MinX; i <= MaxX; i++)
				for (int u = MinY; u <= MaxY; u++)
				{
					for (unsigned int e = 0; e < (*layer).size(); e++)
						if (dur[(*layer)[e].Get(i, u)])
						{
							if (r == 1)
								return (false);
							else
							{
								position.x += (r - 1) * signX;
								position.y += ((int)round((float)(r - 1)/(nextMove.x/nextMove.y))) * signY;
								return (true);
							}
						}
				}
		}
		position.x = x;
		position.y = y;
	}
	else
	{
		for (int r = 1; r <= nextMove.y; r++)
		{
			y = position.y + r * signY;
			x = position.x + ((int)round((float)r/(nextMove.y/nextMove.x))) * signX;
			MinX = x / TILE_W;
			MinY = y / TILE_H;
			MaxX = (x + PLAYER_W) / TILE_W;
			MaxY = (y + PLAYER_H) / TILE_W;
			for (int i = MinX; i <= MaxX; i++)
				for (int u = MinY; u <= MaxY; u++)
				{
					for (unsigned int e = 0; e < (*layer).size(); e++)
						if (dur[(*layer)[e].Get(i, u)])
						{
							if (r == 1)
								return (false);
							else
							{
								position.y += (r - 1) * signY;
								position.x += ((int)round((float)(r - 1)/(nextMove.y/nextMove.x))) * signX;
								return (true);
							}
						}
				}
		}
		position.x = x;
		position.y = y;
	}
	return (true);
}

bool Player::moveX(int x, std::vector<TileMap> *layer)
{
	int MinX = 0;
	int MinY = 0;
	int MaxX = 0;
	int MaxY = 0;
	char signX = 0;
	x < 0 ? signX-- : signX++;
	for (int t = 0 ; t < abs(x) ; t++)
	{
		position.x += 1 * signX;
		MinX = position.x / TILE_W;
		MinY = position.y / TILE_H;
		MaxX = (position.x + PLAYER_W) / TILE_W;
		MaxY = (position.y + PLAYER_H) / TILE_W;
		for (int i = MinX; i <= MaxX; i++)
			for (int u = MinY; u <= MaxY; u++)
			{
				for (unsigned int e = 0; e < (*layer).size(); e++)
					if (dur[(*layer)[e].Get(i, u)])
					{
						position.x -= 1 * signX;
						if (t == 0)
							return (false);
						else
							return (true);
					}
			}

	}
	return (true);
}

bool Player::moveY(int y, std::vector<TileMap> *layer)
{
	int MinX = 0;
	int MinY = 0;
	int MaxX = 0;
	int MaxY = 0;
	char signY = 0;
	y < 0 ? signY-- : signY++;
	for (int t = 0 ; t < abs(y) ; t++)
	{
		position.y += 1 * signY;
		MinX = position.x / TILE_W;
		MinY = position.y / TILE_H;
		MaxX = (position.x + PLAYER_W) / TILE_W;
		MaxY = (position.y + PLAYER_H) / TILE_W;
		for (int i = MinX; i <= MaxX; i++)
			for (int u = MinY; u <= MaxY; u++)
			{
				for (unsigned int e = 0; e < (*layer).size(); e++)
					if (dur[(*layer)[e].Get(i, u)])
					{
						position.y -= 1 * signY;
						if (t == 0)
							return (false);
						else
							return (true);
					}
			}

	}
	return (true);
}

bool Player::fall(std::vector<TileMap> *layer)
{
	int MinX = 0;
	int MinY = 0;
	int MaxX = 0;
	int MaxY = 0;
	int range = GRAVITY_VEL;
	for (int t = 0; t < range;  t++)
	{
		position.y += 1;
		MinX = position.x / TILE_W;
		MinY = position.y / TILE_H;
		MaxX = (position.x + PLAYER_W) / TILE_W;
		MaxY = (position.y + PLAYER_H) / TILE_W;
		for (int i = MinX; i <= MaxX; i++)
			for (int u = MinY; u <= MaxY; u++)
			{
				for (unsigned int e = 0; e < (*layer).size(); e++)
					if (dur[(*layer)[e].Get(i, u)] || ladder[(*layer)[e].Get(i, u)])
					{
						position.y -= 1;
						if (t == 0)
							return (false);
						else
							return (true);
					}
			}

	}
	return (true);
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

void Player::stopJump()
{
	this->jumpTime = -1;
}
