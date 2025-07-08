/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:36:38 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/08 19:38:45 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	close_window(t_game *game)
{
	if (game->mlx)
		mlx_terminate(game->mlx);
	if (game->arena)
		arena_destroy(game->arena);
	exit(0);
}
