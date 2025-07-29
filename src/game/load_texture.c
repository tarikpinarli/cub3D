/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:13:56 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/29 12:14:27 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	load_textures(t_game *game)
{
	game->textures->north_png = mlx_load_png(game->textures->north_path);
	if (!game->textures->north_png)
		error_exit("Failed to load north texture", game);
	game->textures->south_png = mlx_load_png(game->textures->south_path);
	if (!game->textures->south_png)
		error_exit("Failed to load south texture", game);
	game->textures->east_png = mlx_load_png(game->textures->east_path);
	if (!game->textures->east_png)
		error_exit("Failed to load east texture", game);
	game->textures->west_png = mlx_load_png(game->textures->west_path);
	if (!game->textures->west_png)
		error_exit("Failed to load west texture", game);
}
