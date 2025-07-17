/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:56:33 by michoi            #+#    #+#             */
/*   Updated: 2025/07/17 22:33:55 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/**
 * Print an error message with the custom message.
 *
 * In subject: If any misconfiguration of any kind is encountered in the file,
 * the program must exit properly and return "Error\n"
 * followed by an explicit error message of your choice.
 */
void	print_error_messages(char *messsage)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
}

/**
 * Get the length of a char array
 */
int	arrlen(char **arr)
{
	int len;

	if (!arr || !*arr)
		return (0);
	len = 0;
	while (arr[len])
		len++;
	return (len);
}