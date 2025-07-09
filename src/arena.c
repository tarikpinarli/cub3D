/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:46:22 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/09 15:09:07 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_arena(t_game *game)
{
	game->arena = arena_init(100000);
	if (!game->arena)
		error_exit("Arena allocation failed", NULL);
}
char *arena_strdup(t_arena *arena, const char *s)
{
	size_t	len;
	char	*dup;

	len = ft_strlen(s) + 1;
	dup = arena_alloc(arena, len);
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s, len);
	return (dup);
}


t_arena *arena_init(size_t size)
{
    t_arena *arena;

    arena = malloc(sizeof(t_arena));
    if (!arena)
        return NULL;
    arena->memory = malloc(size);
    if (!arena->memory)
    {
        free(arena);
        return NULL;
    }
    arena->size = size;
    arena->offset = 0;
    return (arena);
}

void *arena_alloc(t_arena *arena, size_t size)
{
    void *ptr;

    if (arena->offset + size > arena->size)
        return NULL;
    ptr = (char *)arena->memory + arena->offset;
    arena->offset += size;
    return (ptr);
}

void arena_destroy(t_arena *arena)
{
    if (!arena)
        return;
    free(arena->memory);
    free(arena);
}
