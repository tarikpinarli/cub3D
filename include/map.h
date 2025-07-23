/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:35:39 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/23 21:58:27 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <cub3d.h>

# define N 'N'
# define S 'S'
# define E 'E'
# define W 'W'

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}			t_map;

#endif
