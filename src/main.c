/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:19:49 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/29 14:23:29 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/**
 *
 * initalize game struct according to needs
 * from parsing process to prevent segfaults.
 * could be updated later too.
 *
 */
static void	init_game(t_game *game, t_textures *textures, t_map *map,
		t_player *player)
{
	ft_memset(game, 0, sizeof(t_game));
	ft_memset(map, 0, sizeof(t_map));
	ft_memset(textures, 0, sizeof(t_textures));
	ft_memset(player, 0, sizeof(t_player));
	game->textures = textures;
	game->map = map;
	game->player = player;
	game->player->dir = -1.0f;
	game->dirs.west = M_PI;
	game->dirs.north = 3 * M_PI_2;
	game->dirs.south = M_PI_2;
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
	}
	load_textures(&game);
	init_mlx(&game);
	mlx_loop_hook(game.mlx, render, &game);
	mlx_key_hook(game.mlx, handle_keypress, &game);
	mlx_loop(game.mlx);
	arena_destroy(game.arena);
	return (0);
}
