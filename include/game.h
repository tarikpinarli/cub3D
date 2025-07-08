/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:35:31 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/08 19:46:07 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
#define GAME_H
#include "arena.h"
#include "../lib/MLX42/include/MLX42/MLX42.h"
#include <cub3d.h>

typedef struct s_game {
	mlx_t		*mlx;
	t_arena		*arena;

	// t_textures	*textures;
	// t_color		floor;
	// t_color		ceiling;
	// t_map		*map;
	// t_player	*player;
}	t_game;

#endif
