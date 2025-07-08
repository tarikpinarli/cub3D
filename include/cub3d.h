/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:43:21 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/08 17:10:17 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "arena.h"
// #include "libft.h"
// #include "colors.h"
// #include "map.h"
// #include "player.h"
// #include "textures.h"
#include "game.h"

#ifdef __APPLE__
# include "../lib/minilibx/mlx.h"
#else
# include "../lib/minilibx-linux/mlx.h"
#endif

void	error_exit(const char *message);
#endif
