/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:50:02 by michoi            #+#    #+#             */
/*   Updated: 2025/07/14 14:56:51 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	check_args(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr_fd("Invalid argument(s). Put one texture file.\n",
			STDERR_FILENO);
		return (1);
	}
	if (ft_strrncmp(argv[1], MAP_EXTENSION, ft_strlen(MAP_EXTENSION)))
	{
		ft_putstr_fd("Invalid file extension. Use '*.cub' file.\n",
			STDERR_FILENO);
		return (1);
	}
	return (0);
}
