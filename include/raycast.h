/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:03:13 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/30 16:10:44 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# define NUM_RAYS 800

typedef struct s_ray_hit
{
	double	distance;
	int		wall_dir;
}			t_ray_hit;

// 1 = WEST, 2 = EAST, 3 = NORTH, 4 = SOUTH
typedef enum e_wall_dir
{
	NORTH_WALL,
	SOUTH_WALL,
	EAST_WALL,
	WEST_WALL
}			t_wall_dir;

typedef struct s_raycast
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
	int		side;
}			t_raycast;

#endif
