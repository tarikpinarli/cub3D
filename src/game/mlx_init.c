
#include <cub3d.h>

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init(800, 600, "cub3d", true);
	if (!game->mlx)
		error_exit("MLX initialization failed", game);
}
void	render(void *param)
{
	t_game *game;

	game = (t_game *)param;
	update_player(game);
	if (game->image)
		mlx_delete_image(game->mlx, game->image);
	game->image = mlx_new_image(game->mlx, 800, 600);


	/*if (game->is_jumping)
	{
		game->jump_time += 0.03;
		game->jump_offset = sin(game->jump_time * M_PI) * -0.3;
		if (game->jump_time >= 1.0)
		{
			game->jump_offset = 0;
			game->jump_time = 0;
			game->is_jumping = false;
		}
	}
	else
		game->jump_offset = 0;*/
	draw_3d(game);
	//draw_map(game);
	mlx_image_to_window(game->mlx, game->image, 0, 0);
}