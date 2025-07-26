/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:31:08 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/26 13:48:25 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	draw_vertical_line(t_game *game, int x, int start, int end,
		uint32_t color)
{
	int	y;

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

void	draw_3d(t_game *game)
{
	t_draw3d	d;

	d.floor = (game->floor.r << 24) | (game->floor.g << 16) | (game->floor.b << 8) | 0xFF;
	d.ceiling = (game->ceiling.r << 24) | (game->ceiling.g << 16) | (game->ceiling.b << 8) | 0xFF;
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
