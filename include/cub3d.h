/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:43:21 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/30 13:55:59 by michoi           ###   ########.fr       */
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

void		init_arena(t_game *game);
void		handle_keypress(mlx_key_data_t keydata, void *param);
void		update_player(t_game *game);
void		error_exit(char *message, t_game *game);
void		close_window(t_game *game);
void		draw_map(t_game *game);
void		draw_3d(t_game *game);
void		render(void *param);
void		init_mlx(t_game *game);
t_ray_hit	cast_ray(t_game *game, double ray_angle);
void		draw_texture_stripe(t_game *game, t_draw3d *d);
uint32_t	get_pixel_color(mlx_texture_t *tex, int tex_x, int tex_y,
				double distance);
void		move_forward(t_game *game);
void		move_backward(t_game *game);
void		move_left(t_game *game);
void		move_right(t_game *game);
void		rotate_left(t_game *game);
void		rotate_right(t_game *game);
void		slide_move(t_game *game, t_move *move);
void		load_textures(t_game *game);
void		free_textures(t_textures *tex);

#endif
