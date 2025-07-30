/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:31:08 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/30 13:00:42 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

#define MINIMAP_TILE 10

static void	draw_minimap_tile(t_game *game, t_draw2d *m)
{
	m->tile_py = 0;
	while (m->tile_py < MINIMAP_TILE)
	{
		m->tile_px = 0;
		while (m->tile_px < MINIMAP_TILE)
		{
			m->screen_x = m->map_offset_x + m->map_x * MINIMAP_TILE
				+ m->tile_px;
			m->screen_y = m->map_offset_y + m->map_y * MINIMAP_TILE
				+ m->tile_py;
			if (m->screen_x >= 0 && m->screen_x < game->mlx->width
				&& m->screen_y >= 0 && m->screen_y < game->mlx->height)
				mlx_put_pixel(game->image, m->screen_x, m->screen_y,
					m->tile_color);
			m->tile_px++;
		}
		m->tile_py++;
	}
}

static void	draw_minimap_background(t_game *game, t_draw2d *m)
{
	m->map_y = 0;
	while (m->map_y < game->map->height)
	{
		m->map_x = 0;
		while (m->map_x < game->map->width)
		{
			m->tile_char = game->map->grid[m->map_y][m->map_x];
			if (m->tile_char == '1')
				m->tile_color = 0x0AAE00CF;
			else if (m->tile_char == '0')
				m->tile_color = 0x00000000;
			else
				m->tile_color = 0x00FF00FF;
			draw_minimap_tile(game, m);
			m->map_x++;
		}
		m->map_y++;
	}
}

static void	draw_minimap_player(t_game *game, t_draw2d *m)
{
	m->player_screen_x = m->map_offset_x + game->player->x * MINIMAP_TILE;
	m->player_screen_y = m->map_offset_y + game->player->y * MINIMAP_TILE;
	m->tile_py = 0;
	while (m->tile_py < MINIMAP_TILE)
	{
		m->tile_px = 0;
		while (m->tile_px < MINIMAP_TILE)
		{
			m->screen_x = m->player_screen_x + m->tile_px;
			m->screen_y = m->player_screen_y + m->tile_py;
			if (m->screen_x >= 0 && m->screen_x < game->mlx->width
				&& m->screen_y >= 0 && m->screen_y < game->mlx->height)
				mlx_put_pixel(game->image, m->screen_x, m->screen_y,
					0xFFFFFFFF);
			m->tile_px++;
		}
		m->tile_py++;
	}
}

void	draw_map(t_game *game)
{
	t_draw2d	m;

	m.map_offset_x = 20;
	m.map_offset_y = game->mlx->height - (game->map->height * MINIMAP_TILE)
		- 20;
	draw_minimap_background(game, &m);
	draw_minimap_player(game, &m);
}
