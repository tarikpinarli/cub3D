/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:35:46 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/26 21:40:09 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# define DIR_NORTH 3 * M_PI_2
# define DIR_SOUTH M_PI_2
# define DIR_EAST 0
# define DIR_WEST M_PI

typedef struct s_player
{
	double	x;
	double	y;
	float	dir;

}			t_player;

#endif
