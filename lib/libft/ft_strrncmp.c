/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrncmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:22:54 by michoi            #+#    #+#             */
/*   Updated: 2025/07/07 20:26:20 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define FT_STRRNMP_ERROR -9999

/**
 * Compare the last n characters of two strings from the end.
 * @param s1: first string
 * @param s2: second string
 * @param n: amount of the characters to be compared
 */
int	ft_strrncmp(char *s1, char *s2, int n)
{
	int	i1;
	int	i2;
	int	c_count;

	if (!s1 || !s2 || n <= 0)
		return (FT_STRRNMP_ERROR);
	i1 = ft_strlen(s1) - 1;
	i2 = ft_strlen(s2) - 1;
	if (i1 < n - 1 || i2 < n - 1)
		return (FT_STRRNMP_ERROR);
	c_count = 0;
	while (i1 >= 0 && i2 >= 0 && c_count < n)
	{
		if (s1[i1] != s2[i2])
			return ((unsigned char)s1[i1] - (unsigned char)s2[i2]);
		i1--;
		i2--;
		c_count++;
	}
	return (0);
}
