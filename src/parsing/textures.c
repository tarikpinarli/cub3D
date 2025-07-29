/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:55:44 by michoi            #+#    #+#             */
/*   Updated: 2025/07/28 13:08:52 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	validate_texture_path(char **dir_path, char *file_path)
{
	int	fd;

	if (dir_path && *dir_path)
	{
		print_error_messages("Duplicate identifier");
		return (1);
	}
	fd = open_file(file_path);
	if (fd == -1)
		return (1);
	close(fd);
	*dir_path = file_path;
	return (0);
}

int	get_wall_texture(t_game *game, char *metadata)
{
	int			i;
	char		*identifier;
	char const	*dirs[] = {NO, SO, WE, EA};
	char		**paths[4];

	paths[0] = &game->textures->north_path;
	paths[1] = &game->textures->south_path;
	paths[2] = &game->textures->west_path;
	paths[3] = &game->textures->east_path;
	identifier = metadata;
	if (process_metadata(&metadata))
		return (1);
	i = 0;
	while (i < 4)
	{
		if (!ft_strncmp(identifier, dirs[i], 3))
			return (validate_texture_path(paths[i], metadata));
		i++;
	}
	print_error_messages("Invalid identifier");
	return (1);
}
