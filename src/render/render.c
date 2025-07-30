/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 16:12:51 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/30 16:13:09 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	render(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	game->number_of_rays = game->mlx->width;
	update_player(game);
	if (game->image)
		mlx_delete_image(game->mlx, game->image);
	game->image = mlx_new_image(game->mlx, game->mlx->width, game->mlx->height);
	if (!game->image)
		error_exit("game->image fail.", game);
	draw_3d(game);
	draw_map(game);
	mlx_image_to_window(game->mlx, game->image, 0, 0);
}
