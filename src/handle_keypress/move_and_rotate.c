/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_and_rotate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 15:11:06 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/30 15:03:53 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	move_forward(t_game *game)
{
	t_move	move;
	double	margin;

	margin = game->number_of_rays / 100;
	move.offset_x = cos(game->player->dir) * (MOVE_SPEED * margin);
	move.offset_y = sin(game->player->dir) * (MOVE_SPEED * margin);
	slide_move(game, &move);
}

void	move_backward(t_game *game)
{
	t_move	move;
	double	margin;

	margin = game->number_of_rays / 100;
	move.offset_x = -cos(game->player->dir) * (MOVE_SPEED * margin);
	move.offset_y = -sin(game->player->dir) * (MOVE_SPEED * margin);
	slide_move(game, &move);
}


void	move_left(t_game *game)
{
	t_move	move;
	double	margin;

	margin = game->number_of_rays / 200;
	move.offset_x = sin(game->player->dir) * (MOVE_SPEED * margin);
	move.offset_y = -cos(game->player->dir) * (MOVE_SPEED * margin);
	slide_move(game, &move);
}


void	move_right(t_game *game)
{
	t_move	move;
	double	margin;

	margin = game->number_of_rays / 200;
	move.offset_x = -sin(game->player->dir) * (MOVE_SPEED * margin);
	move.offset_y = cos(game->player->dir) * (MOVE_SPEED * margin);
	slide_move(game, &move);
}


void	rotate_left(t_game *game)
{
	t_player	*p;
	float		rot_margin;

	rot_margin = game->number_of_rays / 1000;
	p = game->player;
	p->dir = p->dir - ROT_SPEED * rot_margin;
	if (p->dir < 0)
		p->dir = p->dir + (2 * M_PI);
}

void	rotate_right(t_game *game)
{
	t_player	*p;
	double		rot_margin;

	rot_margin = game->number_of_rays / 1000;
	p = game->player;
	p->dir = p->dir + ROT_SPEED * rot_margin;
	if (p->dir >= (2 * M_PI))
		p->dir = p->dir - (2 * M_PI);
}
