/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 20:01:23 by michoi            #+#    #+#             */
/*   Updated: 2025/07/31 17:08:04 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init(1200, 900, "cub3d", true);
	if (!game->mlx)
		error_exit("MLX initialization failed", game);
}
