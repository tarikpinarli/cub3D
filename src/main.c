/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:19:49 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/07 16:33:23 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	set_arena(t_arena **arena)
{
	*arena = arena_init(10000);
	if (!*arena)
		error_exit("Arena allocation failed.");
}

int	main()
{
	t_arena	*arena;

	set_arena(&arena);
	arena_destroy(arena);
	return (0);
}
