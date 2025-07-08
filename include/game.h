/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:35:31 by tpinarli          #+#    #+#             */
/*   Updated: 2025/07/08 15:35:33 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
#define GAME_H
# include "arena.h"
# include "textures.h"
# include "colors.h"
# include "map.h"
# include "player.h"

typedef struct s_game {
	void		*mlx;
	void		*win;
	t_arena		*arena;

	t_textures	*textures;
	t_color		floor;
	t_color		ceiling;
	t_map		*map;
	t_player	*player;
}	t_game;

void	init_game(t_game *game);
#endif
