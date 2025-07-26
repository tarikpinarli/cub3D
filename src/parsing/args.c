/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:50:02 by michoi            #+#    #+#             */
/*   Updated: 2025/07/26 21:14:53 by michoi           ###   ########.fr       */
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
		return (fd);
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
	printf("player position: %f\n", game->player->dir);
	puts("-------------------------------------------");
}

static int	check_parsed_info(t_game *game)
{
	return (game->textures->north_path && game->textures->south_path
		&& game->textures->east_path && game->textures->west_path
		&& is_in_rgb_range(game->floor.r) && is_in_rgb_range(game->floor.g)
		&& is_in_rgb_range(game->floor.b) && is_in_rgb_range(game->ceiling.r)
		&& is_in_rgb_range(game->ceiling.g)
		&& is_in_rgb_range(game->ceiling.b));
}

int	is_empty_line(char *s)
{
	if (!s || !*s)
		return (1);
	while (*s)
	{
		if (!is_space(*s))
			return (0);
		s++;
	}
	return (1);
}

int	process_map_line(t_game *game, char *line, int *map_started, int map_ended)
{
	if (map_ended)
	{
		print_error_messages("Extra character(s) after the map");
		return (1);
	}
	if (!check_parsed_info(game))
	{
		print_error_messages("Necessary information before map is lacking");
		return (1);
	}
	*map_started = 1;
	if (validate_map(game, line))
		return (1);
	return (0);
}

int	parse_identifier(t_game *game, char *line, int *map_started, int map_ended)
{
	if (!ft_strncmp(line, NO, 3) || !ft_strncmp(line, SO, 3)
		|| !ft_strncmp(line, WE, 3) || !ft_strncmp(line, EA, 3))
	{
		(game->map->start_line)++;
		if (get_wall_texture(game, line))
			return (1);
	}
	else if (!ft_strncmp(line, F, 2) || !ft_strncmp(line, C, 2))
	{
		(game->map->start_line)++;
		if (get_rgb_color(game, line))
			return (1);
	}
	else
	{
		if (process_map_line(game, line, map_started, map_ended))
			return (1);
	}
	return (0);
}

int	parse_line(t_game *game, int fd)
{
	int		map_started;
	int		map_ended;
	char	*line;

	map_started = 0;
	map_ended = 0;
	line = get_line(game, fd);
	while (line)
	{
		if (!is_empty_line(line))
		{
			if (parse_identifier(game, line, &map_started, map_ended))
				return (1);
		}
		else
		{
			if (!map_started)
				(game->map->start_line)++;
			else
				map_ended = 1;
		}
		line = get_line(game, fd);
	}
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
	parse_line(game, cub_fd);
	close(cub_fd);
	copy_map(game, argv[1]);
	if (check_wall(game->map))
		return (1);
	set_player_position(game->map->grid, game->player);
	print_grid(game->map);
	print_parsed_info(game);
	return (0);
}
