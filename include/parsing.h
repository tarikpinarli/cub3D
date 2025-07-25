/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 21:04:36 by michoi            #+#    #+#             */
/*   Updated: 2025/07/25 18:12:15 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <cub3d.h>

# define MAP_EXTENSION ".cub"
# define NO "NO "
# define SO "SO "
# define WE "WE "
# define EA "EA "
# define F "F "
# define C "C "
# define BUFFER_SIZE 100

int		check_args(int argc, char **argv);
int		get_rgb_color(t_game *game, char *metadata);
int		get_wall_texture(t_game *game, char *metadata);
int		arrlen(char **arr);
void	print_error_messages(char *message);
int		get_idx(char *s, char c);
char	*get_line(t_game *game, int fd);
int		parse_map(t_game *game, int argc, char **argv);
int		open_file(char *file);
int		is_space(char c);
int		process_metadata(char **metadata);
int		is_digit(char c);
int		is_numeric(char *arg);
int		is_in_rgb_range(int i);
int		validate_map(t_game *game, char *line);
int		get_map(t_game *game, char *file, int start_line);
int		set_player_position(char **map, t_player *player);
int		check_wall(t_map *m);
#endif