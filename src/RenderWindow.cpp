#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include "RenderWindow.hpp"
#include "TileMap.hpp"
#include "Player.hpp"
#include "tools.hpp"

RenderWindow::RenderWindow(const char *p_title, int p_w, int p_h)
	: window(NULL), renderer(NULL), background(NULL), keys(4, false), font(NULL)
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
	float actual_vel = PLAYER_VEL * mili_to_sec_float(step);
	float actual_jump_vel = JUMP_VEL * mili_to_sec_float(step);


	if (player.isOnLadder(&layer))
	{
		player.stopJump();

		if (keys[KEY::Z])
			player.move(player.add_delta(0, -actual_vel), &layer);

	}
	else
	{
		if (!tempRestant)
		{
			falling = player.fall(&layer, step);
			if (!falling)
				if (keys[KEY::Z])
					player.jump();
		}
		else
			if (!player.move(player.add_delta(0, -actual_jump_vel * tempRestant / 100), &layer))
				player.stopJump();
	}

	if (keys[KEY::Q])
	{
		player.move(player.add_delta(-actual_vel, 0), &layer);
		player.setDir(LEFT);
	}
	if (keys[KEY::D])
	{
		player.move(player.add_delta(actual_vel, 0), &layer);
		player.setDir(RIGHT);
	}
	if (keys[KEY::S] && !falling && !tempRestant)
		player.move(player.add_delta(0, actual_vel), &layer);

	// ANIMATION
	if (XOR(keys[KEY::D], keys[KEY::Q]))
		player.updateAnim(step);
	else
		player.setAnim(SPRITE_NEUTRE);

	// CAMERA
	this->setCameraX(player.getPos().x + PLAYER_W / 2 - WIN_W / 2);
	this->setCameraY(player.getPos().y + PLAYER_H / 2 - WIN_H / 2);
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

void RenderWindow::PickBurgers(int *compt_rebours)
{
	Vector2 playerPos = player.getPos();
	int minX = playerPos.x / BURGER_W;
	int maxX = (playerPos.x + PLAYER_W) / BURGER_W;
	int minY = playerPos.y / BURGER_H;
	int maxY = (playerPos.y + PLAYER_H) / BURGER_H;
	for (int i = minX; i <= maxX; i++)
		for (int u = minY; u <= maxY; u++)
			if (burgers.pickUp(i, u))
			{
				*compt_rebours -= BURGER_TIME;
				player.addScore(SCORE_BURGER);
			}
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

void RenderWindow::LoadFont(const char *font_path, int size)
{
	if (this->font != nullptr)
		TTF_CloseFont(this->font);
	this->font = TTF_OpenFont(font_path, size);
}

void RenderWindow::LoadBurgerSound(const char *sound_path)
{
	burgers.LoadBurgerSound(sound_path);
}

void RenderWindow::PrintTimer(int time)
{
	SDL_Color Black{0, 0, 0, 255};
	std::string temp = "TIME : ";
	temp += std::to_string(mili_to_sec(time));
	SDL_Surface *surface = TTF_RenderText_Blended(this->font, temp.c_str(), Black);
	SDL_Texture *text = SDL_CreateTextureFromSurface(this->renderer, surface);
	SDL_Rect dst;
	dst.x = RANGE_FROM_BORDER;
	dst.y = RANGE_FROM_BORDER;
	dst.w = surface->w;
	dst.h = surface->h;
	SDL_RenderCopy(this->renderer, text, NULL, &dst);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(text);
}

void RenderWindow::PrintScore()
{
	SDL_Color Black{0, 0, 0, 255};
	std::string temp = "SCORE : ";
	temp +=	std::to_string(player.getScore());
	SDL_Surface *surface = TTF_RenderText_Blended(this->font, temp.c_str(), Black);
	SDL_Texture *text = SDL_CreateTextureFromSurface(this->renderer, surface);
	SDL_Rect dst;
	dst.x = WIN_W - (surface->w + RANGE_FROM_BORDER);
	dst.y = RANGE_FROM_BORDER;
	dst.w = surface->w;
	dst.h = surface->h;
	SDL_RenderCopy(this->renderer, text, NULL, &dst);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(text);
}

bool RenderWindow::isLevelFinish()
{
	Vector2 position = player.getPos();
	int xMin = position.x / TILE_W;
	int xMax = (position.x + PLAYER_W) / TILE_W;
	int yMin = position.y / TILE_H;
	int yMax = (position.y + PLAYER_H) / TILE_H;
	for (int x = xMin; x <= xMax; x++)
		for (int y = yMin; y <= yMax; y++)
			for (unsigned int u = 0; u < layer.size(); u++)
				if (layer[u].Get(x, y) == 8)
					return true;
	return false;
}




RenderWindow::~RenderWindow()
{
	TTF_CloseFont(this->font);
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	SDL_DestroyTexture(this->background);
}
