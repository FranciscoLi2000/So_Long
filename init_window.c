/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 11:12:47 by yufli             #+#    #+#             */
/*   Updated: 2025/08/29 09:52:03 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		error_exit("mlx_init failed\n");
	game->win = mlx_new_window(
			game->mlx,
			game->map.width * TILE_SIZE,
			game->map.height * TILE_SIZE,
			"Jackie Chan Escape From the British Museum");
	if (!game->win)
		error_exit("mlx_new_window failed\n");
}
