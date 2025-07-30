/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:52:43 by michoi            #+#    #+#             */
/*   Updated: 2025/07/30 13:02:28 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_player(char c)
{
	return (c == N || c == S || c == E || c == W);
}

// int	is_valid_tile(char c)
// {
// 	return (is_player(c) || c == '0');
// }

int	check_tile(char **map, int y, int x, int height)
{
	if (y == 0 || x == 0 || y == height - 1 || !map[y][x + 1])
	{
		print_error_messages("The wall doesn't properly surround the map");
		return (1);
	}
	if (map[y][x - 1] == ' ' || map[y][x + 1] == ' ')
	{
		print_error_messages("Space left/right of the tile is invalid");
		return (1);
	}
	if (map[y - 1][x] == ' ' || map[y + 1][x] == ' ')
	{
		print_error_messages("Space above/below the tile is invalid");
		return (1);
	}
	return (0);
}

/**
 * Check if the wall is surrounded by walls properly
 * if the player is in the right place
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
			if (map[y][x] == '0' || is_player(map[y][x]))
			{
				if (check_tile(map, y, x, m->height))
					return (1);
			}
			// else if (map[y][x] == ' ')
			// {
			// 	if ((x > 0 && !is_valid_tile(map[y][x - 1])) || (map[y][x + 1]
			// 			&& !is_valid_tile(map[y][x + 1])) || (y > 0
			// 			&& !is_valid_tile(map[y - 1][x])) || (map[y + 1] && map[y
			// 			+ 1][x] && !is_valid_tile(map[y + 1][x])))
			// 	{
			// 		print_error_messages("Space touches a walkable tile");
			// 		return (1);
			// 	}
			// }
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
			if (is_player(map[y][x]))
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

/**
 * Set player's direction based on the character on the map
 * There should be only one character from N, S, E, or W.
 */
int	set_player_direction(t_game *game, char direction)
{
	t_player	*player;
	t_dirs		dirs;

	player = game->player;
	dirs = game->dirs;
	if (player->dir >= 0)
	{
		print_error_messages("The number of player is more than one");
		return (1);
	}
	if (direction == N)
		player->dir = dirs.north;
	else if (direction == S)
		player->dir = dirs.south;
	else if (direction == E)
		player->dir = dirs.east;
	else if (direction == W)
		player->dir = dirs.west;
	else
	{
		print_error_messages("Invalid direction");
		return (1);
	}
	return (0);
}
