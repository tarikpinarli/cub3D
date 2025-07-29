/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:35:46 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/28 19:49:53 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

typedef struct s_dirs
{
	float	north;
	float	south;
	float	east;
	float	west;
}			t_dirs;

typedef struct s_player
{
	double	x;
	double	y;
	float	dir;
}			t_player;

#endif
