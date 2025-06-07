/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:02:05 by yufli             #+#    #+#             */
/*   Updated: 2025/06/07 18:45:28 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/* 渲染单个图块 */
static void	render_tile(t_game *game, void *img, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, img,
		x * TILE_SIZE, y * TILE_SIZE);
}

/* 渲染地图 */
static void	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			render_tile(game, game->img_floor.img, x, y);
			if (game->map.grid[y][x] == WALL)
				render_tile(game, game->img_wall.img, x, y);
			else if (game->map.grid[y][x] == COLLECTIBLE)
				render_tile(game, game->img_collectible.img, x, y);
			else if (game->map.grid[y][x] == EXIT)
				render_tile(game, game->img_exit.img, x, y);
			else if (game->map.grid[y][x] == PLAYER)
				render_tile(game, game->img_player.img, x, y);
			x++;
		}
		y++;
	}
}

/* 渲染移动次数 */
void	render_moves(t_game *game)
{
	char	*temp;
	char	*moves_str;

	temp = ft_itoa(game->moves);
	moves_str = ft_strjoin("Moves: ", temp);
	free(temp);
	mlx_string_put(game->mlx, game->win, 10, 20, 0xFFFFFF, moves_str);
	free(moves_str);
	ft_printf("Moves: %d\n", game->moves);
}

/* 渲染整个游戏 */
void	render_game(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	render_map(game);
	render_moves(game);
}
