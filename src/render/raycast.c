/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 13:14:16 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/26 13:48:29 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static t_ray_hit	get_hit_result(t_raycast *r)
{
	t_ray_hit	hit;

	if (r->side == 0)
		hit.distance = r->side_dist_x - r->delta_dist_x;
	else
		hit.distance = r->side_dist_y - r->delta_dist_y;
	if (r->side == 0)
	{
		if (r->ray_dir_x < 0)
			hit.wall_dir = WEST_WALL;
		else
			hit.wall_dir = EAST_WALL;
	}
	else
	{
		if (r->ray_dir_y < 0)
			hit.wall_dir = SOUTH_WALL;
		else
			hit.wall_dir = NORTH_WALL;
	}
	return (hit);
}

static int	perform_dda(t_map *map, t_raycast *r)
{
	while (1)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (r->map_x < 0 || r->map_y < 0 || r->map_x >= map->width
			|| r->map_y >= map->height)
			return (0);
		if (map->grid[r->map_y][r->map_x] == '1')
			return (1);
	}
}

static void	init_step_and_side_dist(t_game *game, t_raycast *r)
{
	if (r->ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (game->player->x - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - game->player->x) * r->delta_dist_x;
	}
	if (r->ray_dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (game->player->y - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - game->player->y) * r->delta_dist_y;
	}
}

void	init_raycast(t_game *game, double ray_angle, t_raycast *r)
{
	r->ray_dir_x = cos(ray_angle);
	r->ray_dir_y = sin(ray_angle);
	r->map_x = (int)game->player->x;
	r->map_y = (int)game->player->y;
	r->delta_dist_x = fabs(1 / r->ray_dir_x);
	r->delta_dist_y = fabs(1 / r->ray_dir_y);
}

t_ray_hit	cast_ray(t_game *game, double ray_angle)
{
	t_raycast	r;
	t_ray_hit	hit;

	init_raycast(game, ray_angle, &r);
	init_step_and_side_dist(game, &r);
	if (!perform_dda(game->map, &r))
	{
		hit.distance = 0;
		hit.wall_dir = -1;
		return (hit);
	}
	hit = get_hit_result(&r);
	return (hit);
}
