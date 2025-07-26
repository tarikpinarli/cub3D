/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:35:54 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/26 13:46:58 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_H
# define TEXTURES_H
# include <cub3d.h>

typedef struct s_textures
{
	char			*north_path;
	char			*south_path;
	char			*west_path;
	char			*east_path;
	mlx_texture_t	*north_png;
	mlx_texture_t	*south_png;
	mlx_texture_t	*west_png;
	mlx_texture_t	*east_png;
}					t_textures;

#endif
