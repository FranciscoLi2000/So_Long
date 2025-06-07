/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:45:37 by yufli             #+#    #+#             */
/*   Updated: 2025/06/07 18:47:00 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/* 处理窗口关闭事件 */
int	close_window(t_game *game)
{
	clean_exit(game, EXIT_SUCCESS);
	return (0);
}

/* 处理键盘按键事件 */
int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_window(game);
	if (game->game_over)
		return (0);
	if (keycode == KEY_W)
		move_player(game, game->map.player_x, game->map.player_y - 1);
	else if (keycode == KEY_A)
		move_player(game, game->map.player_x - 1, game->map.player_y);
	else if (keycode == KEY_S)
		move_player(game, game->map.player_x, game->map.player_y + 1);
	else if (keycode == KEY_D)
		move_player(game, game->map.player_x + 1, game->map.player_y);
	return (0);
}
