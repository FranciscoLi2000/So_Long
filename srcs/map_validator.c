/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:24:26 by yufli             #+#    #+#             */
/*   Updated: 2025/06/07 19:17:12 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/* 检查地图是否是矩形 */
static int	check_rectangle(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		if (ft_strlen(map->grid[i]) != map->width)
			return (0);
		i++;
	}
	return (1);
}

/* 检查地图是否被墙壁包围 */
static int	check_walls(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if ((i == 0 || i == map->height - 1
				|| j == 0 || j == map->width - 1)
				&& map->grid[i][j] != WALL)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

/* 检查地图元素是否有效 */
static int	check_elements(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->grid[i][j] == PLAYER)
			{
				map->player_x = j;
				map->player_y = i;
				map->players++;
			}
			else if (map->grid[i][j] == EXIT)
			{
				map->exit_x = j;
				map->exit_y = i;
				map->exits++;
			}
			else if (map->grid[i][j] == COLLECTIBLE)
				map->collectibles++;
			else if (map->grid[i][j] != EMPTY
				&& map->grid[i][j] != WALL)
				return (0);
			j++;
		}
		i++;
	}
	return (map->players == 1 && map->exits == 1 && map->collectibles >= 1);
}

/* 检查地图是否有有效路径 */
static int	check_path(t_map map)
{
	char	**tmp_map;
	int		i;
	int		count;
	int		exit_found;

	tmp_map = (char **)malloc(sizeof(char *) * (map.height + 1));
	if (!tmp_map)
		return (0);
	i = 0;
	while (i < map.height)
	{
		tmp_map[i] = ft_strdup(map.grid[i]);
		if (!tmp_map[i++])
		{
			while (--i >= 0)
				free(tmp_map[i]);
			free(tmp_map);
			return (0);
		}
	}
	tmp_map[i] = NULL;
	count = 0;
	flood_fill(tmp_map, map.player_x, map.player_y, &count);
	exit_found = 0;
	i = 0;
	while (i < map.height)
	{
		if (ft_strchr(tmp_map[i], 'X'))
			exit_found = 1;
		free(tmp_map[i++]);
	}
	free(tmp_map);
	return (count == map.collectibles && exit_found);
}

/* 验证地图是否符合所有要求 */
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
		error_exit("Map has invalid elements");
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
