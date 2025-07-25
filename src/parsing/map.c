/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 18:03:00 by michoi            #+#    #+#             */
/*   Updated: 2025/07/25 19:28:55 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"


int	get_map(t_game *game, char *file, int start_line)
{
	int		i;
	int		map_fd;
	char	*line;
	char	*row;

	game->map->grid = (char **)arena_alloc(game->arena, sizeof(char *)
			* (game->map->height + 1));
	if (!game->map->grid)
	{
		print_error_messages("Map initialization failed");
		return (1);
	}
	printf("starts from %d\n", start_line);
	map_fd = open_file(file);
	if (map_fd == -1)
		return (1);
	i = 0;
	while (i < start_line)
	{
		line = get_line(game, map_fd);
		i++;
	}
	i = 0;
	while (1)
	{
		line = get_line(game, map_fd);
		if (!line)
			break ;
		row = arena_alloc(game->arena, game->map->width + 1);
		if (!row)
			return (1);
		ft_memset(row, ' ', game->map->width + 1);
		ft_strlcpy(row, line, game->map->width + 1);
		row[game->map->width] = 0;
		game->map->grid[i] = row;
		// printf("line len: %zu, row: %zu, %s\n", ft_strlen(line),
		// 	ft_strlen(row), row);
		i++;
	}
	game->map->grid[i] = 0;
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
		player->dir = DIR_NORTH;
	else if (direction == S)
		player->dir = DIR_SOUTH;
	else if (direction == E)
		player->dir = DIR_EAST;
	else if (direction == W)
		player->dir = DIR_WEST;
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
				if (y == 0 || x == 0)
					return (1);
				if (y == m->height || x == m->width - 1)
					return (1);
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
