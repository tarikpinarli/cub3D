/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:05:17 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/29 12:19:20 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVE_H
# define MOVE_H

# define MOVE_SPEED 0.035
# define ROT_SPEED 0.040
# define HOR_MOVE 0.019
# define COLLISION_MARGIN 0.05

typedef struct s_move
{
	double	offset_x;
	double	offset_y;
	double	target_x;
	double	target_y;
	bool	can_move_x;
	bool	can_move_y;
}			t_move;

#endif
