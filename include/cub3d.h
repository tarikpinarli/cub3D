/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:43:21 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/22 21:06:10 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"
# include "arena.h"
# include "game.h"
# include "parsing.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

void	init_arena(t_game *game);
void	handle_keypress(mlx_key_data_t keydata, void *param);
void	update_player(t_game *game);
void	error_exit(char *message, t_game *game);
void	close_window(t_game *game);
int		init_dummy_data(t_game *game);
void	draw_map(t_game *game);
void	draw_3d(t_game *game);
void	render(void *param);
void	init_mlx(t_game *game);

#endif
