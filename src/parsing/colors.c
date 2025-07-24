/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 20:39:35 by michoi            #+#    #+#             */
/*   Updated: 2025/07/24 12:29:50 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_in_rgb_range(int i)
{
	return ((i >= 0) && (i <= 255));
}

static int	parse_rgb_values(char **colors, int *rgb)
{
	int	i;
	int	i_color;

	if (arrlen(colors) != 3)
		return (print_error_messages("Invalid amount of values"), 1);
	i = 0;
	while (colors[i])
	{
		if (!is_numeric(colors[i]))
		{
			print_error_messages("Only numeric characters are accepted");
			return (1);
		}
		i_color = ft_atoi(colors[i]);
		if (!is_in_rgb_range(i_color))
		{
			print_error_messages("The value should be in the range of [0,255]");
			return (1);
		}
		rgb[i] = i_color;
		i++;
	}
	return (0);
}

static int	validate_colors(t_game *game, char *metadata,
		char const *identifier)
{
	char	**colors;
	int		rgb[3];

	colors = arena_split(game->arena, metadata, ',');
	if (!colors)
	{
		print_error_messages("arena_split failed");
		return (1);
	}
	if (parse_rgb_values(colors, rgb))
		return (1);
	// game->floor = ((r << 24) | (g << 16) | (b << 8) | 255);
	if (!ft_strncmp(identifier, F, 2))
		game->floor = (t_color){rgb[0], rgb[1], rgb[2]};
	else if (!ft_strncmp(identifier, C, 2))
		game->ceiling = (t_color){rgb[0], rgb[1], rgb[2]};
	else
	{
		print_error_messages("Invalid identifier");
		return (1);
	}
	return (0);
}

/**
 * Get RGB colors from identifiers (F, C)
 * Shape: (R[0,255], G[0,255], B[0,255])
 * -> colors[0] = R, colors[1] = G, colors[2] = B
 * No transparency needed
 * overflow/underflow possible?
 */
int	get_rgb_color(t_game *game, char *metadata)
{
	int			i;
	char		*identifier;
	char const	*dirs[] = {F, C};
	t_color		*targets[2];

	targets[0] = &game->floor;
	targets[1] = &game->ceiling;
	identifier = metadata;
	if (process_metadata(&metadata))
		return (1);
	i = 0;
	while (i < 2)
	{
		if (!ft_strncmp(identifier, dirs[i], 2))
		{
			if (targets[i]->r >= 0 && targets[i]->g >= 0 && targets[i]->b >= 0)
				return (print_error_messages("Duplicate identifier"), 1);
			return (validate_colors(game, metadata, dirs[i]));
		}
		i++;
	}
	print_error_messages("Invalid identifier");
	return (1);
}
