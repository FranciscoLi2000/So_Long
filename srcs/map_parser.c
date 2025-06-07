/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:21:58 by yufli             #+#    #+#             */
/*   Updated: 2025/06/07 17:21:34 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/* 检查文件扩展名是否为.ber */
static int	check_file_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	if (ft_strncmp(filename + len - 4, ".ber", 4) != 0)
		return (0);
	return (1);
}

/* 计算地图的高度（行数） */
static int	get_map_height(char *filename)
{
	int		fd;
	int		height;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	height = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		height++;
		free(line);
	}
	close(fd);
	return (height);
}

/* 读取地图文件并填充地图数据结构 */
static int	read_map(t_map *map, char *filename)
{
	int		fd;
	int		i;
	char	*line;
	char	*tmp;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	i = 0;
	while (i < map->height)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		tmp = line;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		map->grid[i] = ft_strdup(line);
		free(tmp);
		if (!map->grid[i])
			return (0);
		if (i == 0)
			map->width = ft_strlen(map->grid[i]);
		i++;
	}
	close(fd);
	return (1);
}

/* 释放地图内存 */
void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (!map->grid)
		return ;
	while (i < map->height)
	{
		if (map->grid[i])
			free(map->grid[i]);
		i++;
	}
	free(map->grid);
	map->grid = NULL;
}

/* 解析地图文件 */
int	parse_map(t_game *game, char *filename)
{
	if (!check_file_extension(filename))
	{
		error_exit("Invalid file extension.");
		return (0);
	}
	game->map.height = get_map_height(filename);
	if (game->map.height <= 0)
	{
		error_exit("Failed to read map or map is empty");
		return (0);
	}
	game->map.grid = (char **)malloc(sizeof(char *) * (game->map.height + 1));
	if (!game->map.grid)
	{
		error_exit("Grid memory allocation failed.");
		return (0);
	}
	game->map.grid[game->map.height] = NULL;
	if (!read_map(&game->map, filename))
	{
		error_exit("Failed to read map data");
		return (0);
	}
	init_map_data(&game->map);
	return (1);
}
