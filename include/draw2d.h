/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:30:17 by michoi            #+#    #+#             */
/*   Updated: 2025/07/29 12:06:13 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW2D_H
# define DRAW2D_H

# include <cub3d.h>

typedef struct s_draw2d
{
	int			map_offset_x;
	int			map_offset_y;

	int			map_x;
	int			map_y;
	int			tile_px;
	int			tile_py;

	int			screen_x;
	int			screen_y;

	char		tile_char;
	uint32_t	tile_color;

	int			player_screen_x;
	int			player_screen_y;
}				t_draw2d;

#endif
