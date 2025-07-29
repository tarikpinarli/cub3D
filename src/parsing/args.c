/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:50:02 by michoi            #+#    #+#             */
/*   Updated: 2025/07/29 10:51:26 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_parsed_info(t_game *game)
{
	return (game->textures->north_path && game->textures->south_path
		&& game->textures->east_path && game->textures->west_path
		&& is_in_rgb_range(game->floor.r) && is_in_rgb_range(game->floor.g)
		&& is_in_rgb_range(game->floor.b) && is_in_rgb_range(game->ceiling.r)
		&& is_in_rgb_range(game->ceiling.g)
		&& is_in_rgb_range(game->ceiling.b));
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
