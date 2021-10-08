#ifndef PICKMAP_HPP
# define PICKMAP_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include <vector>
#include <string>

#include "Pickable.hpp"

class PickMap
{
	public:
		PickMap();
		void LoadTab(const char *TabPath);
		void LoadTexture(const char *TexturePath);
		void LoadRenderer(SDL_Renderer *renderer);
		void Display(SDL_Rect *camera);
		void FreeTab();
		bool pickUp(int x, int y);
		void LoadBurgerSound(const char *sound_path);
		~PickMap();
	private:
		void ParseLine(std::string line);
		std::vector<std::vector<Pickable*>> tab;
		SDL_Renderer *renderer;
		SDL_Texture *texture;
		Mix_Music *music;
};

#endif
