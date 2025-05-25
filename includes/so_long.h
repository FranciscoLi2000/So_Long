/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:04:18 by yufli             #+#    #+#             */
/*   Updated: 2025/05/25 02:52:22 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "../minilibx_linux/mlx.h"

/* 定义游戏中使用的键码 */
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_DOWN 65364
# define KEY_RIGHT 65363

/* 定义游戏中的元素 */
# define EMPTY '0'
# define WALL '1'
# define COLLECTIBLE 'C'
# define EXIT 'E'
# define PLAYER 'P'
# define ENEMY 'X'  // 添加敌人元素

/* 定义图像大小 */
# define IMG_SIZE 32

/* 游戏状态 */
# define GAME_RUNNING 0
# define GAME_WIN 1
# define GAME_LOSE 2

/* 坐标结构 */
typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

/* 图像结构 */
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

/* 游戏地图结构 */
typedef struct s_map
{
	char	**grid;         // 地图网格
	int		width;          // 地图宽度
	int		height;         // 地图高度
	int		collectibles;   // 收集品总数
	int		exits;          // 出口数量
	int		players;        // 玩家数量
	int		enemies;        // 敌人数量
	t_pos	player_pos;     // 玩家位置
	t_pos	*enemy_pos;     // 敌人位置数组
}	t_map;

/* 游戏结构 */
typedef struct s_game
{
	void	*mlx;           // MLX连接指针
	void	*win;           // 窗口指针
	t_map	map;            // 游戏地图
	t_img	img_player;     // 玩家图像
	t_img	img_wall;       // 墙壁图像
	t_img	img_collectible;// 收集品图像
	t_img	img_exit;       // 出口图像
	t_img	img_floor;      // 地板图像
	t_img	img_enemy;      // 敌人图像
	int		collected;      // 已收集的收集品数量
	int		moves;          // 移动次数
	int		game_state;     // 游戏状态
}	t_game;

/* 初始化函数 - init.c */
int		init_game(t_game *game);
int		init_window(t_game *game);
int		init_images(t_game *game);
void	init_map_data(t_map *map);

/* 地图处理函数 - map.c */
int		parse_map(t_game *game, char *filename);
int		validate_map(t_game *game);
void	free_map(t_map *map);

/* 渲染函数 - render.c */
void	render_game(t_game *game);
void	render_map(t_game *game);
void	render_player(t_game *game);
void	render_ui(t_game *game);

/* 玩家相关函数 - player.c */
int		move_player(t_game *game, int key);
int		check_collision(t_game *game, int x, int y);
void	collect_item(t_game *game, int x, int y);
int		check_exit(t_game *game);

/* 敌人相关函数 - enemy.c */
void	move_enemies(t_game *game);
int		check_enemy_collision(t_game *game);

/* 工具函数 - utils.c */
void	error_exit(char *message);
int		key_handler(int keycode, t_game *game);
int		close_game(t_game *game);
void	free_game(t_game *game);

#endif
