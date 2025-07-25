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

static void init_step_and_side_dist(t_game *game, t_raycast *r)
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


static int perform_dda(t_map *map, t_raycast *r)
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
		if (r->map_x < 0 || r->map_y < 0 || r->map_x >= map->width || r->map_y >= map->height)
			return (0);
		if (map->grid[r->map_y][r->map_x] == '1')
			return (1);
	}
}


static t_ray_hit get_hit_result(t_raycast *r)
{
	t_ray_hit hit;

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

static void init_raycast(t_game *game, double ray_angle, t_raycast *r)
{
	r->ray_dir_x = cos(ray_angle);
	r->ray_dir_y = sin(ray_angle);
	r->map_x = (int)game->player->x;
	r->map_y = (int)game->player->y;
	r->delta_dist_x = fabs(1 / r->ray_dir_x);
	r->delta_dist_y = fabs(1 / r->ray_dir_y);
}

t_ray_hit cast_ray(t_game *game, double ray_angle)
{
	t_raycast r;
	t_ray_hit hit;

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

static mlx_texture_t *get_wall_texture_raycast(t_game *game, int wall_dir)
{
	if (wall_dir == 1)
		return game->textures->west_png;
	else if (wall_dir == 2)
		return game->textures->east_png;
	else if (wall_dir == 3)
		return game->textures->north_png;
	else if (wall_dir == 4)
		return game->textures->south_png;
	return NULL;
}


static double compute_wall_hit(t_game *game, t_draw3d *d)
{
	double wall_hit;

	if (d->hit.wall_dir == 1 || d->hit.wall_dir == 2)
		wall_hit = game->player->y + d->hit.distance * sin(d->ray_angle);
	else
		wall_hit = game->player->x + d->hit.distance * cos(d->ray_angle);
	return (wall_hit - floor(wall_hit));
}


static int compute_tex_x(double wall_hit, int tex_width, int wall_dir)
{
	int tex_x = (int)(wall_hit * tex_width);

	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex_width)
		tex_x = tex_width - 1;

	if (wall_dir == 2 || wall_dir == 4) // EAST or SOUTH → flip X
		tex_x = tex_width - tex_x - 1;

	return tex_x;
}

static uint32_t get_pixel_color(mlx_texture_t *tex, int tex_x, int tex_y)
{
	t_pixel_color	color;
	int				index;
	uint8_t			*pixels;

	index = (tex_y * tex->width + tex_x) * 4;
	pixels = (uint8_t *)tex->pixels;
	color.r = pixels[index + 0];
	color.g = pixels[index + 1];
	color.b = pixels[index + 2];
	color.a = pixels[index + 3];
	return (color.r << 24) | (color.g << 16) | (color.b << 8) | color.a;
}



static void draw_stripe_pixels(t_game *game, t_draw3d *d, mlx_texture_t *tex, int tex_x)
{
	int y;
	int tex_y;
	int d_y;
	uint32_t color;

	y = d->start;
	while (y < d->end)
	{
		if (y >= 0 && y < (int)game->mlx->height)
		{
			d_y = y * 256 - game->mlx->height * 128 + d->wall_height * 128;
			tex_y = ((d_y * tex->height) / (int)d->wall_height) / 256;

			if (tex_y < 0)
				tex_y = 0;
			if (tex_y >= (int)tex->height)
				tex_y = tex->height - 1;

			color = get_pixel_color(tex, tex_x, tex_y);
			mlx_put_pixel(game->image, d->ray, y, color);
		}
		y++;
	}
}



static void draw_texture_stripe(t_game *game, t_draw3d *d)
{
	mlx_texture_t	*tex;
	double			wall_hit;
	int 			tex_x;

	tex = get_wall_texture_raycast(game, d->hit.wall_dir);
	if (!tex || !tex->pixels)
		return;
	wall_hit = compute_wall_hit(game, d);
	tex_x = compute_tex_x(wall_hit, tex->width, d->hit.wall_dir);
	draw_stripe_pixels(game, d, tex, tex_x);
}



void draw_3d(t_game *game)
{
	t_draw3d d;

	d.floor = (game->floor.r << 24) | (game->floor.g << 16)
				| (game->floor.b << 8) | 0xFF;
	d.ceiling = (game->ceiling.r << 24) | (game->ceiling.g << 16)
				| (game->ceiling.b << 8) | 0xFF;
	d.dir = game->player->dir;
	d.start_angle = d.dir - (FOV / 2);
	d.angle_step = FOV / game->number_of_rays;
	d.ray = 0;
	while (d.ray < game->number_of_rays)
	{
		d.ray_angle = d.start_angle + (d.ray * d.angle_step);
		d.hit = cast_ray(game, d.ray_angle);
		d.corrected_dist = d.hit.distance * cos(d.ray_angle - d.dir);
		d.wall_height = game->mlx->height / d.corrected_dist;
		d.start = (game->mlx->height / 2) - (d.wall_height / 2);
		d.end = d.start + d.wall_height;
		draw_vertical_line(game, d.ray, 0, d.start, d.ceiling);
		draw_texture_stripe(game, &d);
		draw_vertical_line(game, d.ray, d.end, game->mlx->height, d.floor);
		d.ray++;
	}
}


