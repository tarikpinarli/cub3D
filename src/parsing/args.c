/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:50:02 by michoi            #+#    #+#             */
/*   Updated: 2025/07/23 21:57:25 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	open_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd("Error", STDERR_FILENO);
		perror(file);
		return (-1);
	}
	return (fd);
}

int	check_args(int argc, char **argv)
{
	int	map_fd;

	if (argc <= 1)
	{
		print_error_messages("No map file provided");
		return (1);
	}
	if (argc > 2)
	{
		print_error_messages("Too many arguments. Put one file");
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
	printf("player position: %f\n", game->player->dir);
	puts("-------------------------------------------");
}

int	check_parsed_info(t_game *game)
{
	return (game->textures->north_path && game->textures->south_path
		&& game->textures->east_path && game->textures->west_path
		&& is_in_rgb_range(game->floor.r) && is_in_rgb_range(game->floor.g)
		&& is_in_rgb_range(game->floor.b) && is_in_rgb_range(game->ceiling.r)
		&& is_in_rgb_range(game->ceiling.g)
		&& is_in_rgb_range(game->ceiling.b));
}

/**
 * Check if given argument is valid.
 * If the argument is valid, open the file and extract the data inside.
 * @param argc: number of arguments from the main function
 * @param argv: argument array from the main function
 * @param game: pointer to the game   struct
 */
int	parse_map(t_game *game, int argc, char **argv)
{
	int		map_fd;
	char	*line;

	if (check_args(argc, argv))
		return (1);
	map_fd = open_file(argv[1]);
	if (map_fd == -1)
		return (1);
	line = get_line(game, map_fd);
	while (line)
	{
		if (ft_strncmp(line, "\n", ft_strlen(line)))
		{
			if (!ft_strncmp(line, NO, 3) || !ft_strncmp(line, SO, 3)
				|| !ft_strncmp(line, WE, 3) || !ft_strncmp(line, EA, 3))
			{
				if (get_wall_texture(game, line))
					return (1); // invalid map
			}
			else if (!ft_strncmp(line, F, 2) || !ft_strncmp(line, C, 2))
			{
				if (get_rgb_color(game, line))
					return (1);
			}
			else
			{
				if (!check_parsed_info(game))
				{
					print_error_messages("Necessary information befor map is lacking");
					return (1);
				}
				// map validation
				if (validate_map(game, line))
				{
					print_error_messages("Invalid identifier");
					return (1);
				}
			}
		}
		line = get_line(game, map_fd);
	}
	print_parsed_info(game);
	game->map->grid = (char **)arena_alloc(game->arena, (game->map->width + 1)
			* (game->map->height + 1));
	if (!game->map->grid)
	{
		print_error_messages("Map initialization failed");
		return (1);
	}
	close(map_fd);
	return (0);
}
