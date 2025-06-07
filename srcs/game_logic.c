/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:48:34 by yufli             #+#    #+#             */
/*   Updated: 2025/06/07 18:56:48 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/* 检查是否收集到物品 */
void	check_collectible(t_game *game, int x, int y)
{
	if (game->map.grid[y][x] == COLLECTIBLE)
	{
		game->map.grid[y][x] = EMPTY;
		game->map.collected++;
	}
}

/* 检查是否到达出口 */
void	check_exit(t_game *game)
{
	if (game->map.grid[game->map.player_y][game->map.player_x] == EXIT
		&& game->map.collected == game->map.collectibles)
	{
		ft_printf("Congratulations! You escaped the British Museum in %d moves!\n",
			game->moves);
		game->game_over = 1;
	}
}

/* 移动玩家 */
int	move_player(t_game *game, int new_x, int new_y)
{
	if (game->map.grid[new_y][new_x] == WALL)
		return (0);
	if (game->map.grid[new_y][new_x] == EXIT
		&& game->map.collected != game->map.collectibles)
		return (0);
	game->map.grid[game->map.player_y][game->map.player_x] = EMPTY;
	check_collectible(game, new_x, new_y);
	game->map.player_x = new_x;
	game->map.player_y = new_y;
	game->map.grid[new_y][new_x] = PLAYER;
	game->moves++;
	check_exit(game);
	render_game(game);
	return (1);
}
