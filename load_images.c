/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 11:12:47 by yufli             #+#    #+#             */
/*   Updated: 2025/08/29 09:51:21 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
		error_exit("Failed to load some XPM images.\n");
}
