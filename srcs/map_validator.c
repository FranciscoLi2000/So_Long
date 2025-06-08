/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:24:26 by yufli             #+#    #+#             */
/*   Updated: 2025/06/08 09:54:39 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

/* Helper function to check if the exit is reachable */
static int	is_exit_reachable(char **tmp_map, int height)
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

/* 检查地图是否有有效路径 */
static int	check_path(t_map map)
{
	char	**tmp_map;
	int		count;

	tmp_map = duplicate_map(&map);
	if (!tmp_map)
		return (0);
	count = 0;
	flood_fill(tmp_map, map.player_x, map.player_y,
		&count, map.width, map.height);
	return (count == map.collectibles
		&& is_exit_reachable(tmp_map, map.height));
}

/* 验证地图是否符合所有要求 */
int	validate_map(t_map *map)
{
	if (!validate_structure(map))
		return (0);
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
