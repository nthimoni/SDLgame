#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>

#include <iostream>
#include <vector>

#include "RenderWindow.hpp"
#include "TileMap.hpp"
#include "Player.hpp"

RenderWindow::RenderWindow(const char *p_title, int p_w, int p_h)
	: window(NULL), renderer(NULL), keys(4, false)
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
}

void RenderWindow::PrintPlayer()
{
	player.display(&camera);
}

void RenderWindow::MovePlayer()
{
	if (keys[KEY::Z])
	{
		player.move(Vector2(0, -PLAYER_VEL));
		player.setDir(UP);
	}
	if (keys[KEY::Q])
	{
		player.move(Vector2(-PLAYER_VEL, 0));
		player.setDir(LEFT);
	}
	if (keys[KEY::S])
	{
		player.move(Vector2(0, PLAYER_VEL));
		player.setDir(DOWN);
	}
	if (keys[KEY::D])
	{
		player.move(Vector2(PLAYER_VEL, 0));
		player.setDir(RIGHT);
	}

	Vector2 cameraPos(player.getPos().x + PLAYER_W / 2 - WIN_W / 2 ,
						player.getPos().y + PLAYER_H / 2 - WIN_H / 2);
	this->setCamera(&cameraPos);
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

RenderWindow::~RenderWindow()
{
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
}
