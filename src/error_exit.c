/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:00:35 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/07 16:03:16 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	error_exit(const char *message)
{
	printf("Error: %s.\n", message);
	exit(EXIT_FAILURE);
}
