/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 18:03:00 by michoi            #+#    #+#             */
/*   Updated: 2025/07/26 21:36:23 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	move_lines_until_map(t_game *game, char *file)
{
	int	i;
	int	map_fd;

	map_fd = open_file(file);
	if (map_fd == -1)
		return (-1);
	i = 0;
	while (i < game->map->start_line)
	{
		get_line(game, map_fd);
		i++;
	}
	return (map_fd);
}

int	copy_map_line(t_game *game, int fd)
{
	int		i;
	char	*row;
	char	*line;

	i = 0;
	while (i < game->map->height)
	{
		line = get_line(game, fd);
		row = arena_alloc(game->arena, game->map->width + 1);
		if (!row || !line)
		{
			print_error_messages("Cannot get a map line");
			return (1);
		}
		ft_strlcpy(row, line, game->map->width + 1);
		game->map->grid[i] = row;
		i++;
	}
	game->map->grid[i] = 0;
	return (0);
}

int	copy_map(t_game *game, char *file)
{
	int	map_fd;

	game->map->grid = (char **)arena_alloc(game->arena, sizeof(char *)
			* (game->map->height + 1));
	if (!game->map->grid)
	{
		print_error_messages("Map initialization failed");
		return (1);
	}
	map_fd = move_lines_until_map(game, file);
	if (map_fd == -1)
		return (1);
	if (copy_map_line(game, map_fd))
		return (1);
	close(map_fd);
	return (0);
}

/**
 * Set player's direction based on the character on the map
 * There should be only one character from N, S, E, or W.
 */
int	set_player_direction(t_player *player, char direction)
{
	if (player->dir >= 0)
	{
		print_error_messages("The number of player is more than one");
		return (1);
	}
	if (direction == N)
		player->dir = t_dir.north;
	else if (direction == S)
		player->dir = t_dir.south;
	else if (direction == E)
		player->dir = t_dir.east;
	else if (direction == W)
		player->dir = t_dir.west;
	else
	{
		print_error_messages("Invalid direction");
		return (1);
	}
	return (0);
}

int	validate_map(t_game *game, char *line)
{
	int	i;

	if (!line || !*line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '0' && line[i] != '1' && line[i] != N
			&& line[i] != S && line[i] != E && line[i] != W)
		{
			print_error_messages("Invalid character in the map");
			return (1);
		}
		if (line[i] == N || line[i] == S || line[i] == E || line[i] == W)
		{
			if (set_player_direction(game->player, line[i]))
				return (1);
		}
		i++;
	}
	if (game->map->width < i)
		game->map->width = i;
	game->map->height += 1;
	return (0);
}

/**
 * Check if the wall is surrounded by walls properly
 *
 */
int	check_wall(t_map *m)
{
	int		x;
	int		y;
	char	**map;

	map = m->grid;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0')
			{
				if (y == 0 || x == 0 || y == m->height || !map[y][x + 1])
				{
					print_error_messages("The wall doesn't properly surround the map");
					return (1);
				}
				if (map[y][x - 1] == ' ' || map[y][x + 1] == ' ')
					return (1);
				if (map[y - 1][x] == ' ' || map[y + 1][x] == ' ')
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	set_player_position(char **map, t_player *player)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == N || map[y][x] == S || map[y][x] == E
				|| map[y][x] == W)
			{
				player->x = x + 0.5;
				player->y = y + 0.5;
			}
			else if (map[y][x] != '0' && map[y][x] != '1' && map[y][x] != ' ')
			{
				print_error_messages("Invalid character in the map");
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}
