/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:43:21 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/09 14:42:25 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "arena.h"
#include "game.h"
#include <math.h>
#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "../lib/libft/libft.h"

void	init_arena(t_game *game);
void	handle_keypress(mlx_key_data_t keydata, void *param);
void	update_player(t_game *game);
void	error_exit(char *message, t_game *game);
void	close_window(t_game *game);
int 	init_dummy_data(t_game *game);
void	draw_map(t_game *game);
void    draw_3d(t_game *game);
void	render(void *param);
void	load_textures(t_game *game);
#endif
