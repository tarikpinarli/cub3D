/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:36:38 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/26 14:37:21 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void free_textures(t_textures *tex)
{
    if (tex->north_png)
        mlx_delete_texture(tex->north_png);
    if (tex->south_png)
        mlx_delete_texture(tex->south_png);
    if (tex->east_png)
        mlx_delete_texture(tex->east_png);
    if (tex->west_png)
        mlx_delete_texture(tex->west_png);
}


void	close_window(t_game *game)
{
	free_textures(game->textures);
	if (game->arena)
		arena_destroy(game->arena);
	exit(0);
}
