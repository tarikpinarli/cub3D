/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 18:03:00 by michoi            #+#    #+#             */
/*   Updated: 2025/07/24 14:50:12 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	get_map(t_game *game, char *file, int start_line)
{
	int		i;
	int		map_fd;
	char	*line;

	line = NULL;
	// char	*map_line;
	printf("start from %d\n", start_line);
	map_fd = open_file(file);
	if (map_fd == -1)
		return (1);
	i = 0;
	while (i < start_line)
	{
		line = get_line(game, map_fd);
		i++;
	}
	while (i < game->map->height)
	{
		line = get_line(game, map_fd);
		puts(line);
		game->map->grid[i] = line;
		i++;
	}
	game->map->grid[i] = 0;
	close(map_fd);
	return (0);
}

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
	// printf("line %d: %s\n", game->map->height, line);
	return (0);
}
