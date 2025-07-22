/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_extraction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:55:44 by michoi            #+#    #+#             */
/*   Updated: 2025/07/22 21:02:29 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	process_metadata(char **metadata)
{
	if (!metadata || !*metadata || !**metadata)
	{
		print_error_messages("Identifier is lacking information");
		return (1);
	}
	*metadata += 2;
	while (is_space(**metadata))
		(*metadata)++;
	return (0);
}

int	validate_texture_path(char **dir_path, char *file_path)
{
	int	temp_fd;

	if (dir_path && *dir_path)
	{
		print_error_messages("Duplicate identifier");
		return (1);
	}
	temp_fd = open_file(file_path);
	if (temp_fd == -1)
		return (1);
	close(temp_fd);
	*dir_path = file_path;
	return (0);
}

int	get_wall_texture(t_game *game, char *metadata)
{
	char	*identifier;

	identifier = metadata;
	if (process_metadata(&metadata))
		return (1);
	if (!ft_strncmp(identifier, NO, 3))
	{
		if (validate_texture_path(&(game->textures->north_path), metadata))
			return (1);
	}
	else if (!ft_strncmp(identifier, SO, 3))
	{
		if (validate_texture_path(&(game->textures->south_path), metadata))
			return (1);
	}
	else if (!ft_strncmp(identifier, WE, 3))
	{
		if (validate_texture_path(&(game->textures->west_path), metadata))
			return (1);
	}
	else if (!ft_strncmp(identifier, EA, 3))
	{
		if (validate_texture_path(&(game->textures->east_path), metadata))
			return (1);
	}
	else
	{
		print_error_messages("Invalid identifier");
		return (1);
	}
	return (0);
}
