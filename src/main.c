/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:19:49 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/08 17:18:10 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(void)
{
	t_game	game;

	init_game(&game);
	printf("Arena used: %zu / %zu bytes\n", game.arena->offset, game.arena->size);
	arena_destroy(game.arena);
	return (0);
}

