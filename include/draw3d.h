/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 13:49:24 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/26 13:52:33 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW3D_H
# define DRAW3D_H

# include <cub3d.h>

typedef struct s_line {
    int         x;
    int         start;
    int         end;
    uint32_t    color;
}   t_line;

typedef struct s_draw3d
{
	double		dir;
	double		start_angle;
	double		angle_step;
	int			ray;
	uint32_t	floor;
	uint32_t	ceiling;

	double		ray_angle;
	t_ray_hit	hit;
	double		corrected_dist;
	double		wall_height;
	int			start;
	int			end;

}				t_draw3d;

#endif
