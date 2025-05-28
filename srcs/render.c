/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 02:23:47 by yufli             #+#    #+#             */
/*   Updated: 2025/05/25 02:24:07 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* 渲染单个地图元素 */
static void	render_element(t_game *game, int x, int y)
{
	int	pos_x;
	int	pos_y;

	pos_x = x * IMG_SIZE;
	pos_y = y * IMG_SIZE;
	mlx_put_image_to_window(game->mlx, game->win, game->img_floor.img, pos_x, pos_y);
	if (game->map.grid[y][x] == WALL)
		mlx_put_image_to_window(game->mlx, game->win, game->img_wall.img, pos_x, pos_y);
	else if (game->map.grid[y][x] == COLLECTIBLE)
		mlx_put_image_to_window(game->mlx, game->win, game->img_collectible.img, pos_x, pos_y);
	else if (game->map.grid[y][x] == EXIT)
		mlx_put_image_to_window(game->mlx, game->win, game->img_exit.img, pos_x, pos_y);
	else if (game->map.grid[y][x] == ENEMY)
		mlx_put_image_to_window(game->mlx, game->win, game->img_enemy.img, pos_x, pos_y);
}

/* 渲染地图 */
void	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			render_element(game, x, y);
			x++;
		}
		y++;
	}
}

/* 渲染玩家 */
void	render_player(t_game *game)
{
	int	pos_x;
	int	pos_y;

	pos_x = game->map.player_pos.x * IMG_SIZE;
	pos_y = game->map.player_pos.y * IMG_SIZE;
	mlx_put_image_to_window(game->mlx, game->win, game->img_player.img, pos_x, pos_y);
}

/* 渲染UI（移动次数信息）*/
void	render_ui(t_game *game)
{
	char	moves_str[50];
	char	collectibles_str[50];

	ft_printf("Moves: %d", game->moves);
	mlx_string_put(game->mlx, game->win, 10, 20, 0xFFFFFF, moves_str);
	ft_printf("Treasures: %d/%d", game->collected, game->map.collectibles);
	mlx_string_put(game->mlx, game->win, 10, 40, 0xFFFFFF, collectibles_str);
	if (game->game_state == GAME_WIN)
		mlx_string_put(game->mlx, game->win, game->map.width * IMG_SIZE / 2 - 50,
				game->map.height * IMG_SIZE / 2, 0x00FF00, "Mission Completed!");
	else if (game->game_state == GAME_LOSE)
		mlx_string_put(game->mlx, game->win, game->map.width * IMG_SIZE / 2 - 50,
				game->map.height * IMG_SIZE / 2, 0xFF0000, "Mission Failed!");
}

/* 渲染整个游戏 */
void	render_game(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	render_map(game);
	render_player(game);
	render_ui(game);
}
