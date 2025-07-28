/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:31:08 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/28 20:08:49 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	draw_vertical_line(t_game *game, t_line *line)
{
	int	y;

	if (line->start < 0)
		line->start = 0;
	if (line->end >= (int)game->mlx->height)
		line->end = game->mlx->height - 1;
	y = line->start;
	while (y <= line->end)
	{
		mlx_put_pixel(game->image, line->x, y, line->color);
		y++;
	}
}

static void	init_draw_data(t_game *game, t_draw3d *d)
{
	t_color	*f;
	t_color	*c;

	f = &game->floor;
	c = &game->ceiling;
	d->floor = (f->b << 24) | (f->g << 16) | (f->b << 8) | 0xFF;
	d->ceiling = (c->b << 24) | (c->g << 16) | (c->b << 8) | 0xFF;
	d->dir = game->player->dir;
	d->start_angle = d->dir - (FOV / 2);
	d->angle_step = FOV / game->number_of_rays;
	d->ray = 0;
}

static void	calculate_wall_dimensions(t_game *game, t_draw3d *d)
{
	d->corrected_dist = d->hit.distance * cos(d->ray_angle - d->dir);
	d->wall_height = game->mlx->height / d->corrected_dist;
	d->start = (game->mlx->height / 2) - (d->wall_height / 2);
	d->end = d->start + d->wall_height;
}

static void	draw_wall_section(t_game *game, t_draw3d *d)
{
	t_line	line;

	line = (t_line){d->ray, 0, d->start, d->ceiling};
	draw_vertical_line(game, &line);
	draw_texture_stripe(game, d);
	line = (t_line){d->ray, d->end, game->mlx->height, d->floor};
	draw_vertical_line(game, &line);
}

void	draw_3d(t_game *game)
{
	t_draw3d	d;

	init_draw_data(game, &d);
	while (d.ray < game->number_of_rays)
	{
		d.ray_angle = d.start_angle + (d.ray * d.angle_step);
		d.hit = cast_ray(game, d.ray_angle);
		if (d.hit.distance == 0)
		{
			printf("Ray %d hit nothing\n", d.ray);
			close_window(game);
		}
		calculate_wall_dimensions(game, &d);
		draw_wall_section(game, &d);
		d.ray++;
	}
}
