/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 02:25:27 by yufli             #+#    #+#             */
/*   Updated: 2025/05/25 21:51:43 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: [your_username] <[your_email]>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 [time]                      #+#    #+#             */
/*   Updated: 2025/05/25 [time]                     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

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
	// 如果游戏已经结束，只响应ESC键
	if (game->game_state != GAME_RUNNING && keycode != KEY_ESC)
		return (0);

	// ESC键退出游戏
	if (keycode == KEY_ESC)
		close_game(game);
	// WASD或方向键移动玩家
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
	// 释放资源
	free_game(game);
	// 退出程序
	exit(0);
	return (0);
}

/*
** 释放游戏资源函数
*/
void	free_game(t_game *game)
{
	// 释放地图资源
	if (game->map.grid)
		free_map(&game->map);

	// 释放图像资源
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

	// 销毁窗口
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);

	// 销毁MLX连接
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	free(game->mlx);
}
