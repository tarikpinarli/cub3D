/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 18:03:00 by michoi            #+#    #+#             */
/*   Updated: 2025/07/30 13:34:03 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	move_lines_until_map(t_game *game, char *file)
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

static int	copy_map_line(t_game *game, int fd)
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
		ft_memset(row, ' ', game->map->width);
		row[game->map->width] = '\0';
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

int	validate_map(t_game *game, char *line)
{
	int	i;

	if (!line || !*line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '0' && line[i] != '1'
			&& !is_player(line[i]))
		{
			print_error_messages("Invalid character in the map");
			return (1);
		}
		if (is_player(line[i]))
		{
			if (set_player_direction(game, line[i]))
				return (1);
		}
		i++;
	}
	if (game->map->width < i)
		game->map->width = i;
	game->map->height += 1;
	return (0);
}
