/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:31:08 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/26 13:48:12 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

#define MINIMAP_TILE 5

static void	draw_minimap_tile(t_game *game, t_draw2d *m)
{
	m->dy = 0;
	while (m->dy < MINIMAP_TILE)
	{
		m->dx = 0;
		while (m->dx < MINIMAP_TILE)
		{
			m->px = m->offset_x + m->x * MINIMAP_TILE + m->dx;
			m->py = m->offset_y + m->y * MINIMAP_TILE + m->dy;
			if (m->px >= 0 && m->px < game->mlx->width && m->py >= 0
				&& m->py < game->mlx->height)
				mlx_put_pixel(game->image, m->px, m->py, m->color);
			m->dx++;
		}
		m->dy++;
	}
}

static void	draw_minimap_background(t_game *game, t_draw2d *m)
{
	m->y = 0;
	while (m->y < game->map->height)
	{
		m->x = 0;
		while (m->x < game->map->width)
		{
			m->c = game->map->grid[m->y][m->x];
			m->color = 0x00FF00FF;
			if (m->c == '1')
				m->color = 0xF7700088;
			else if (m->c == '0')
				m->color = 0x00000000;
			draw_minimap_tile(game, m);
			m->x++;
		}
		m->y++;
	}
}

static void	draw_minimap_player(t_game *game, t_draw2d *m)
{
	m->player_px = m->offset_x + game->player->x * MINIMAP_TILE;
	m->player_py = m->offset_y + game->player->y * MINIMAP_TILE;
	m->dy = -2;
	while (m->dy <= 2)
	{
		m->dx = -2;
		while (m->dx <= 2)
		{
			m->px = m->player_px + m->dx;
			m->py = m->player_py + m->dy;
			if (m->px >= 0 && m->px < game->mlx->width && m->py >= 0
				&& m->py < game->mlx->height)
				mlx_put_pixel(game->image, m->px, m->py, 0xFFFFFFFF);
			m->dx++;
		}
		m->dy++;
	}
}

void	draw_map(t_game *game)
{
	t_draw2d	m;

	m.offset_x = 20;
	m.offset_y = game->mlx->height - (game->map->height * MINIMAP_TILE) - 20;
	draw_minimap_background(game, &m);
	draw_minimap_player(game, &m);
}
