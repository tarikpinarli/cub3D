/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:19:49 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/07 16:05:31 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

//void	set_arena(t_arena **arena)
//{
//	*arena = arena_init(10000);
//	if (!*arena)
//		error_exit("Arena allocation failed.");
//}

int	render_frame(t_game *game)
{
	// x:100, y:100 konumuna kırmızı piksel (0xFF0000) çiz
	mlx_pixel_put(game->mlx, game->win, 100, 100, 0xFF0000);
	return (0);
}

int	main(void)
{
	t_game	game;

	init_game(&game);
	mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_loop(game.mlx);
	return (0);
}


