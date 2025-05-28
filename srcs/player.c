/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 02:24:19 by yufli             #+#    #+#             */
/*   Updated: 2025/05/28 22:07:29 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* 检查碰撞 */
int	check_collision(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map.width || y < 0 || y >= game->map.height)
		return (1);
	if (game->map.grid[y][x] == WALL)
		return (1);
	return (0);
}

/* 收集物品 */
void	collect_item(t_game *game, int x, int y)
{
	if (game->map.grid[y][x] == COLLECTIBLE)
	{
		game->collected++;
		game->map.grid[y][x] = EMPTY;
		ft_printf("Collected: %d/%d\n", game->collected, game->map.collectibles);
	}
}

/* 检查出口 */
int	check_exit(t_game *game)
{
	int	x;
	int	y;

	x = game->map.player_pos.x;
	y = game->map.player_pos.y;
	if (game->map.grid[y][x] == EXIT && game->collected == game->map.collectibles)
	{
		game->game_state = GAME_WIN;
		ft_printf("Mission Completed!\n");
		ft_printf("Moved times: %d\n", game->moves);
		return (1);
	}
	else if (game->map.grid[y][x] == EXIT && game->collected < game->map.collectibles)
	{
		ft_printf("You need to collect all the treasure: %d/", game->collected);
		ft_printf("%d\n", game->map.collectibles);
	}
	return (0);
}

/* 检查敌人碰撞 */
int	check_enemy_collision(t_game *game)
{
	int	i;
	int	player_x;
	int	player_y;

	player_x = game->map.player_pos.x;
	player_y = game->map.player_pos.y;
	i = 0;
	while (i < game->map.enemies)
	{
		if (player_x == game->map.enemy_pos[i].x && player_y == game->map.enemy_pos[i].y)
		{
			ft_printf("Jackie Chan is caught by the guardian.\n");
			game->map.player_pos.x = game->map.start_pos.x;
			game->map.player_pos.y = game->map.start_pos.y;
			game->moves++;
			render_game(game);
			return (1);
		}
		i++;
	}
	return (0);
}

/* 移动玩家 */
int	move_player(t_game *game, int key)
{
	int	new_x;
	int	new_y;

	if (game->game_state != GAME_RUNNING)
		return (0);
	new_x = game->map.player_pos.x;
	new_y = game->map.player_pos.y;
	if (key == KEY_W || key == KEY_UP)
		new_y--;
	else if (key == KEY_S || key == KEY_DOWN)
		new_y++;
	else if (key == KEY_A || key == KEY_LEFT)
		new_x--;
	else if (key == KEY_D || key == KEY_RIGHT)
		new_x++;
	else
		return (0);
	if (check_collision(game, new_x, new_y))
		return (0);
	game->map.player_pos.x = new_x;
	game->map.player_pos.y = new_y;
	game->moves++;
	collect_item(game, new_x, new_y);
	check_exit(game);
	check_enemy_collision(game);
	render_game(game);
	return (1);
}
