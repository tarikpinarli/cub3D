/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:31:44 by michoi            #+#    #+#             */
/*   Updated: 2025/07/29 11:45:46 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// temp function
void	print_grid(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	puts("-------------------------------------------");
	puts("processed grid");
	printf("height: %d, width: %d\n", map->height, map->width);
	while (j < map->height)
	{
		i = 0;
		while (i < map->width)
		{
			write(1, &map->grid[j][i], 1);
			i++;
		}
		write(1, "\n", 1);
		j++;
	}
	puts("-------------------------------------------");
}

// temp function
static void	print_parsed_info(t_game *game)
{
	puts("-------------------------------------------");
	printf("north_path: %s\n", game->textures->north_path);
	printf("south_path: %s\n", game->textures->south_path);
	printf("east_path: %s\n", game->textures->east_path);
	printf("west_path: %s\n", game->textures->west_path);
	printf("floor r: %d\n", game->floor.r);
	printf("floor g: %d\n", game->floor.g);
	printf("floor b: %d\n", game->floor.b);
	printf("ceiling r: %d\n", game->ceiling.r);
	printf("ceiling g: %d\n", game->ceiling.g);
	printf("ceiling b: %d\n", game->ceiling.b);
	printf("map width: %d\n", game->map->width);
	printf("map height: %d\n", game->map->height);
	printf("player direction: %f\n", game->player->dir);
	printf("player position x: %f\n", game->player->x);
	printf("player position x: %f\n", game->player->y);
	puts("-------------------------------------------");
}

static int	check_args(int argc, char **argv)
{
	int	map_fd;

	if (argc <= 1)
	{
		print_error_messages("No map file provided");
		return (1);
	}
	if (argc > 2)
	{
		print_error_messages("Too many arguments. Use one file");
		return (1);
	}
	if (ft_strrncmp(argv[1], MAP_EXTENSION, ft_strlen(MAP_EXTENSION)))
	{
		print_error_messages("Invalid file extension. Use '*.cub' file");
		return (1);
	}
	map_fd = open_file(argv[1]);
	if (map_fd == -1)
		return (1);
	close(map_fd);
	return (0);
}

/**
 * Check if given argument is valid.
 * If the argument is valid, open the file and extract the data inside.
 * @param game: pointer to the game   struct
 * @param argc: number of arguments from the main function
 * @param argv: argument array from the main function
 */
int	parse_cub_file(t_game *game, int argc, char **argv)
{
	int	cub_fd;

	if (check_args(argc, argv))
		return (1);
	cub_fd = open_file(argv[1]);
	if (cub_fd == -1)
		return (1);
	if (parse_line(game, cub_fd))
		return (1);
	if (game->player->dir < 0)
	{
		print_error_messages("No player in the map");
		return (1);
	}
	close(cub_fd);
	if (!check_parsed_info(game))
	{
		print_error_messages("No information");
		return (1);
	}
	if (copy_map(game, argv[1]))
		return (1);
	if (check_wall(game->map))
		return (1);
	if (set_player_position(game->map->grid, game->player))
		return (1);
	print_grid(game->map);
	print_parsed_info(game);
	return (0);
}
