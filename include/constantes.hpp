#ifndef CONSTANTES_HPP
# define CONSTANTES_HPP

// Info window
# define TITLE "SteakOvergame"
# define WIN_W 1279
# define WIN_H 742

// Info TileMap
# define NB_TILE 10 // Number of tile on each line of tileset
# define TILE_W 32
# define TILE_H 32
# define MAX_TILE 300
typedef short int tile_id;

// Info Player
# define PLAYER_W 37
# define PLAYER_H 62
# define PLAYER_VEL 700
# define JUMP_TIME_MAX 350 
# define JUMP_VEL 280
# define GRAVITY_VEL 5
# define NB_SPRITE_LINE 8
# define SPRITE_NEUTRE 7
# define STEP_ANIM 100

// Info burger (pickable)
# define BURGER_W 32
# define BURGER_H 32

// INFO TEMPS
# define MAX_LVL_TIME 120000
# define BURGER_TIME 10000

// INFO SCORE
# define SCORE_BURGER 1000
# define SCORE_TIME 10
# define MILI_PER_POINT 20 // nombre de milisecondes pour obtenir un poit bonus en fin de partie

// INFO AFFICHAGE
# define FONT_PATH "assets/Highman.ttf"
# define RANGE_FROM_BORDER 10

#endif
