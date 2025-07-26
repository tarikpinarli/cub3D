#ifndef DRAW2D_H
# define DRAW2D_H

# include <cub3d.h>

typedef struct s_draw2d
{
	int			offset_x;
	int			offset_y;

	int			x;
	int			y;
	int			dx;
	int			dy;

	int			px;
	int			py;

	char		c;
	uint32_t	color;

	int			player_px;
	int			player_py;
}				t_draw2d;

#endif
