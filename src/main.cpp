#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <fstream>

#include "RenderWindow.hpp"
#include "Player.hpp"
#include "constantes.hpp"
#include "init.hpp"
#include "EntityManager.hpp"

int	main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	if (Init())
	{
		RenderWindow window(TITLE, WIN_W, WIN_H);
		window.AddLayer("assets/tileset.png", "assets/map1.txt");
		window.LoadPlayer("assets/mainsheet.png");
		window.LoadBackground("assets/BG1.jpg");	
		window.LoadBurgers("assets/burger.png", "assets/BurgerTab.txt");
		window.LoadBurgerSound("assets/borgir.wav");
		window.LoadFont(FONT_PATH, 40);
		EntityManager manager;
		manager.addEntity("assets/SkeletonSprite.png", window.getRenderer(), Vector2{1000, 0}); 
		unsigned int previous = 0;
		unsigned int current = SDL_GetTicks();
		unsigned int step = 0;
		unsigned int fps = 0;
		unsigned int fps_time = 0;
		int compt_rebours = MAX_LVL_TIME;

		while (window.Event())
		{
			current = SDL_GetTicks();
			step = current - previous;
			previous = current;
			compt_rebours -= step;
			if (compt_rebours <= 0)
				if (window.DefeatScreen() == -1)
					break;
			window.Clear();
			window.PrintBackground();
			window.PrintMap();
			window.PrintBurgers();
			window.MovePlayer(step);
			window.PickBurgers(&compt_rebours);
			window.PrintPlayer();
			if (compt_rebours < 0)
				compt_rebours = 0;
			window.PrintTimer(compt_rebours);
			window.PrintScore();
			window.PatrolEnnemy(&manager,step);
			window.PrintEnnemy(&manager);
			if (window.hitting(&manager))
				if (window.DefeatScreen() == -1)
					break;
			window.Render();
			fps++;
			fps_time += step;
			if (fps_time > 1000)
			{
				std::cout << fps << std::endl;
				fps = 0;
				fps_time = 0;
			}
			if (window.isLevelFinish())
			{
				window.CompleteScore(compt_rebours);
				if (window.WinScreen() == -1)
					break;
			}
		}
	}
	else
		return (-1);
	Quit();
	return (0);
}
