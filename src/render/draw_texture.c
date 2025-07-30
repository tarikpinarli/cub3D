/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 13:23:47 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/30 13:56:04 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/**
 * screen_y: Current screen y-coordinate
 * texture_y: Y-coordinate in texture
 * scaled_height: Helps map screen coordinates to texture
 * pixel_color:  Final color including shading
 */
static void	draw_stripe_pixels(t_game *game, t_draw3d *draw_data,
		mlx_texture_t *wall_texture, int texture_x)
{
	int			screen_y;
	int			texture_y;
	int			scaled_height;
	uint32_t	pixel_color;

	screen_y = draw_data->start;
	while (screen_y < draw_data->end)
	{
		if (screen_y >= 0 && screen_y < (int)game->mlx->height)
		{
			scaled_height = (screen_y * 256) - (game->mlx->height * 128)
				+ (draw_data->wall_height * 128);
			texture_y = ((scaled_height * wall_texture->height)
					/ (int)draw_data->wall_height) / 256;
			if (texture_y < 0)
				texture_y = 0;
			if (texture_y >= (int)wall_texture->height)
				texture_y = wall_texture->height - 1;
			pixel_color = get_pixel_color(wall_texture, texture_x, texture_y,
					draw_data->corrected_dist);
			mlx_put_pixel(game->image, draw_data->ray, screen_y, pixel_color);
		}
		screen_y++;
	}
}

static int	compute_tex_x(double wall_hit, int tex_width, int wall_dir)
{
	int	tex_x;

	tex_x = (int)(wall_hit * tex_width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex_width)
		tex_x = tex_width - 1;
	if (wall_dir == EAST_WALL || wall_dir == SOUTH_WALL)
		tex_x = tex_width - tex_x - 1;
	return (tex_x);
}

static double	compute_wall_hit(t_game *game, t_draw3d *d)
{
	double	wall_hit;

	if (d->hit.wall_dir == WEST_WALL || d->hit.wall_dir == EAST_WALL)
		wall_hit = game->player->y + d->hit.distance * sin(d->ray_angle);
	else
		wall_hit = game->player->x + d->hit.distance * cos(d->ray_angle);
	return (wall_hit - floor(wall_hit));
}

static mlx_texture_t	*get_wall_texture_raycast(t_game *game, int wall_dir)
{
	if (wall_dir == WEST_WALL)
		return (game->textures->west_png);
	else if (wall_dir == EAST_WALL)
		return (game->textures->east_png);
	else if (wall_dir == NORTH_WALL)
		return (game->textures->north_png);
	else if (wall_dir == SOUTH_WALL)
		return (game->textures->south_png);
	return (NULL);
}

void	draw_texture_stripe(t_game *game, t_draw3d *d)
{
	mlx_texture_t	*tex;
	double			wall_hit;
	int				tex_x;

	tex = get_wall_texture_raycast(game, d->hit.wall_dir);
	if (!tex || !tex->pixels)
		return ;
	wall_hit = compute_wall_hit(game, d);
	tex_x = compute_tex_x(wall_hit, tex->width, d->hit.wall_dir);
	draw_stripe_pixels(game, d, tex, tex_x);
}
