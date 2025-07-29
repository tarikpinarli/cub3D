/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:08:24 by michoi            #+#    #+#             */
/*   Updated: 2025/07/28 15:15:58 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	open_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd("Error", STDERR_FILENO);
		perror(file);
		return (fd);
	}
	return (fd);
}

int	is_empty_line(char *s)
{
	if (!s || !*s)
		return (1);
	while (*s)
	{
		if (!is_space(*s))
			return (0);
		s++;
	}
	return (1);
}

int	process_metadata(char **metadata)
{
	if (!metadata || !*metadata || !**metadata)
	{
		print_error_messages("Identifier is lacking information");
		return (1);
	}
	*metadata += 2;
	while (is_space(**metadata))
		(*metadata)++;
	return (0);
}

/**
 * Print an error message with the custom message.
 *
 * In subject: If any misconfiguration of any kind is encountered in the file,
 * the program must exit properly and return "Error\n"
 * followed by an explicit error message of your choice.
 */
void	print_error_messages(char *message)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
}
