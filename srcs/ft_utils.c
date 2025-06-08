/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 00:11:32 by yufli             #+#    #+#             */
/*   Updated: 2025/06/08 09:38:06 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Helper function to duplicate the map */
char	**duplicate_map(t_map *map)
{
	char	**tmp_map;
	int		i;

	tmp_map = (char **)malloc(sizeof(char *) * (map->height + 1));
	if (!tmp_map)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		tmp_map[i] = ft_strdup(map->grid[i]);
		if (!tmp_map[i++])
		{
			while (--i >= 0)
				free(tmp_map[i]);
			free(tmp_map);
			return (NULL);
		}
	}
	tmp_map[i] = NULL;
	return (tmp_map);
}

/* Helper function to check if the exit is reachable */
int	is_exit_reachable(char **tmp_map, int height)
{
	int	i;
	int	exit_found;

	exit_found = 0;
	i = 0;
	while (i < height)
	{
		if (ft_strchr(tmp_map[i], 'X'))
			exit_found = 1;
		free(tmp_map[i++]);
	}
	free(tmp_map);
	return (exit_found);
}

/* Helper function to validate rectangle and walls */
int	validate_structure(t_map *map)
{
	if (!check_rectangle(map))
	{
		error_exit("Map is not rectangular");
		return (0);
	}
	if (!check_walls(map))
	{
		error_exit("Map is not surrounded by walls");
		return (0);
	}
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

/* 检查文件扩展名是否为.ber */
int	check_file_extension(char *filename)
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
int	get_map_height(char *filename)
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