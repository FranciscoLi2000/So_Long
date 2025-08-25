#include "so_long.h"

void	init_game(t_game *g)
{
	g->mlx = mlx_init();
	if (!g->mlx)
		error_exit("MLX init failed.");
	g->win = mlx_new_window(g->mlx, g->map.width * TILE_SIZE,
	g->map.height * TILE_SIZE, "so_long");
	g->img_wall = mlx_xpm_file_to_image(g->mlx, "assets/wall.xpm", &(int){0}, &(int){0});
	g->img_floor = mlx_xpm_file_to_image(g->mlx, "assets/floor.xpm", &(int){0}, &(int){0});
	g->img_player = mlx_xpm_file_to_image(g->mlx, "assets/player.xpm", &(int){0}, &(int){0});
	g->img_collect = mlx_xpm_file_to_image(g->mlx, "assets/collect.xpm", &(int){0}, &(int){0});
	g->img_exit = mlx_xpm_file_to_image(g->mlx, "assets/exit.xpm", &(int){0}, &(int){0});
	g->moves = 0;
	g->win_status = 0;
}
