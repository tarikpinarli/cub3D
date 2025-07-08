/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:23:17 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/08 19:33:42 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_game(t_game *game)
{
	game->arena = arena_init(100000);
	if (!game->arena)
		error_exit("Arena allocation failed", NULL);
	game->mlx = mlx_init(800, 600, "cub3d", true);
	if (!game->mlx)
		error_exit("MLX initialization failed", game);
}
