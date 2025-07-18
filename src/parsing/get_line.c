/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:07:55 by michoi            #+#    #+#             */
/*   Updated: 2025/07/18 16:58:51 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

char	*get_line_strjoin(char *s1, char *s2)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	new_str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new_str)
		return (free(s1), (char *)0);
	if (s1)
	{
		while (s1[i])
		{
			new_str[i] = s1[i];
			i++;
		}
		free(s1);
	}
	j = 0;
	if (s2)
	{
		while (s2[j])
			new_str[i++] = s2[j++];
	}
	new_str[i] = '\0';
	return (new_str);
}

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

static char	*initialize_line(t_game *game, char buffer[])
{
	size_t	buffer_len;
	char	*line;

	buffer_len = ft_strlen(buffer);
	line = arena_alloc(game->arena, buffer_len + 1);
	if (!line)
		return (NULL);
	ft_memset(line, 0, buffer_len + 1);
	if (buffer_len)
		ft_strlcpy(line, buffer, buffer_len);
	return (line);
}

static char	*read_line(t_game *game, int fd, char buffer[])
{
	char	*line;
	ssize_t	read_bytes;

	line = initialize_line(buffer);
	if (!line)
		return (NULL);
	if (get_idx(line, '\n') != -1)
		return (line);
	while (1)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes <= 0)
		{	
            // maybe no need when using arena?
			// free(line);
			// line = NULL;
			break ;
		}
		buffer[read_bytes] = '\0';
		line = get_line_strjoin(line, buffer);
		if (!line || get_idx(line, '\n') != -1)
			break ;
	}
	return (line);
}

static char	*extract_line(char **line, char leftover[])
{
	int		i;
	char	*complete_line;

	if ((!line) || (!*line) || (!**line))
		return (NULL);
	i = get_idx(*line, '\n');
	if (i == -1)
	{
		complete_line = ft_substr(*line, 0, ft_strlen(*line));
		if (!complete_line)
			return (free(*line), leftover[0] = '\0', NULL);
		leftover[0] = NULL;
	}
	else
	{
		complete_line = ft_substr(*line, 0, (i + 1));
		if (!complete_line)
			return (free(*line), leftover[0] = '\0', NULL);
		ft_strcpy(leftover, (*line + i + 1));
	}
	free(*line);
	*line = NULL;
	return (complete_line);
}

char	*get_line(t_game *game, int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*read_content;
	char		*complete_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_content = read_line(game, fd, buffer);
	if (!read_content)
		return (NULL);
	complete_line = extract_line(&read_content, buffer);
	return (complete_line);
}
