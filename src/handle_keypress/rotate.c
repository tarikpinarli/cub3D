/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 13:45:48 by michoi            #+#    #+#             */
/*   Updated: 2025/07/30 15:52:58 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	rotate_left(t_game *game)
{
	t_player	*p;
	double		margin;

	margin = game->number_of_rays / 1000;
	p = game->player;
	p->dir = p->dir - (ROT_SPEED * margin);
	if (p->dir < 0)
		p->dir = p->dir + (2 * M_PI);
}

void	rotate_right(t_game *game)
{
	t_player	*p;
	double		margin;

	margin = game->number_of_rays / 1000;
	p = game->player;
	p->dir = p->dir + (ROT_SPEED * margin);
	if (p->dir >= (2 * M_PI))
		p->dir = p->dir - (2 * M_PI);
}
