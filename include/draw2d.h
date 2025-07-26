/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:30:17 by michoi            #+#    #+#             */
/*   Updated: 2025/07/26 21:30:18 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW2D_H
# define DRAW2D_H

# include <cub3d.h>

typedef struct s_draw2d
{
	int			offset_x;
	int			offset_y;

	int			x;
	int			y;
	int			dx;
	int			dy;

	int			px;
	int			py;

	char		c;
	uint32_t	color;

	int			player_px;
	int			player_py;
}				t_draw2d;

#endif
