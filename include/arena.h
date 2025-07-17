/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:20:00 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/17 21:10:01 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_H
# define ARENA_H

# include <cub3d.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_arena
{
	void	*memory;
	size_t	size;
	size_t	offset;
}			t_arena;

t_arena		*arena_init(size_t size);
void		*arena_alloc(t_arena *arena, size_t size);
void		arena_destroy(t_arena *arena);
char		*arena_strdup(t_arena *arena, const char *s);
#endif
