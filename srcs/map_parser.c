/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:21:58 by yufli             #+#    #+#             */
/*   Updated: 2025/06/07 21:17:58 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

/* Helper function to allocate memory for the map grid */
static int	allocate_map_grid(t_map *map)
{
	map->grid = (char **)malloc(sizeof(char *) * (map->height + 1));
	if (!map->grid)
	{
		error_exit("Grid memory allocation failed.");
		return (0);
	}
	map->grid[map->height] = NULL;
	return (1);
}

/* Helper function to validate the file extension and map height */
static int	validate_file_and_height(t_game *game, char *filename)
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
	return (1);
}

/* 解析地图文件 */
int	parse_map(t_game *game, char *filename)
{
	if (!validate_file_and_height(game, filename))
		return (0);
	if (!allocate_map_grid(&game->map))
		return (0);
	if (!read_map(&game->map, filename))
	{
		error_exit("Failed to read map data");
		return (0);
	}
	init_map_data(&game->map);
	return (1);
}
