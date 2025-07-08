/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:43:21 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/08 19:37:02 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "arena.h"
#include "game.h"
#include "../lib/MLX42/include/MLX42/MLX42.h"

void	init_game(t_game *game);
void	handle_keypress(mlx_key_data_t keydata, void *param);
void	error_exit(const char *message, t_game *game);
void	close_window(t_game *game);
#endif
