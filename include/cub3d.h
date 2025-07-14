/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:43:21 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/14 15:00:43 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// FOR PARSING
# define MAP_EXTENSION ".cub"
# define NO "NO"
# define SO "SO"
# define WE "WE"
# define EA "EA"
# define F "F"
# define C "C"

# include "arena.h"
# include "libft.h"

// FOR PARSING
int		check_args(int argc, char **argv);
int		get_rgb_color(char **metadata);
int		get_wall_texture(char **metatdata);
int		arrlen(char **arr);
void	print_error_messages(char **messsage);

void	error_exit(const char *message);
#endif
