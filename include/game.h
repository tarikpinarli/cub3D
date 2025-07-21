/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:35:31 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/16 16:39:43 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
#define GAME_H
#include "arena.h"
#include "../lib/MLX42/include/MLX42/MLX42.h"
#include <cub3d.h>
#include <textures.h>
#include <map.h>
#include <player.h>
#include <colors.h>
#include "raycast.h"

#define TILE_SIZE 16

typedef struct s_game {
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_arena		*arena;

	t_textures	*textures;
	t_color		floor;
	t_color		ceiling;
	t_map		*map;
	t_player	*player;
	int			number_of_rays;
    double	jump_offset;
	double	jump_time;
	bool	is_jumping;
}	t_game;

#endif
