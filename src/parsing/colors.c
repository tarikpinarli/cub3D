/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 20:39:35 by michoi            #+#    #+#             */
/*   Updated: 2025/07/29 10:46:58 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	get_nb_comma(char *line)
{
	int	n;

	n = 0;
	if (!line || !*line)
		return (n);
	while (*line)
	{
		if (*line == ',')
			n++;
		line++;
	}
	return (n);
}

int	is_in_rgb_range(int i)
{
	return ((i >= 0) && (i <= 255));
}

static int	parse_rgb_values(char **colors, int *rgb)
{
	int	i;
	int	color;

	if (arrlen(colors) != 3)
		return (print_error_messages("Invalid amount of color values"), 1);
	i = 0;
	while (colors[i])
	{
		if (!is_numeric(colors[i]))
		{
			print_error_messages("Only numeric characters are accepted");
			return (1);
		}
		color = ft_atoi(colors[i]);
		if (!is_in_rgb_range(color))
		{
			print_error_messages("The value should be in the range of [0,255]");
			return (1);
		}
		rgb[i] = color;
		i++;
	}
	return (0);
}

static int	validate_colors(t_game *game, char *metadata,
		char const *identifier)
{
	char	**colors;
	int		rgb[3];

	if (get_nb_comma(metadata) != 2)
		return (print_error_messages("Invalid amount of color values"), 1);
	colors = arena_split(game->arena, metadata, ',');
	if (!colors)
	{
		print_error_messages("arena_split failed");
		return (1);
	}
	if (parse_rgb_values(colors, rgb))
		return (1);
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
