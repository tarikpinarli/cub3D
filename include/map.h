/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:35:39 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/08 15:35:41 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
#define MAP_H
#include <cub3d.h>

typedef struct s_map {
	char	**grid;
	int		width;
	int		height;
}	t_map;

char	**load_dummy_map(t_arena *arena);
#endif
