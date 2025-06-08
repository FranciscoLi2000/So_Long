/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 11:12:47 by yufli             #+#    #+#             */
/*   Updated: 2025/06/09 00:48:54 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		error_exit("mlx_init failed");
	game->win = mlx_new_window(
			game->mlx,
			game->map.width * TILE_SIZE,
			game->map.height * TILE_SIZE,
			"Jackie Chan Escape From the British Museum");
	if (!game->win)
		error_exit("mlx_new_window failed");
}

void	load_images(t_game *game)
{
	int	size;

	size = TILE_SIZE;
	game->img_wall = mlx_xpm_file_to_image(game->mlx,
			"textures/wall.xpm", &size, &size);
	game->img_floor = mlx_xpm_file_to_image(game->mlx,
			"textures/floor.xpm", &size, &size);
	game->img_player = mlx_xpm_file_to_image(game->mlx,
			"textures/player.xpm", &size, &size);
	game->img_exit = mlx_xpm_file_to_image(game->mlx,
			"textures/exit.xpm", &size, &size);
	game->img_collect = mlx_xpm_file_to_image(game->mlx,
			"textures/collectible.xpm", &size, &size);
	if (!game->img_wall || !game->img_floor || !game->img_player
		|| !game->img_exit || !game->img_collect)
		error_exit("Failed to load some XPM images.");
}

void	init_game(t_game *game)
{
	init_window(game);
	load_images(game);
	game->moves = 0;
}
