/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 13:44:38 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/26 13:48:00 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

#define MOVE_SPEED 0.035
#define ROT_SPEED 0.020
#define HOR_MOVE 0.019

void	move_forward(t_game *game)
{
	double	next_x;
	double	next_y;

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
	double	next_x;
	double	next_y;

	next_x = game->player->x - cos(game->player->dir) * MOVE_SPEED;
	next_y = game->player->y - sin(game->player->dir) * MOVE_SPEED;
	if (game->map->grid[(int)next_y][(int)next_x] != '1')
	{
		game->player->x = next_x;
		game->player->y = next_y;
	}
}

void	move_left(t_game *game)
{
	double	dir;
	double	next_x;
	double	next_y;

	dir = game->player->dir;
	next_x = game->player->x + sin(dir) * HOR_MOVE;
	next_y = game->player->y - cos(dir) * HOR_MOVE;
	if (game->map->grid[(int)next_y][(int)next_x] != '1')
	{
		game->player->x = next_x;
		game->player->y = next_y;
	}
}

void	move_right(t_game *game)
{
	double	dir;
	double	next_x;
	double	next_y;

	dir = game->player->dir;
	next_x = game->player->x - sin(dir) * HOR_MOVE;
	next_y = game->player->y + cos(dir) * HOR_MOVE;
	if (game->map->grid[(int)next_y][(int)next_x] != '1')
	{
		game->player->x = next_x;
		game->player->y = next_y;
	}
}

void	rotate_left(t_game *game)
{
	t_player	*p;

	p = game->player;
	p->dir = p->dir - ROT_SPEED;
	if (p->dir < 0)
		p->dir = p->dir + (2 * M_PI);
}

void	rotate_right(t_game *game)
{
	t_player	*p;

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
		move_left(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_right(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_left(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_right(game);
}
