/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:00:35 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/26 13:48:33 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	error_exit(char *message, t_game *game)
{
	if (game->arena)
		arena_destroy(game->arena);
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(message, 2);
	exit(EXIT_FAILURE);
}
