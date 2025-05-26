/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 02:23:10 by yufli             #+#    #+#             */
/*   Updated: 2025/05/26 16:22:12 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
** 计算文件行数
*/
static int	count_lines(char *filename)
{
	int		fd;
	int		lines;
	char	buffer[1024];
	int		bytes_read;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	lines = 0;
	while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
	{
		i = 0;
		while (i < bytes_read)
		{
			if (buffer[i] == '\n')
				lines++;
			i++;
		}
		// 如果最后一行没有换行符
		if (bytes_read > 0 && buffer[bytes_read - 1] != '\n')
			lines++;
	}
	close(fd);
	return (lines);
}

/*
** 读取地图文件
*/
static char	**read_map_file(char *filename, int height)
{
	int		fd;
	char	**map;
	char	*line;
	int		i;
	int		len;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = (char **)malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	i = 0;
	// 这里假设有一个get_next_line函数来读取文件的每一行
	// 如果您没有这个函数，可以自己实现一个简单的版本
	while (i < height && (line = get_next_line(fd)) != NULL)
	{
		// 移除行尾的换行符
		len = strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		map[i] = line;
		i++;
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

/*
** 解析地图元素
*/
static void	parse_map_elements(t_game *game)
{
	int	i;
	int	j;

	game->map.collectibles = 0;
	game->map.exits = 0;
	game->map.players = 0;
	game->map.enemies = 0;

	for (i = 0; i < game->map.height; i++)
	{
		for (j = 0; j < game->map.width; j++)
		{
			if (game->map.grid[i][j] == COLLECTIBLE)
				game->map.collectibles++;
			else if (game->map.grid[i][j] == EXIT)
				game->map.exits++;
			else if (game->map.grid[i][j] == PLAYER)
			{
				game->map.players++;
				game->map.player_pos.x = j;
				game->map.player_pos.y = i;
			}
			else if (game->map.grid[i][j] == ENEMY)
				game->map.enemies++;
			else if (game->map.grid[i][j] != EMPTY && game->map.grid[i][j] != WALL)
				error_exit("Invalid character in map");
		}
	}
}

/*
** 解析地图
*/
int	parse_map(t_game *game, char *filename)
{
	int	height;

	// 计算地图高度
	height = count_lines(filename);
	if (height <= 0)
		return (0);
	game->map.height = height;

	// 读取地图文件
	game->map.grid = read_map_file(filename, height);
	if (!game->map.grid)
		return (0);

	// 设置地图宽度
	game->map.width = strlen(game->map.grid[0]);

	// 解析地图元素
	parse_map_elements(game);

	return (1);
}

/*
** 创建地图副本用于Flood Fill检查
*/
static char	**create_map_copy(t_map *map)
{
	char	**copy;
	int		i;

	copy = (char **)malloc(sizeof(char *) * (map->height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		copy[i] = strdup(map->grid[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

/*
** Flood Fill算法实现
*/
static void	flood_fill(char **map, int height, int width, t_pos pos)
{
	// 检查边界条件
	if (pos.y < 0 || pos.y >= height || pos.x < 0 || pos.x >= width)
		return;
	
	// 如果当前位置是墙或已经被访问过，则返回
	if (map[pos.y][pos.x] == '1' || map[pos.y][pos.x] == 'F')
		return;
	
	// 标记当前位置为已访问
	map[pos.y][pos.x] = 'F';
	
	// 递归访问上下左右四个方向
	t_pos up = {pos.x, pos.y - 1};
	t_pos down = {pos.x, pos.y + 1};
	t_pos left = {pos.x - 1, pos.y};
	t_pos right = {pos.x + 1, pos.y};
	
	flood_fill(map, height, width, up);
	flood_fill(map, height, width, down);
	flood_fill(map, height, width, left);
	flood_fill(map, height, width, right);
}

/*
** 检查地图是否有效（所有收集品和出口都可达）
*/
static int	check_map_valid_path(t_game *game)
{
	char	**map_copy;
	int		i;
	int		j;
	int		valid;
	
	// 创建地图副本
	map_copy = create_map_copy(&game->map);
	if (!map_copy)
		return (0);
	
	// 从玩家位置开始进行Flood Fill
	flood_fill(map_copy, game->map.height, game->map.width, game->map.player_pos);
	
	// 检查所有收集品和出口是否都被标记为可达
	valid = 1;
	for (i = 0; i < game->map.height; i++)
	{
		for (j = 0; j < game->map.width; j++)
		{
			if (game->map.grid[i][j] == 'C' || game->map.grid[i][j] == 'E')
			{
				if (map_copy[i][j] != 'F')
				{
					valid = 0;
					break;
				}
			}
		}
		if (!valid)
			break;
	}
	
	// 释放地图副本
	for (i = 0; i < game->map.height; i++)
		free(map_copy[i]);
	free(map_copy);
	
	return (valid);
}

/*
** 验证地图
*/
int	validate_map(t_game *game)
{
	int	i;
	int	width;
	
	// 检查地图是否为矩形
	width = game->map.width;
	for (i = 0; i < game->map.height; i++)
	{
		if ((int)strlen(game->map.grid[i]) != width)
			return (0);
	}
	
	// 检查地图是否被墙壁包围
	for (i = 0; i < width; i++)
	{
		if (game->map.grid[0][i] != '1' || game->map.grid[game->map.height - 1][i] != '1')
			return (0);
	}
	for (i = 0; i < game->map.height; i++)
	{
		if (game->map.grid[i][0] != '1' || game->map.grid[i][width - 1] != '1')
			return (0);
	}
	
	// 检查地图元素数量
	if (game->map.collectibles < 1 || game->map.exits != 1 || game->map.players != 1)
		return (0);
	
	// 使用Flood Fill检查所有收集品和出口是否可达
	if (!check_map_valid_path(game))
		return (0);
	
	return (1);
}

/*
** 释放地图资源
*/
void	free_map(t_map *map)
{
	int	i;

	if (map->grid)
	{
		i = 0;
		while (i < map->height)
		{
			free(map->grid[i]);
			i++;
		}
		free(map->grid);
		map->grid = NULL;
	}
	if (map->enemy_pos)
	{
		free(map->enemy_pos);
		map->enemy_pos = NULL;
	}
}
