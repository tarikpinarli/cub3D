/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:31:08 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/21 16:40:55 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	t_map *map;
	double ray_dir_x;
	double ray_dir_y;
	int map_x;
	int map_y;
	double delta_dist_x;
	double delta_dist_y;
	int step_x, step_y;
	double side_dist_x, side_dist_y;
	int hit_wall;
	int side;

	map = game->map;
	ray_dir_x = cos(ray_angle);
	ray_dir_y = sin(ray_angle);
	map_x = (int)game->player->x;
	map_y = (int)game->player->y;
	delta_dist_x = fabs(1 / ray_dir_x);
	delta_dist_y = fabs(1 / ray_dir_y);
	hit_wall = 0;
	if (ray_dir_x > 0) 
	{
		step_x = -1;
		side_dist_x = (game->player->x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - game->player->x) * delta_dist_x;
	}
	if (ray_dir_y > 0)
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
			side = 0; // X side?
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

	if (side == 0)
		hit.distance = (side_dist_x - delta_dist_x);
	else
		hit.distance = (side_dist_y - delta_dist_y);

	if (side == 0)
	{
		if (ray_dir_x < 0)
			hit.wall_dir = 1;
		else
			hit.wall_dir = 2;
	}
	else  // SOUTH : NORTH
	{
		if (ray_dir_y < 0)
			hit.wall_dir = 4;
		else
			hit.wall_dir = 3;
	}

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

static void draw_texture_stripe(t_game *game, int ray_x, int start, int end,
								double wall_height, t_ray_hit hit, double ray_angle)
{
	mlx_texture_t *tex = NULL;
	double wall_hit;
	int tex_x, tex_y;
	int y;

	// 1. Doğru texture’ı seç
	if (hit.wall_dir == 1)
		tex = game->textures->west_png;
	else if (hit.wall_dir == 2)
		tex = game->textures->east_png;
	else if (hit.wall_dir == 3)
		tex = game->textures->north_png;
	else if (hit.wall_dir == 4)
		tex = game->textures->south_png;

	// Güvenlik: Texture NULL ise çizim yapma
	if (!tex || !tex->pixels)
		return;

	// 2. Duvarın çarpma noktası (X veya Y ekseni üzerinde)
	if (hit.wall_dir == 1 || hit.wall_dir == 2)
		wall_hit = -game->player->y + hit.distance * sin(ray_angle);
	else
		wall_hit = -game->player->x + hit.distance * cos(ray_angle);
	wall_hit -= floor(wall_hit);

	// 3. Texture X koordinatını hesapla
	tex_x = (int)(wall_hit * tex->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= (int)tex->width)
		tex_x = tex->width - 1;
	if (hit.wall_dir == 2 || hit.wall_dir == 4) // EAST, SOUTH => flip
		tex_x = tex->width - tex_x - 1;

	// 4. Ekrana çizim (pixel-by-pixel)
	for (y = start; y < end; y++)
	{
		if (y < 0 || y >= (int)game->mlx->height)
			continue;

		int d = y * 256 - game->mlx->height * 128 + wall_height * 128;
		tex_y = ((d * tex->height) / (int)wall_height) / 256;

		// Sınır kontrolü
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= (int)tex->height)
			tex_y = tex->height - 1;

		uint8_t *pixel = (uint8_t *)tex->pixels;
		int index = (tex_y * tex->width + tex_x) * 4;

		uint8_t r = pixel[index + 0];
		uint8_t g = pixel[index + 1];
		uint8_t b = pixel[index + 2];
		uint8_t a = pixel[index + 3];

		uint32_t color = (r << 24) | (g << 16) | (b << 8) | a;

		mlx_put_pixel(game->image, ray_x, y, color);
	}
}




void draw_3d(t_game *game)
{
	double		dir;
	double		start_angle;
	double		angle_step;
	int			ray;
	uint32_t	floor;
	uint32_t	ceiling;

	double ray_angle;
	t_ray_hit hit;
	double corrected_dist;
	double wall_height;
	int start;
	int end;

	floor = (game->floor.r << 24) | (game->floor.g << 16) | (game->floor.b << 8) | 0xFF;
	ceiling = (game->ceiling.r << 24) | (game->ceiling.g << 16) | (game->ceiling.b << 8) | 0xFF;
	dir = game->player->dir;
	start_angle = dir - (FOV / 2);
	angle_step = FOV / game->number_of_rays;
	ray = 0;
	while (ray < game->number_of_rays)
	{
		ray_angle = start_angle + ray * angle_step;
		hit = cast_ray(game, ray_angle);

		// Fish-eye correction
		corrected_dist = hit.distance * cos(ray_angle - dir);
		wall_height = game->mlx->height / corrected_dist;

		start = (game->mlx->height / 2) - (wall_height / 2);
		end = start + wall_height;

		// ceiling
		draw_vertical_line(game, ray, 0, start, ceiling);
		draw_texture_stripe(game, ray, start, end, wall_height, hit, ray_angle);

		draw_vertical_line(game, ray, end, game->mlx->height, floor);

		ray++;
	}
}

