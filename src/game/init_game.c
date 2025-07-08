// init_game.c
#include <cub3d.h>

void	init_game(t_game *game)
{
	game->arena = arena_init(100000); // Geniş bir alan
	if (!game->arena)
		error_exit("Arena init failed");

	// Pencere
	game->mlx = mlx_init();
	if (!game->mlx)
		error_exit("mlx_init failed");

	game->win = mlx_new_window(game->mlx, 800, 600, "cub3D");
	if (!game->win)
		error_exit("mlx_new_window failed");

	// Textures
	game->textures = arena_alloc(game->arena, sizeof(t_textures));
	game->textures->north = "textures/simonkraft/cobblestone.xpm";
	game->textures->south = "textures/simonkraft/cobblestone_01.xpm";
	game->textures->west = "textures/simonkraft/mossy_cobblestone1.xpm";
	game->textures->east = "textures/simonkraft/cobblestone_02.xpm";

	// Floor & Ceiling Colors
	game->floor = (t_color){76, 76, 76};
	game->ceiling = (t_color){99, 99, 99};

	// Map
	game->map = arena_alloc(game->arena, sizeof(t_map));
	game->map->grid = load_dummy_map(game->arena);
	game->map->height = 10;
	game->map->width = ft_strlen(game->map->grid[0]);

	// Player
	game->player = arena_alloc(game->arena, sizeof(t_player));
	game->player->x = 3.5;
	game->player->y = 1.5;
	game->player->dir = WEST;
}
