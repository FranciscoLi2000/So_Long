/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 11:13:48 by yufli             #+#    #+#             */
/*   Updated: 2025/06/08 18:21:55 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* 渲染场景 */

/* 将地图转化为图像元素渲染 */

/* 每次玩家移动后刷新画面 */

static void	put_tile(t_game *g, void *img, int x, int y)
{
	mlx_put_image_to_window(g->mlx, g->win, img,
		x * TILE_SIZE, y * TILE_SIZE);
}

void	render_map(t_game *g)
{
	int		x;
	int		y;
	char	tile;

	y = 0;
	while (y < g->map.height)
	{
		x = 0;
		while (x < g->map.width)
		{
			tile = g->map.grid[y][x];
			put_tile(g, g->img_floor, x, y);
			if (tile == WALL)
				put_tile(g, g->img_wall, x, y);
			else if (tile == PLAYER)
				put_tile(g, g->img_player, x, y);
			else if (tile == COLLECTIBLE)
				put_tile(g, g->img_collect, x, y);
			else if (tile == EXIT)
				put_tile(g, g->img_exit, x, y);
			x++;
		}
		y++;
	}
}
