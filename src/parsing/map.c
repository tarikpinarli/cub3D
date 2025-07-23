/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 18:03:00 by michoi            #+#    #+#             */
/*   Updated: 2025/07/23 21:58:14 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	set_player_position(t_player *player, char position)
{
	if (position == N)
		player->dir = DIR_NORTH;
	else if (position == S)
		player->dir = DIR_SOUTH;
	else if (position == E)
		player->dir = DIR_EAST;
	else if (position == W)
		player->dir = DIR_WEST;
	else
	{
		print_error_messages("Invalid position");
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
			if (set_player_position(game->player, line[i]))
				return (1);
		}
		i++;
	}
	if (game->map->width < i)
		game->map->width = i;
	game->map->height += 1;
	return (0);
}
