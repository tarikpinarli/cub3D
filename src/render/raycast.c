/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:31:08 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/15 15:54:44 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// src/render/raycast.c
#include <cub3d.h>


#define FOV (60.0 * M_PI / 180.0)
#define NUM_RAYS 800
#define MAX_DEPTH 100.0



static int is_wall(t_map *map, int x, int y, double ray_angle)
{
	double ray_dir_x;
	double ray_dir_y;

	ray_dir_x = cos(ray_angle);
	ray_dir_y = sin(ray_angle);
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (1);

	// Debug: hangi duvar yüzüne çarptığını yazdır

	if (map->grid[y][x] == '1')
	{
		// Duvar yüzü belirleme mantığı:
		if (fabs(ray_dir_x) > fabs(ray_dir_y))
		{
			// Dikey duvara çarptı (x değişimi baskın)
			if (ray_dir_x > 0)
				return (1); //WEST
			else
				return (2); //EAST
		}
		else
		{
			// Yatay duvara çarptı (y değişimi baskın)
			if (ray_dir_y > 0)
				return (3); //NORTH
			else
				return (4); //SOUTH
		}
	}
	return (0);
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
	double	player_curr_x;
	double	player_curr_y;
	double	dir;
	double	start_angle;
	double	angle_step;
	int		ray;
    uint32_t floor;
    uint32_t ceiling;

	double	ray_angle;
	double	power_x;
	double	power_y;
	double	dist;
	double	test_x;
	double	test_y;
	double	wall_height;
	int		start;
	int		end;
	int		wall;

	wall = 0;
    floor = (game->floor.r << 24) | (game->floor.g << 16) | (game->floor.b << 8) | 0xFF;
    ceiling = (game->ceiling.r << 24) | (game->ceiling.g << 16) | (game->ceiling.b << 8) | 0xFF;
	player_curr_x = game->player->x;
	player_curr_y = game->player->y;
	dir = game->player->dir;

	start_angle = dir - (FOV / 2);
	angle_step = FOV / NUM_RAYS;
	ray = 0;
	while (ray < NUM_RAYS)
	{

		ray_angle = start_angle + ray * angle_step;
		power_x = cos(ray_angle);
		power_y = sin(ray_angle);
		dist = 0.0;

		while (dist < MAX_DEPTH)
		{
			test_x = player_curr_x + power_x * dist;
			test_y = player_curr_y + power_y * dist;
			wall = is_wall(game->map, (int)test_x, (int)test_y, ray_angle);
			if (wall > 0)
				break;
			dist += 0.01;
		}
		wall_height = game->mlx->height / (dist * cos(ray_angle - dir)); // Fish eye correction.
		start = (game->mlx->height / 2 /*- game->jump_offset * game->mlx->height*/) - (wall_height / 2);
		end = start + wall_height;

		draw_vertical_line(game, ray, 0, start, ceiling);
		//draw_texture(game, ray, start, end, power_x, power_y);
		if (wall == 1)
			draw_vertical_line(game, ray, start, end, 0xFF0000FF);
		draw_vertical_line(game, ray, end, game->mlx->height, floor);
		ray++;
	}
}
