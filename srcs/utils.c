/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 02:25:27 by yufli             #+#    #+#             */
/*   Updated: 2025/05/26 16:18:28 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
** 错误退出函数
*/
void	error_exit(char *message)
{
	printf("Error\n%s\n", message);
	exit(1);
}

/*
** 键盘事件处理函数
*/
int	key_handler(int keycode, t_game *game)
{
	if (game->game_state != GAME_RUNNING && keycode != KEY_ESC)
		return (0);
	if (keycode == KEY_ESC)
		close_game(game);
	else if (keycode == KEY_W || keycode == KEY_UP)
		move_player(game, keycode);
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		move_player(game, keycode);
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		move_player(game, keycode);
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		move_player(game, keycode);
	return (0);
}

/*
** 关闭游戏函数
*/
int	close_game(t_game *game)
{
	free_game(game);
	exit(0);
	return (0);
}

/*
** 释放游戏资源函数
*/
void	free_game(t_game *game)
{
	if (game->map.grid)
		free_map(&game->map);
	if (game->img_player.img)
		mlx_destroy_image(game->mlx, game->img_player.img);
	if (game->img_wall.img)
		mlx_destroy_image(game->mlx, game->img_wall.img);
	if (game->img_collectible.img)
		mlx_destroy_image(game->mlx, game->img_collectible.img);
	if (game->img_exit.img)
		mlx_destroy_image(game->mlx, game->img_exit.img);
	if (game->img_floor.img)
		mlx_destroy_image(game->mlx, game->img_floor.img);
	if (game->img_enemy.img)
		mlx_destroy_image(game->mlx, game->img_enemy.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	free(game->mlx);
}
