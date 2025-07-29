/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:56:33 by michoi            #+#    #+#             */
/*   Updated: 2025/07/29 14:57:20 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

/**
 * Get the length of a char array
 */
int	arrlen(char **arr)
{
	int	len;

	if (!arr || !*arr)
		return (0);
	len = 0;
	while (arr[len])
		len++;
	return (len);
}

/**
 * Get an index of a specific character from a string
 */
int	get_idx(char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	is_digit(char c)
{
	return ((c >= '0') && (c <= '9'));
}

int	is_numeric(char *arg)
{
	if (!arg || !*arg)
		return (0);
	while (is_space(*arg))
		arg++;
	if (*arg == '-' || *arg == '+')
	{
		if (!is_digit(*(arg + 1)))
			return (0);
		arg++;
	}
	while (*arg)
	{
		if (!is_digit(*arg))
			return (0);
		arg++;
	}
	return (1);
}
