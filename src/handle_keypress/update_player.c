/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dummy_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 13:44:38 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/09 15:33:44 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

#define MOVE_SPEED 0.035
#define ROT_SPEED 0.025

void	move_forward(t_game *game)
{
	double next_x;
	double next_y;

	next_x = game->player->x + cos(game->player->dir) * MOVE_SPEED;
	next_y = game->player->y + sin(game->player->dir) * MOVE_SPEED;
	if (game->map->grid[(int)next_y][(int)next_x] != '1')
	{
		game->player->x = next_x;
		game->player->y = next_y;
	}
}

void	move_backward(t_game *game)
{
	double next_x;
	double next_y;

	next_x = game->player->x - cos(game->player->dir) * MOVE_SPEED;
	next_y = game->player->y - sin(game->player->dir) * MOVE_SPEED;
	if (game->map->grid[(int)next_y][(int)next_x] != '1')
	{
		game->player->x = next_x;
		game->player->y = next_y;
	}
}

void	rotate_left(t_game *game)
{
	t_player *p;

	p = game->player;
	p->dir = p->dir - ROT_SPEED;
	if (p->dir < 0)
		p->dir = p->dir + (2 * M_PI);
}

void	rotate_right(t_game *game)
{
	t_player *p;

	p = game->player;
	p->dir = p->dir + ROT_SPEED;
	if (p->dir >= (2 * M_PI))
		p->dir = p->dir - (2 * M_PI);
}

void	update_player(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_forward(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_backward(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		rotate_left(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		rotate_right(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_SPACE) && !game->is_jumping)
		game->is_jumping = true;
}
