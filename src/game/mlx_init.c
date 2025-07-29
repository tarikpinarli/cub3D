/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 20:01:23 by michoi            #+#    #+#             */
/*   Updated: 2025/07/28 20:01:34 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init(1200, 900, "cub3d", true);
	if (!game->mlx)
		error_exit("MLX initialization failed", game);
}

void	render(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	game->number_of_rays = game->mlx->width;
	update_player(game);
	if (game->image)
		mlx_delete_image(game->mlx, game->image);
	game->image = mlx_new_image(game->mlx, game->mlx->width, game->mlx->height);
	draw_3d(game);
	draw_map(game);
	mlx_image_to_window(game->mlx, game->image, 0, 0);
}
