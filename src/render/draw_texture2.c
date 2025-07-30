/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 13:52:39 by michoi            #+#    #+#             */
/*   Updated: 2025/07/30 13:56:02 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

uint32_t	get_pixel_color(mlx_texture_t *tex, int tex_x, int tex_y,
		double distance)
{
	t_pixel_color	color;
	int				index;
	uint8_t			*pixels;
	double			shade;

	shade = 1.0 / (1.0 + distance * 0.2);
	if (shade > 1.0)
		shade = 1.0;
	if (shade < 0.1)
		shade = 0.1;
	index = (tex_y * tex->width + tex_x) * 4;
	pixels = (uint8_t *)tex->pixels;
	color.r = (uint8_t)(pixels[index + 0] * shade);
	color.g = (uint8_t)(pixels[index + 1] * shade);
	color.b = (uint8_t)(pixels[index + 2] * shade);
	color.a = pixels[index + 3];
	return ((color.r << 24) | (color.g << 16) | (color.b << 8) | color.a);
}
