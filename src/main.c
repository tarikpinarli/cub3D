/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:19:49 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/26 21:42:20 by michoi           ###   ########.fr       */
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

/**
 *
 * initalize game struct according to needs
 * from parsing process to prevent segfaults.
 * could be updated later too.
 *
 */
void	init_game(t_game *game, t_textures *textures, t_map *map,
		t_player *player)
{
	ft_memset(game, 0, sizeof(t_game));
	ft_memset(map, 0, sizeof(t_map));
	ft_memset(textures, 0, sizeof(t_textures));
	ft_memset(player, -1, sizeof(t_player));
	game->textures = textures;
	game->map = map;
	game->player = player;
	ft_memset(&game->floor, -1, sizeof(t_color));
	ft_memset(&game->ceiling, -1, sizeof(t_color));
}

int	main(int argc, char **argv)
{
	t_game		game;
	t_textures	textures;
	t_map		map;
	t_player	player;

	init_game(&game, &textures, &map, &player);
	init_arena(&game);
	if (argc > 1)
	{
		if (parse_cub_file(&game, argc, argv) != 0)
			return (arena_destroy(game.arena), 1);
		return (1);
	}
	init_mlx(&game);
	if (argc == 1)
	{
		if (init_dummy_data(&game) != 0)
			return (arena_destroy(game.arena), 1);
	}
	else
		error_exit("Usage: ./cub3D [map_file.cub] or for dummy map ./cub3D",
			&game);
	mlx_loop_hook(game.mlx, render, &game);
	mlx_key_hook(game.mlx, handle_keypress, &game);
	mlx_loop(game.mlx);
	arena_destroy(game.arena);
	return (0);
}
