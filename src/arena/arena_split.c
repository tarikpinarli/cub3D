/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 12:12:21 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/26 13:47:10 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	split_count(char const *s, char c);
static char	**sub_array_size(char const *s, char c, char **ar, int ct,
				t_arena *arena);
static char	**ch_alloc(char const *s, char c, char **array);

char	**arena_split(t_arena *arena, char const *s, char c)
{
	int		count;
	char	**array;

	count = split_count(s, c);
	array = (char **)arena_alloc(arena, (count + 1) * sizeof(char *));
	if (!array)
		return (NULL); // Arena failed, return NULL
	array = sub_array_size(s, c, array, count, arena);
	if (!array)
		return (NULL);
	array = ch_alloc(s, c, array);
	return (array);
}

static char	**sub_array_size(char const *s, char c, char **ar, int ct,
		t_arena *arena)
{
	int	i;
	int	len;

	i = 0;
	while (i < ct)
	{
		while (*s == c && *s != '\0')
			s++;
		len = 0;
		while (*s != c && *s != '\0')
		{
			len++;
			s++;
		}
		ar[i] = (char *)arena_alloc(arena, (len + 1) * sizeof(char));
		if (!ar[i])
			return (NULL); // Arena failed, return NULL
		i++;
	}
	ar[ct] = NULL;
	return (ar);
}

static char	**ch_alloc(char const *s, char c, char **array)
{
	int	i;
	int	k;
	int	j;

	i = 0;
	k = 0;
	j = 0;
	while (array[i] != NULL)
	{
		j = 0;
		while (s[k] == c && s[k] != '\0')
			k++;
		while (s[k] != '\0' && s[k] != c)
		{
			array[i][j] = s[k];
			j++;
			k++;
		}
		array[i][j] = '\0';
		i++;
	}
	return (array);
}

static int	split_count(char const *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	if (s[0] == '\0')
		return (count);
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
			count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}
