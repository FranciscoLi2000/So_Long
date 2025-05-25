/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 02:22:25 by yufli             #+#    #+#             */
/*   Updated: 2025/05/25 21:51:10 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: [your_username] <[your_email]>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 [time]                      #+#    #+#             */
/*   Updated: 2025/05/25 [time]                     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/*
** 初始化游戏数据
*/
int	init_game(t_game *game)
{
	// 初始化MLX
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);

	// 初始化游戏状态
	game->collected = 0;
	game->moves = 0;
	game->game_state = GAME_RUNNING;

	// 初始化地图数据
	init_map_data(&game->map);

	return (1);
}

/*
** 初始化地图数据
*/
void	init_map_data(t_map *map)
{
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
	map->collectibles = 0;
	map->exits = 0;
	map->players = 0;
	map->enemies = 0;
	map->player_pos.x = 0;
	map->player_pos.y = 0;
	map->enemy_pos = NULL;
}

/*
** 初始化游戏窗口
*/
int	init_window(t_game *game)
{
	int	win_width;
	int	win_height;

	// 计算窗口大小
	win_width = game->map.width * IMG_SIZE;
	win_height = game->map.height * IMG_SIZE;

	// 创建窗口
	game->win = mlx_new_window(game->mlx, win_width, win_height, 
		"Jackie Chan: Escape from the British Museum");
	if (!game->win)
		return (0);

	return (1);
}

/*
** 初始化游戏图像
*/
int	init_images(t_game *game)
{
	int	width;
	int	height;

	// 加载玩家图像（Jackie Chan）
	game->img_player.img = mlx_xpm_file_to_image(game->mlx, 
		"textures/player.xpm", &width, &height);
	// 加载墙壁图像（博物馆墙壁）
	game->img_wall.img = mlx_xpm_file_to_image(game->mlx, 
		"textures/wall.xpm", &width, &height);
	// 加载收集品图像（中国文物）
	game->img_collectible.img = mlx_xpm_file_to_image(game->mlx, 
		"textures/collectible.xpm", &width, &height);
	// 加载出口图像（逃生车辆）
	game->img_exit.img = mlx_xpm_file_to_image(game->mlx, 
		"textures/exit.xpm", &width, &height);
	// 加载地板图像（博物馆地板）
	game->img_floor.img = mlx_xpm_file_to_image(game->mlx, 
		"textures/floor.xpm", &width, &height);
	// 加载敌人图像（博物馆保安）
	game->img_enemy.img = mlx_xpm_file_to_image(game->mlx, 
		"textures/enemy.xpm", &width, &height);

	// 检查是否所有图像都加载成功
	if (!game->img_player.img || !game->img_wall.img || 
		!game->img_collectible.img || !game->img_exit.img || 
		!game->img_floor.img || !game->img_enemy.img)
		return (0);

	return (1);
}
