#ifndef DRAW3D_H
#define DRAW3D_H

#include <cub3d.h>

typedef struct s_draw_data
{
	double		dir;
	double		start_angle;
	double		angle_step;
	int			ray;
	uint32_t	floor;
	uint32_t	ceiling;

	double		ray_angle;
	t_ray_hit	hit;
	double		corrected_dist;
	double		wall_height;
	int			start;
	int			end;

}	t_draw_data;



#endif
