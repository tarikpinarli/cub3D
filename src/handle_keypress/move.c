/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 15:11:06 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/30 16:09:14 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	move_forward(t_game *game)
{
	t_move	move;
	double	margin;

	margin = game->number_of_rays / 150;
	move.offset_x = cos(game->player->dir) * (MOVE_SPEED * margin);
	move.offset_y = sin(game->player->dir) * (MOVE_SPEED * margin);
	slide_move(game, &move);
}

void	move_backward(t_game *game)
{
	t_move	move;
	double	margin;

	margin = game->number_of_rays / 150;
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
