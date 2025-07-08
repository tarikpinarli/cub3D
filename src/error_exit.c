/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:00:35 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/08 19:27:55 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	error_exit(const char *message, t_game *game)
{
	(void)game;
	printf("Error: %s.\n", message);
	exit(EXIT_FAILURE);
}
