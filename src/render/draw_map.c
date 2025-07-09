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

void	draw_map(t_game *game)
{
	for (int y = 0; y < game->map->height; ++y)
	{
		for (int x = 0; x < game->map->width; ++x)
		{
			char c = game->map->grid[y][x];
			uint32_t color;

			if (c == '1')
				color = 0xFF0000FF; // red walls
			else if (c == '0')
				color = 0x00000000; // transparent or black floor
			else
				color = 0x00FF00FF; // something else

			for (int dy = 0; dy < TILE_SIZE; ++dy)
			{
				for (int dx = 0; dx < TILE_SIZE; ++dx)
				{
					int px = x * TILE_SIZE + dx;
					int py = y * TILE_SIZE + dy;
					mlx_put_pixel(game->image, px, py, color);
				}
			}
		}
	}
}

