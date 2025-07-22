/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 20:39:35 by michoi            #+#    #+#             */
/*   Updated: 2025/07/22 21:26:54 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	is_digit(char c)
{
	return ((c >= '0') && (c <= '9'));
}

static int	is_numeric(char *arg)
{
	if (!arg || !*arg)
		return (0);
	if (*arg == '-' || *arg == '+')
	{
		if (!is_digit(*(arg + 1)))
			return (0);
		arg++;
	}
	while (*arg)
	{
		if (!is_digit(*arg))
			return (0);
		arg++;
	}
	return (1);
}

int	validate_colors(t_game *game, char *metadata, char *identifier)
{
	char	**colors;
	int		r;
	int		g;
	int		b;
	int		i;

	i = 0;
	colors = arena_split(game->arena, metadata, ',');
	if (!colors)
	{
		print_error_messages("arena_split failed");
		return (1);
	}
	if (arrlen(colors) != 3)
	{
		print_error_messages("The program needs three values (R, G, B)");
		return (1);
	}
	while (colors[i])
	{
		if (!is_numeric(colors[i]))
		{
			print_error_messages("Only numeric characters are accepted for colors");
			return (1);
		}
		if (i == 0)
			r = ft_atoi(colors[i]);
		else if (i == 1)
			g = ft_atoi(colors[i]);
		else if (i == 2)
			b = ft_atoi(colors[i]);
		i++;
	}
	// game->floor = ((r << 24) | (g << 16) | (b << 8) | 255);
	if (!ft_strncmp(identifier, F, 2))
	{
		game->floor.r = r;
		game->floor.g = g;
		game->floor.b = b;
	}
	else if (!ft_strncmp(identifier, C, 2))
	{
		game->ceiling.r = r;
		game->ceiling.g = g;
		game->ceiling.b = b;
	}
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
	char	*identifier;

	identifier = metadata;
	if (process_metadata(&metadata))
		return (1);
	if (!ft_strncmp(identifier, F, 2))
	{
		if (validate_colors(game, metadata, F))
			return (1);
	}
	else if (!ft_strncmp(identifier, C, 2))
	{
		if (validate_colors(game, metadata, C))
			return (1);
	}
	else
	{
		print_error_messages("Invalid identifier");
		return (1);
	}
	return (0);
}
