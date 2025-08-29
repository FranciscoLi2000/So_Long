#include "so_long.h"

static void     free_map(t_game *game)
{
	int	i;
	
	i = 0;
        while (i < game->map.height)
		free(game->map.grid[i++]);
	free(game->map.grid);
	game->map.grid = NULL;
}

void	clean_exit(t_game *game)
{
	if (game->img_wall)
	{
		mlx_destroy_image(game->mlx, game->img_wall);
		game->img_wall = NULL;
	}
	if (game->img_floor)
	{
		mlx_destroy_image(game->mlx, game->img_floor);
		game->img_floor = NULL;
	}
	if (game->img_player)
	{
		mlx_destroy_image(game->mlx, game->img_player);
		game->img_player = NULL;
	}
	if (game->img_exit)
	{
		mlx_destroy_image(game->mlx, game->img_exit);
		game->img_exit = NULL;
	}
	if (game->img_collect)
	{
		mlx_destroy_image(game->mlx, game->img_collect);
		game->img_collect = NULL;
	}
	if (game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		game->mlx = NULL;
	}
	if (game->map.grid)
		free_map(game);
	exit(0);
}
