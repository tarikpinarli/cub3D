/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 13:45:48 by michoi            #+#    #+#             */
/*   Updated: 2025/07/30 13:50:17 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
