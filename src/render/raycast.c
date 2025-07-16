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

typedef struct s_ray_hit {
	double distance;
	int wall_dir; // 1 = WEST, 2 = EAST, 3 = NORTH, 4 = SOUTH
}	t_ray_hit;


static t_ray_hit cast_ray(t_game *game, double ray_angle)
{
	t_ray_hit hit;
	t_map *map = game->map;
	double ray_dir_x = cos(ray_angle);
	double ray_dir_y = sin(ray_angle);
	int map_x = (int)game->player->x;
	int map_y = (int)game->player->y;

	double delta_dist_x = fabs(1 / ray_dir_x);
	double delta_dist_y = fabs(1 / ray_dir_y);

	int step_x, step_y;
	double side_dist_x, side_dist_y;

	int hit_wall = 0;
	int side;

	// Step ve side_dist hesapla
	if (ray_dir_x < 0) // from right to left
	{
		step_x = -1;
		side_dist_x = (game->player->x - map_x) * delta_dist_x;
	}
	else // from left to right
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - game->player->x) * delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (game->player->y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - game->player->y) * delta_dist_y;
	}

	while (!hit_wall)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0; // X tarafı
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1; // Y tarafı
		}
		if (map_x < 0 || map_y < 0 || map_x >= map->width || map_y >= map->height)
			break;
		if (map->grid[map_y][map_x] == '1')
			hit_wall = 1;
	}

	// Mesafe
	if (side == 0)
		hit.distance = (side_dist_x - delta_dist_x);
	else
		hit.distance = (side_dist_y - delta_dist_y);

	// Duvar yönü belirleme
	if (side == 0)
		hit.wall_dir = (ray_dir_x < 0) ? 1 : 2; // WEST : EAST
	else
		hit.wall_dir = (ray_dir_y < 0) ? 4 : 3; // SOUTH : NORTH

	return hit;
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
	double		dir = game->player->dir;
	double		start_angle = dir - (FOV / 2);
	double		angle_step = FOV / NUM_RAYS;
	int			ray = 0;

	uint32_t	floor = (game->floor.r << 24) | (game->floor.g << 16) | (game->floor.b << 8) | 0xFF;
	uint32_t	ceiling = (game->ceiling.r << 24) | (game->ceiling.g << 16) | (game->ceiling.b << 8) | 0xFF;

	while (ray < NUM_RAYS)
	{
		double ray_angle = start_angle + ray * angle_step;
		t_ray_hit hit = cast_ray(game, ray_angle);

		// Fish-eye düzeltme
		double corrected_dist = hit.distance * cos(ray_angle - dir);
		double wall_height = game->mlx->height / corrected_dist;

		int start = (game->mlx->height / 2) - (wall_height / 2);
		int end = start + wall_height;

		// Tavan
		draw_vertical_line(game, ray, 0, start, ceiling);

		// Duvar rengi (WEST kırmızı, diğerleri beyaz örnek)
		uint32_t wall_color;
		if (hit.wall_dir == 1)
			wall_color = 0xFF0000FF; // WEST (kırmızı)
		else
			wall_color = 0xFFFFFFFF; // diğer yönler beyaz

		draw_vertical_line(game, ray, start, end, wall_color);

		// Zemin
		draw_vertical_line(game, ray, end, game->mlx->height, floor);

		ray++;
	}
}

