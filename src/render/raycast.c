/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:31:08 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/09 15:07:42 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// src/render/raycast.c
#include <cub3d.h>


#define FOV (60.0 * M_PI / 180.0)
#define NUM_RAYS 800
#define MAX_DEPTH 100.0



static int is_wall(t_map *map, int x, int y)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (1);
	return (map->grid[y][x] == '1');
}

static void draw_vertical_line(t_game *game, int x, int start, int end, uint32_t color)
{
	int y;

	if (start < 0)
		start = 0;
	if (end >= (int)game->mlx->height)
		end = game->mlx->height - 1;

	y = start;
	while (y <= end)
	{
		mlx_put_pixel(game->image, x, y, color);
		y++;
	}
}

void draw_3d(t_game *game)
{
	double	px;
	double	py;
	double	dir;
	double	start_angle;
	double	angle_step;
	int		ray;
    uint32_t floor;
    uint16_t ceiling;

    floor = (game->floor.r << 24) | (game->floor.g << 16) | (game->floor.b << 8) | 0xFF;
    ceiling = (game->ceiling.r << 24) | (game->ceiling.g << 16) | (game->ceiling.b << 8) | 0xFF;
	px = game->player->x;
	py = game->player->y;
	dir = game->player->dir;

	start_angle = dir - (FOV / 2);
	angle_step = FOV / NUM_RAYS;
	ray = 0;
	while (ray < NUM_RAYS)
	{
		double	ray_angle;
		double	ray_x;
		double	ray_y;
		double	dist;
		double	test_x;
		double	test_y;
		double	wall_height;
		int		start;
		int		end;

		ray_angle = start_angle + ray * angle_step;
		ray_x = cos(ray_angle);
		ray_y = sin(ray_angle);
		dist = 0.0;

		while (dist < MAX_DEPTH)
		{
			test_x = px + ray_x * dist;
			test_y = py + ray_y * dist;
			if (is_wall(game->map, (int)test_x, (int)test_y))
				break;
			dist += 0.001;
		}
		wall_height = game->mlx->height / (dist * cos(ray_angle - dir)); // Fish eye correction.
		start = (game->mlx->height / 2 - game->jump_offset * game->mlx->height) - (wall_height / 2);
		end = start + wall_height;

		draw_vertical_line(game, ray, 0, start, ceiling);
		draw_vertical_line(game, ray, start, end, 0xFF0000FF);
		draw_vertical_line(game, ray, end, game->mlx->height, floor);
		ray++;
	}
}
