/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:35:31 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/26 14:02:33 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "arena.h"
# include "colors.h"
# include "raycast.h"
# include "move.h"
# include "draw2d.h"
# include "draw3d.h"
# include <cub3d.h>
# include <map.h>
# include <player.h>
# include <textures.h>

# define TILE_SIZE 16

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_arena		*arena;

	t_textures	*textures;
	t_color		floor;
	t_color		ceiling;
	t_map		*map;
	t_player	*player;
	int			number_of_rays;
}				t_game;

#endif
