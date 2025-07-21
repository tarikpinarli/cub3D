/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_substr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 12:34:28 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/21 12:38:28 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

char	*arena_substr(t_arena *arena, const char *s,
		unsigned int start, size_t len)
{
	size_t	i;
	size_t	len1;
	size_t	s_len;
	char	*res;

	if (!s || !arena)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		len1 = 0;
	else if (len > s_len - start)
		len1 = s_len - start;
	else
		len1 = len;
	res = (char *)arena_alloc(arena, (len1 + 1) * sizeof(char));
	if (!res)
		return (NULL); // Arena allocatiion fail.
	i = 0;
	while (i < len1)
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

