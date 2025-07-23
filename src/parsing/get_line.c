/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:07:55 by michoi            #+#    #+#             */
/*   Updated: 2025/07/23 15:36:27 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

char	*get_line_strjoin(t_game *game, char *s1, char *s2)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = arena_alloc(game->arena, ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	if (s1)
	{
		while (s1[i])
		{
			new_str[i] = s1[i];
			i++;
		}
	}
	j = 0;
	if (s2)
	{
		while (s2[j])
			new_str[i++] = s2[j++];
	}
	new_str[i] = 0;
	return (new_str);
}

static char	*initialize_line(t_game *game, char buffer[])
{
	size_t	buffer_len;
	char	*line;

	buffer_len = ft_strlen(buffer);
	line = arena_alloc(game->arena, buffer_len + 1);
	if (!line)
	{
		print_error_messages("spare line initialization failed");
		return (NULL);
	}
	ft_memset(line, 0, buffer_len + 1);
	if (buffer_len)
		ft_strlcpy(line, buffer, buffer_len + 1);
	return (line);
}

static char	*read_line(t_game *game, int fd, char buffer[])
{
	char	*line;
	ssize_t	read_bytes;

	line = initialize_line(game, buffer);
	if (!line)
		return (NULL);
	if (get_idx(line, '\n') != -1)
		return (line);
	while (1)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes <= 0)
			return (NULL);
		buffer[read_bytes] = 0;
		line = get_line_strjoin(game, line, buffer);
		if (!line)
		{
			print_error_messages("strjoin failed");
			break ;
		}
		else if (get_idx(line, '\n') != -1)
			break ;
	}
	return (line);
}

static char	*extract_line(t_game *game, char *read_content,
		char buffer[])
{
	int		i;
	char	*complete_line;

	if (!read_content || !*read_content)
		return (NULL);
	i = get_idx(read_content, '\n');
	if (i == -1)
		return (NULL);
	complete_line = arena_substr(game->arena, read_content, 0, i);
	if (!complete_line)
	{
		print_error_messages("substring genaration failed");
		return (NULL);
	}
	ft_strlcpy(buffer, (read_content + i + 1), ft_strlen(read_content + i + 1)
		+ 1);
	return (complete_line);
}

char	*get_line(t_game *game, int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*read_content;
	char		*line_with_nl;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_content = read_line(game, fd, buffer);
	if (!read_content)
		return (NULL);
	if (get_idx(read_content, '\n') == -1)
		return (read_content);
	line_with_nl = extract_line(game, read_content, buffer);
	return (line_with_nl);
}
