/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:23:17 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/08 17:19:54 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_game(t_game *game)
{
	char *str;

	game->arena = arena_init(100000);
	str = arena_alloc(game->arena, 200);
}
