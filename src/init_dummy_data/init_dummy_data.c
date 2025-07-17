/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dummy_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 13:44:38 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/16 15:47:08 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <textures.h>
#include <map.h>
#include <player.h>
#include <colors.h>

// void load_textures(t_game *game)
// {
//     // Load texture files
//     game->textures->north_png = mlx_load_png(game->textures->north_path);
//     if (!game->textures->north_png)
//         error_exit("Failed to load north texture", game);

//     game->textures->south_png = mlx_load_png(game->textures->south_path);
//     if (!game->textures->south_png)
//         error_exit("Failed to load south texture", game);

//     game->textures->east_png = mlx_load_png(game->textures->east_path);
//     if (!game->textures->east_png)
//         error_exit("Failed to load east texture", game);

//     game->textures->west_png = mlx_load_png(game->textures->west_path);
//     if (!game->textures->west_png)
//         error_exit("Failed to load west texture", game);

//     // Convert textures to images
//     game->textures->north_img = mlx_texture_to_image(game->mlx, game->textures->north_png);
//     if (!game->textures->north_img)
//         error_exit("Failed to convert north texture to image", game);

//     game->textures->south_img = mlx_texture_to_image(game->mlx, game->textures->south_png);
//     if (!game->textures->south_img)
//         error_exit("Failed to convert south texture to image", game);

//     game->textures->east_img = mlx_texture_to_image(game->mlx, game->textures->east_png);
//     if (!game->textures->east_img)
//         error_exit("Failed to convert east texture to image", game);

//     game->textures->west_img = mlx_texture_to_image(game->mlx, game->textures->west_png);
//     if (!game->textures->west_img)
//         error_exit("Failed to convert west texture to image", game);
// }

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
	textures->north_path = arena_strdup(game->arena, "textures/wall_2.png");
	if (!textures->north_path)
		error_exit("textures->north initialization failed", game);
	textures->south_path = arena_strdup(game->arena, "textures/wall_2.png");
	if (!textures->south_path)
		error_exit("textures->south initialization failed", game);
	textures->west_path = arena_strdup(game->arena, "textures/wall_2.png");
	if (!textures->west_path)
		error_exit("textures->west initialization failed", game);
	textures->east_path = arena_strdup(game->arena, "textures/wall_2.png");
	if (!textures->east_path)
		error_exit("textures->east initialization failed", game);
    return (textures);
}


static t_player *init_dummy_player(t_game *game)
{
    t_player *player;

	player = arena_alloc(game->arena, sizeof(t_player));
    if (!player)
        error_exit("Failed to allocate dummy player", game);

    player->x = 1.5; //index in column
    player->y = 19.5; //index in row
    player->dir = (M_PI / 2); // N == 90 degree
    game->jump_offset = 0;
    game->jump_time = 0;
    game->is_jumping = false;
    return (player);
}

static void init_dummy_colors(t_color *floor, t_color *ceiling)
{
    floor->r = 0;
    floor->g = 0;
    floor->b = 0;

    ceiling->r = 0;
    ceiling->g = 191;
    ceiling->b = 255;
}

int init_dummy_data(t_game *game)
{
    game->map = init_dummy_map(game);
    game->textures = init_dummy_textures(game);
    //load_textures(game);
    game->player = init_dummy_player(game);

    init_dummy_colors(&game->floor, &game->ceiling);
    return 0;
}
