#ifndef DRAW2D_H
# define DRAW2D_H

# include <cub3d.h>

typedef struct s_draw2d
{
	int	map_offset_x;       // Where the minimap starts on the screen (X)
	int	map_offset_y;       // Where the minimap starts on the screen (Y)

	int	map_x;              // Tile X coordinate in the map grid
	int	map_y;              // Tile Y coordinate in the map grid
	int	tile_px;            // Pixel offset within the tile (0 to TILE_SIZE)
	int	tile_py;

	int	screen_x;           // Final X coordinate on the screen
	int	screen_y;           // Final Y coordinate on the screen

	char	tile_char;         // The character in the map grid ('1', '0', etc.)
	uint32_t	tile_color;     // Color to draw the tile

	int	player_screen_x;    // Player's X position on the minimap
	int	player_screen_y;    // Player's Y position on the minimap
}	t_draw2d;

#endif
