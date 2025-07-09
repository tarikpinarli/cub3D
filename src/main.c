/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:19:49 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/09 15:13:18 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init(800, 600, "cub3d", true);
	if (!game->mlx)
		error_exit("MLX initialization failed", game);
}
void	render(void *param)
{
	t_game *game;

	game = (t_game *)param;
	if (game->image)
		mlx_delete_image(game->mlx, game->image);
	game->image = mlx_new_image(game->mlx, 800, 600);

	draw_map(game);

	mlx_image_to_window(game->mlx, game->image, 0, 0);
}


int	main(int argc, char **argv)
{
	t_game	game;

	init_arena(&game);
	if (argc == 2)
	{
		(void)argv;
		// if (parse_map(argv[1], &game) != 0)
		// 	return (arena_destroy(game.arena), 1);
	}
	else if (argc == 1)
	{
		if (init_dummy_data(&game) != 0)
		 	return (arena_destroy(game.arena), 1);
		if (!game.map || !game.map->grid)
			error_exit("Map initialization failed", &game);
		if (!game.textures)
			error_exit("Textures initialization failed", &game);
		if (!game.player)
			error_exit("Player initialization failed", &game);
	}
	else
		error_exit("Usage: ./cub3D [map_file.cub] or for dummy map ./cub3D", &game);

	int i = 0;
	while (game.map->grid[i])
	{
		printf("%s\n", game.map->grid[i]);
		i++;
	}
	printf("testure north: %s\n", game.textures->north);
	printf("testure south: %s\n", game.textures->south);
	printf("testure east: %s\n", game.textures->east);
	printf("testure west: %s\n", game.textures->west);
	init_mlx(&game);
	mlx_loop_hook(game.mlx, render, &game);
	mlx_key_hook(game.mlx, handle_keypress, &game);
	mlx_loop(game.mlx);
	arena_destroy(game.arena);
	return (0);
}



