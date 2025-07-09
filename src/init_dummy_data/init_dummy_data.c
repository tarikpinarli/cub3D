/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dummy_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 13:44:38 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/09 15:00:36 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <textures.h>
#include <map.h>
#include <player.h>
#include <colors.h>

static t_map *init_dummy_map(t_game *game)
{
    t_map *map;

	map = arena_alloc(game->arena, sizeof(t_map));
    if (!map)
        error_exit("Failed to allocate dummy map", game);

    static char *grid[] = {
        "111111111111111111111",
        "101000001000000000001",
        "101010101011111110001",
        "100010100010000010001",
        "111110101111101011101",
        "100000101000101000001",
        "101111101011101111111",
        "101000001010100000101",
        "101011111010111110101",
        "101010001010100010101",
        "101110101010101010101",
        "100000101010001010001",
        "111111101011111011101",
        "100000101000100010001",
        "101110101110101110111",
        "101000100000100010101",
        "101011111111111010101",
        "100010000000000010001",
        "101010111011111111101",
        "1N1000001000000000001",
        "111111111111111111111",
    };

    map->grid = grid;
    map->width = 21;
    map->height = 21;
    return (map);
}
static t_textures *init_dummy_textures(t_game *game)
{
    t_textures *textures;

	textures = arena_alloc(game->arena, sizeof(t_textures));
    if (!textures)
	{
		error_exit("Failed to allocate dummy textures", game);
	}
	// You will need to allocate some memory for these pointers here.
	textures->north = arena_strdup(game->arena, "textures/matrix.xpm");
	textures->south = arena_strdup(game->arena, "textures/matrix.xpm");
	textures->west = arena_strdup(game->arena, "textures/matrix.xpm");
	textures->east = arena_strdup(game->arena, "textures/matrix.xpm");
    return (textures);
}

static t_player *init_dummy_player(t_game *game)
{
    t_player *player;

	player = arena_alloc(game->arena, sizeof(t_player));
    if (!player)
        error_exit("Failed to allocate dummy player", game);

    player->x = 1.0; //index in column
    player->y = 19.0; //index in row
    player->dir = NORTH;
    return (player);
}

static void init_dummy_colors(t_color *floor, t_color *ceiling)
{
    floor->r = 0;
    floor->g = 0;
    floor->b = 0;

    ceiling->r = 0;
    ceiling->g = 0;
    ceiling->b = 0;
}

int init_dummy_data(t_game *game)
{
    game->map = init_dummy_map(game);
    game->textures = init_dummy_textures(game);
    game->player = init_dummy_player(game);

    init_dummy_colors(&game->floor, &game->ceiling);
    return 0;
}
