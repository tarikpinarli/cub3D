/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:01:38 by michoi            #+#    #+#             */
/*   Updated: 2025/07/30 14:07:27 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	count_words(char const *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if ((*s != c) && !in_word)
		{
			count++;
			in_word = 1;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*allocate_word(t_arena *arena, int start, int end, char const *s)
{
	char	*word;
	int		i;

	word = arena_alloc(arena, end - start + 1);
	if (!word)
		return (0);
	i = 0;
	while (start < end)
		word[i++] = s[start++];
	word[i] = 0;
	return (word);
}

static char	**add_words(t_arena *arena, char **arr, char const *s, char c)
{
	int	start;
	int	end;
	int	i;

	i = 0;
	start = 0;
	while (s[start])
	{
		if (s[start] != c)
		{
			end = start;
			while (s[end] != c && s[end])
				end++;
			arr[i] = allocate_word(arena, start, end, s);
			if (!arr[i])
				return (NULL);
			i++;
			start = end;
		}
		else
			start++;
	}
	arr[i] = 0;
	return (arr);
}

char	**arena_split(t_arena *arena, char const *s, char c)
{
	char	**result;

	if (!s)
		return (0);
	result = arena_alloc(arena, sizeof(*result) * (count_words(s, c) + 1));
	if (!result)
		return (NULL);
	result = add_words(arena, result, s, c);
	if (!result)
		return (NULL);
	return (result);
}
