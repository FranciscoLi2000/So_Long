/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 02:24:52 by yufli             #+#    #+#             */
/*   Updated: 2025/05/28 23:26:30 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* 初始化敌人位置 */
void	init_enemies(t_game *game)
{
	int	i;
	int	j;
	int	enemy_count;

	game->map.enemy_pos = (t_pos *)malloc(sizeof(t_pos) * game->map.enemies);
	if (!game->map.enemy_pos)
		error_exit("Failed to allocate memory for enemies");
	enemy_count = 0;
	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (game->map.grid[i][j] == ENEMY)
			{
				game->map.enemy_pos[enemy_count].x = j;
				game->map.enemy_pos[enemy_count].y = i;
				enemy_count++;
			}
			else if (game->map.grid[i][j] == PLAYER)
			{
				game->map.start_pos.x = j;
				game->map.start_pos.y = i;
			}
			j++;
		}
		i++;
	}
}

/*
** 检查敌人移动位置是否有效
*/
static int	is_valid_enemy_move(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map.width || y < 0 || y >= game->map.height)
		return (0);
	if (game->map.grid[y][x] == WALL ||
		game->map.grid[y][x] == EXIT ||
		game->map.grid[y][x] == COLLECTIBLE ||
		game->map.grid[y][x] == ENEMY)
		return (0);
	return (1);
}

/* 移动单个敌人 */
static void	move_single_enemy(t_game *game, int enemy_index)
{
	int		directions[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}}; // 上下左右
	int		new_x;
	int		new_y;
	int		dir;
	int		attempts;
	t_pos	*enemy;

	enemy = &game->map.enemy_pos[enemy_index];
	attempts = 0;
	while (attempts < 4)
	{
		dir = rand() % 4;
		new_x = enemy->x + directions[dir][0];
		new_y = enemy->y + directions[dir][1];
		if (is_valid_enemy_move(game, new_x, new_y))
		{
			game->map.grid[enemy->y][enemy->x] = EMPTY;
			game->map.grid[new_y][new_x] = ENEMY;
			enemy->x = new_x;
			enemy->y = new_y;
			break ;
		}
		attempts++;
	}
}

/* 移动所有敌人 */
int	move_enemies(t_game *game)
{
	int	i;
	int	moved;

	moved = 0;
	if (game->game_state != GAME_RUNNING)
		return (0);
	i = 0;
	while (i < game->map.enemies)
	{
		if (rand() % 5 == 0)
		{
			move_single_enemy(game, i);
			moved = 1;
		}
		i++;
	}
	if (moved && check_enemy_collision(game))
	{
	}
	if (moved)
		render_game(game);
	return (moved);
}
