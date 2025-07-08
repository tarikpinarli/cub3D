#ifndef MAP_H
#define MAP_H
#include <cub3d.h>

typedef struct s_map {
	char	**grid;
	int		width;
	int		height;
}	t_map;

char	**load_dummy_map(t_arena *arena);
#endif