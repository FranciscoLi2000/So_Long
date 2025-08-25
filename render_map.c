#include "so_long.h"

void	render_map(t_game *g)
{
	char	**grid;
	int		y;
	int		x;

	grid = g->map.grid;
	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x])
		{
			draw_tile(g, x, y, grid[y][x]);
			x++;
		}
		y++;
	}
	return ;
}
