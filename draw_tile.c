#include "so_long.h"

void	draw_tile(t_game *g, int x, int y, char tile)
{
	void	*img;

	if (tile == WALL)
		img = g->img_wall;
	else if (tile == PLAYER)
		img = g->img_player;
	else if (tile == COLLECTIBLE)
		img = g->img_collect;
	else if (tile == EXIT)
		img = g->img_exit;
	else
		img = g->img_floor;
	mlx_put_image_to_window(g->mlx, g->win, img, x * TILE_SIZE, y * TILE_SIZE);
}
