/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_extraction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:55:44 by michoi            #+#    #+#             */
/*   Updated: 2025/07/14 14:59:48 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/**
 * Get RGB colors from identifiers (F, C)
 * Shape: (R[0,255], G[0,255], B[0,255])
 * -> colors[0] = R, colors[1] = G, colors[2] = B
 * No transparency needed
 */
int	get_rgb_color(char **metadata)
{
	char	*identifier;
	char	**colors;
	int		r;
	int		g;
	int		b;

	if (!metatdata || !*metatdata || !*(metatdata + 1))
	{
		print_error_messages("Identifier is lacking information.");
		return (1);
	}
	identifier = metadata[1];
	if (identifier != F && identifier != C)
	{
		print_error_messages("Invalid identifier");
		return (1);
	}
	colors = ft_split(metadata[2], ',');
	if (!colors)
		return (1);
	if (arrlen(colors) != 3)
	{
		print_error_messages("Invalid RGB value(s)");
		free(colors);
		return (1);
	}
	// error checkup later?
	r = ft_atoi(colors[0]);
	g = ft_atoi(colors[1]);
	b = ft_atoi(colors[2]);
	if (identifier == F)
		// struct.F = ((r <<) | (g << ) | (b << ) | 255);
	else if (identifier == C)
		// struct.C = ((r <<) | (g << ) | (b << ) | 255);
	return (0);
}

int	get_wall_texture(char **metatdata)
{
	char	*identifier;
	char	*texture;

	if (!metatdata || !*metatdata || !*(metatdata + 1))
	{
		print_error_messages("Identifier is lacking information.");
		return (1);
	}
	identifier = metatdata[1];
	texture = metatdata[2];
	if (!ft_strncmp(identifier, NO, ft_strlen(identifier)))
	{
		// save data
	}
	else if (!ft_strncmp(identifier, SO, ft_strlen(identifier)))
	{
		// save data
	}
	else if (!ft_strncmp(identifier, WE, ft_strlen(identifier)))
	{
		// save data
	}
	else if (!ft_strncmp(identifier, EA, ft_strlen(identifier)))
	{
		// save data
	}
	else
	{
		print_error_messages("Invalid identifier");
		return (1);
	}
	return (0);
}
