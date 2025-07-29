/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dummy_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 13:44:38 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/29 10:41:00 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <colors.h>
#include <cub3d.h>
#include <map.h>
#include <player.h>
#include <textures.h>

void	load_textures(t_game *game)
{
	game->textures->north_png = mlx_load_png(game->textures->north_path);
	if (!game->textures->north_png)
		error_exit("Failed to load north texture", game);
	game->textures->south_png = mlx_load_png(game->textures->south_path);
	if (!game->textures->south_png)
		error_exit("Failed to load south texture", game);
	game->textures->east_png = mlx_load_png(game->textures->east_path);
	if (!game->textures->east_png)
		error_exit("Failed to load east texture", game);
	game->textures->west_png = mlx_load_png(game->textures->west_path);
	if (!game->textures->west_png)
		error_exit("Failed to load west texture", game);
}

static t_map	*init_dummy_map(t_game *game)
{
	t_map	*map;

	map = arena_alloc(game->arena, sizeof(t_map));
	if (!map)
		error_exit("Failed to allocate dummy map", game);
	static char *grid[] = {
		"111111111111111111111",
        "1000000000000000000W1",
		"100000000010000000001",
        "100000000000000000001",
		"100000111101110000001",
        "100000100000010000001",
		"100000100000010000001",
        "100000100000010000001",
		"100000111111110000001",
        "100000001010100010101",
		"100000101010101010101",
        "100000101010001010001",
		"100000101011111011101",
        "100000101000100010001",
		"100000101110101110101",
        "100000100000100010101",
		"100000111111111010101",
        "100000000000000010001",
		"100000111011111111101",
        "100000001000000000001",
		"111111111111111111111",
	};
	map->grid = grid;
	map->width = 21;
	map->height = 21;
	return (map);
}
static t_textures	*init_dummy_textures(t_game *game)
{
	t_textures	*textures;

	textures = arena_alloc(game->arena, sizeof(t_textures));
	if (!textures)
		error_exit("Failed to allocate dummy textures", game);
	textures->north_path = arena_strdup(game->arena, "textures/matrix.png");
	if (!textures->north_path)
		error_exit("textures->north initialization failed", game);
	textures->south_path = arena_strdup(game->arena, "textures/matrix.png");
	if (!textures->south_path)
		error_exit("textures->south initialization failed", game);
	textures->west_path = arena_strdup(game->arena, "textures/matrix.png");
	if (!textures->west_path)
		error_exit("textures->west initialization failed", game);
	textures->east_path = arena_strdup(game->arena, "textures/matrix.png");
	if (!textures->east_path)
		error_exit("textures->east initialization failed", game);
	return (textures);
}

static t_player	*init_dummy_player(t_game *game)
{
	t_player	*player;

	player = arena_alloc(game->arena, sizeof(t_player));
	if (!player)
		error_exit("Failed to allocate dummy player", game);
	player->x = 19.5;       // index in column
	player->y = 1.5;        // index in row
	player->dir = game->dirs.west; // N == 270 degree
	return (player);
}

static void	init_dummy_colors(t_color *floor, t_color *ceiling)
{
	floor->r = 0;
	floor->g = 0;
	floor->b = 0;
	ceiling->r = 0;
	ceiling->g = 0;
	ceiling->b = 0;
}

int	init_dummy_data(t_game *game)
{
	game->map = init_dummy_map(game);
	game->textures = init_dummy_textures(game);
	load_textures(game);
	game->player = init_dummy_player(game);
	init_dummy_colors(&game->floor, &game->ceiling);
	return (0);
}
