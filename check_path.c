#include "so_long.h"

int	check_path(t_map map)
{
	t_ff_input	in;
	int			coins;
	int			found_exit;

	coins = map.collectibles;
	found_exit = 0;
	in.map = duplicate_map(map.grid);	/* 深拷贝地图，避免污染 */
	in.size.x = map.width;
	in.size.y = map.height;
	in.start.x = map.player_x;
	in.start.y = map.player_y;
	in.coins = &coins;
	in.found_exit = &found_exit;
	flood_fill(&in, in.start.x, in.start.y);
	free_map_copy(in.map);
	return (coins == 0 && found_exit == 1);
}
