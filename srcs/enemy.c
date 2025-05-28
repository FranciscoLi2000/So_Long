/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 02:24:52 by yufli             #+#    #+#             */
/*   Updated: 2025/05/25 02:25:18 by yufli            ###   ########.fr       */
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
			j++;
		}
		i++;
	}
}

/* 移动单个敌人 */
static void	move_single_enemy(t_game *game, int enemy_index)
{
	t_pos	*enemy;
	int		directions[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
	int		new_x;
	int		new_y;
	int		dir;

	enemy = &game->map.enemy_pos[enemy_index];
	dir = rand() % 4;
	new_x = enemy->x + directions[dir][0];
	new_y = enemy->y + directions[dir][1];
	if (new_x >= 0 && new_x < game->map.width && new_y >= 0 && new_y < game->map.height
		&& game->map.grid[new_y][new_x] != WALL
		&& game->map.grid[new_y][new_x] != EXIT
		&& game->map.grid[new_y][new_x] != COLLECTIBLE)
	{
		game->map.grid[enemy->y][enemy->x] = EMPTY;
		game->map.grid[new_y][new_x] = ENEMY;
		enemy->x = new_x;
		enemy->y = new_y;
	}
}

/* 移动所有敌人 */
void	move_enemies(t_game *game)
{
	int	i;

	if (game->game_state != GAME_RUNNING)
		return ;
	i = 0;
	while (i < game->map.enemies)
	{
		move_single_enemy(game, i);
		i++;
	}
	if (check_enemy_collision(game))
		render_game(game);
}
