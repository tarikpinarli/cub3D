/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:19:49 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/16 16:20:28 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/*
** This main function is set up so we can both work independently:
**
** - If a .cub file is given as an argument, your parsing code will run.
**
** - If no arguments are given, the program runs with dummy data.
**   This lets me test rendering, movement, raycasting, etc.
**
** - If too many arguments are given, the program shows a usage error.
**
** This way, you can work on parsing, and I can work on rendering
** without blocking each other.
*/

int	main(int argc, char **argv)
{
	t_game	game;

	init_arena(&game);
	init_mlx(&game);
	if (argc == 2)
	{
		(void)argv;
		// This is your part :)
		// if (parse_map(argv[1], &game) != 0)
		// 	return (arena_destroy(game.arena), 1);
	}
	else if (argc == 1)
	{
		if (init_dummy_data(&game) != 0)
		 	return (arena_destroy(game.arena), 1);
	}
	else
		error_exit("Usage: ./cub3D [map_file.cub] or for dummy map ./cub3D", &game);

	mlx_loop_hook(game.mlx, render, &game);
	mlx_key_hook(game.mlx, handle_keypress, &game);
	mlx_loop(game.mlx);
	arena_destroy(game.arena);
	return (0);
}



