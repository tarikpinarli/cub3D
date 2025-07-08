#include <cub3d.h>

char **load_dummy_map(t_arena *arena)
{
	const char *lines[] = {
		"1111111111111111111",
		"10W1001001001000001",
		"1011000001000001001",
		"1001001001111101111",
		"1001111000001001001",
		"1000000000000001001",
		"1001111111111001001",
		"1111000000000001011",
		"1000000001000000001",
		"1111111111111111111",
		NULL
	};
	int i = 0;
	char **map;

	while (lines[i])
		i++;
	map = arena_alloc(arena, sizeof(char *) * (i + 1));
	if (!map)
		return NULL;
	for (int j = 0; j < i; j++)
		map[j] = (char *)lines[j];
	map[i] = NULL;
	return map;
}
