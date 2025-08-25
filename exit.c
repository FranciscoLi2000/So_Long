#include "so_long.h"

int	handle_exit(void *param)
{
	t_game	*g;

	g = (t_game *)param;
	mlx_destroy_window(g->mlx, g->win);
	free_map_copy(g->map.grid);
	exit(0);
}
