#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>

#include <iostream>
#include <vector>

#include "RenderWindow.hpp"
#include "TileMap.hpp"
#include "Player.hpp"
#include "tools.hpp"

RenderWindow::RenderWindow(const char *p_title, int p_w, int p_h)
	: window(NULL), renderer(NULL), background(NULL), keys(4, false)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
	if (!window)
		std::cout << "Window failed to init. SDL_ERROR : " << SDL_GetError() << std::endl;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	player.LoadRenderer(renderer);
	camera.x = 0;
	camera.y = 0;
	camera.w = WIN_W;
	camera.h = WIN_H;
}

void RenderWindow::AddLayer(const char *p_text, const char *p_tab)
{
	layer.emplace_back(p_text, p_tab, this->renderer);
}

void RenderWindow::PrintMap()
{
	for (unsigned int i = 0; i < layer.size(); i++)
		layer[i].Display(&camera);
}

void RenderWindow::LoadPlayer(const char *sprite)
{
	player.LoadSprite(sprite);
	player.setCollision();
}

void RenderWindow::LoadBurgers(const char *texture, const char *tab)
{
	burgers.LoadRenderer(renderer);
	burgers.LoadTab(tab);
	burgers.LoadTexture(texture);
}

void RenderWindow::PrintPlayer()
{
	player.display(&camera);
}

void RenderWindow::PrintBurgers()
{
	burgers.Display(&camera);
}

void RenderWindow::MovePlayer(unsigned int step)
{
	bool falling = false;
	int tempRestant = player.isJumping(step);
	if (player.isOnLadder(&layer))
	{
		player.stopJump();

		if (keys[KEY::Z])
			player.move(Vector2(0, -PLAYER_VEL), &layer);
	}
	else
	{
		if (!tempRestant)
		{
			falling = player.fall(&layer);
			if (!falling)
				if (keys[KEY::Z])
					player.jump();
		}
		else
			if (!player.move(Vector2(0, -JUMP_VEL * tempRestant / 100), &layer))
				player.stopJump();
	}

	if (keys[KEY::Q])
	{
		player.move(Vector2(-PLAYER_VEL, 0), &layer);
		player.setDir(LEFT);
	}
	if (keys[KEY::D])
	{
		player.move(Vector2(PLAYER_VEL, 0), &layer);
		player.setDir(RIGHT);
	}
	if (keys[KEY::S] && !falling && !tempRestant)
		player.move(Vector2(0, PLAYER_VEL), &layer);

	// ANIMATION
	if (XOR(keys[KEY::D], keys[KEY::Q]))
		player.updateAnim(step);
	else
		player.setAnim(SPRITE_NEUTRE);

	// CAMERA
	this->setCameraX(player.getPos().x + PLAYER_W / 2 - WIN_W / 2);
}

void RenderWindow::Clear()
{
	SDL_RenderClear(this->renderer);
}

void RenderWindow::Render()
{
	SDL_RenderPresent(this->renderer);
}

void RenderWindow::setCamera(Vector2 *pos)
{
	camera.x = pos->x;
	camera.y = pos->y;
}
void RenderWindow::setCameraX(int x)
{
	camera.x = x;
}
void RenderWindow::setCameraY(int y)
{
	camera.y = y;
}

void RenderWindow::PickBurgers()
{
	Vector2 playerPos = player.getPos();
	int minX = playerPos.x / BURGER_W;
	int maxX = (playerPos.x + PLAYER_W) / BURGER_W;
	int minY = playerPos.y / BURGER_H;
	int maxY = (playerPos.y + PLAYER_H) / BURGER_H;
	for (int i = minX; i <= maxX; i++)
		for (int u = minY; u <= maxY; u++)
			burgers.pickUp(i, u);
}

void RenderWindow::LoadBackground(const char *bgtext)
{
	if (background != NULL)
		SDL_DestroyTexture(background);
	background = IMG_LoadTexture(this->renderer, bgtext);
	if (background == NULL)
		std::cout << "Erreur lors du chargement de " << bgtext << '\n';
}

void RenderWindow::PrintBackground()
{
	SDL_RenderCopy(this->renderer, this->background, NULL, NULL);
}

RenderWindow::~RenderWindow()
{
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	SDL_DestroyTexture(this->background);
}
