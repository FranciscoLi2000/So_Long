/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 11:11:27 by yufli             #+#    #+#             */
/*   Updated: 2025/06/08 12:07:56 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* 解析 .ber 文件，转换为二维字符数组 */
char	**read_map(char *filename)
{
	int		fd;
	char	*line;
	char	*map_str;
	char	*tmp;
	char	**map;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Error\nCannot open map file");
	map_str = ft_strdup("");
	line = get_next_line(fd);
	while (line)
	{
		tmp = ft_strjoin(map_str, line);
		free(map_str);
		free(line);
		map_str = ft_strjoin(tmp, "\n");
		free(tmp);
		line = get_next_line(fd);
	}
	close(fd);
	map = ft_split(map_str, '\n');
	free(map_str);
	return (map);
}

/* 验证地图是否合法（封闭、字符合法、路径可达） */
int	validate_map(t_map *map)
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
	if (!check_elements(map))
	{
		ft_printf("Map has invalid elements ");
		error_exit("or missing required elements");
		return (0);
	}
	if (!check_path(*map))
	{
		error_exit("No valid path found in the map");
		return (0);
	}
	return (1);
}
