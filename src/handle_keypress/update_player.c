/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 13:44:38 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/26 13:48:00 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	is_walkable(t_map *map, double x, double y)
{
	return (
		map->grid[(int)(y)][(int)(x)] != '1' &&
		map->grid[(int)(y + COLLISION_MARGIN)][(int)(x)] != '1' &&
		map->grid[(int)(y - COLLISION_MARGIN)][(int)(x)] != '1' &&
		map->grid[(int)(y)][(int)(x + COLLISION_MARGIN)] != '1' &&
		map->grid[(int)(y)][(int)(x - COLLISION_MARGIN)] != '1'
	);
}

void	slide_move(t_game *game, t_move *move)
{
	move->target_x = game->player->x + move->offset_x;
	move->target_y = game->player->y + move->offset_y;
	move->can_move_x = is_walkable(game->map, move->target_x, game->player->y);
	move->can_move_y = is_walkable(game->map, game->player->x, move->target_y);
	if (move->can_move_x && move->can_move_y)
	{
		game->player->x = move->target_x;
		game->player->y = move->target_y;
	}
	else if (move->can_move_x)
		game->player->x = move->target_x;
	else if (move->can_move_y)
		game->player->y = move->target_y;
}

void	update_player(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_forward(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_backward(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_left(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_right(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_left(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_right(game);
}
