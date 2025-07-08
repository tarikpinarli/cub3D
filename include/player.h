#ifndef PLAYER_H
#define PLAYER_H
#include <cub3d.h>

typedef enum e_dir {
	NORTH,
	SOUTH,
	EAST,
	WEST
}	t_dir;

typedef struct s_player {
	double	x;
	double	y;
	t_dir	dir;
}	t_player;

#endif