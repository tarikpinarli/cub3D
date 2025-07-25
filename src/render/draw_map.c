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

#include <cub3d.h>

#define MINIMAP_TILE 5

void	draw_map(t_game *game)
{
	int offset_x;
	int offset_y;
	int y;
	int x;
	int dx;
	int dy;
	int px;
	int py;
	char c;
	uint32_t color;
	int player_px;
	int player_py;

	offset_x = 20;
	offset_y = game->mlx->height - (game->map->height * MINIMAP_TILE) - 20;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			c = game->map->grid[y][x];
			color = 0x00FF00FF;
			if (c == '1')
				color = 0xF7700088;
			else if (c == '0')
				color = 0x00000000;

			dy = 0;
			while (dy < MINIMAP_TILE)
			{
				dx = 0;
				while (dx < MINIMAP_TILE)
				{
					px = offset_x + x * MINIMAP_TILE + dx;
					py = offset_y + y * MINIMAP_TILE + dy;
					if (px >= 0 && px < game->mlx->width && py >= 0 && py < game->mlx->height)
						mlx_put_pixel(game->image, px, py, color);
					dx++;
				}
				dy++;
			}
			x++;
		}
		y++;
	}

	player_px = offset_x + game->player->x * MINIMAP_TILE;
	player_py = offset_y + game->player->y * MINIMAP_TILE;

	dy = -2;
	while (dy <= 2)
	{
		dx = -2;
		while (dx <= 2)
		{
			px = player_px + dx;
			py = player_py + dy;
			if (px >= 0 && px < game->mlx->width && py >= 0 && py < game->mlx->height)
				mlx_put_pixel(game->image, px, py, 0xFFFFFFFF);
			dx++;
		}
		dy++;
	}
}


