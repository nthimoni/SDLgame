#include <SDL2/SDL.h>
#include <SLD2/SDL_image.h>

#include "RenderWindow.hpp"

RenderWindow::RenderWindow(const char *p-title, int p_w, int p_h) 
	: window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN;

}
