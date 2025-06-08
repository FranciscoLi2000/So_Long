/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 16:12:57 by yufli             #+#    #+#             */
/*   Updated: 2025/06/08 17:18:29 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* 检查地图是否是矩形 */
int	check_rectangle(t_map *map)
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
int	check_walls(t_map *map)
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

int	check_cell(t_map *map, int i, int j)
{
	char	c;

	c = map->grid[i][j];
	if (c == PLAYER)
	{
		map->player_x = j;
		map->player_y = i;
		map->players++;
	}
	else if (c == EXIT)
	{
		map->exit_x = j;
		map->exit_y = i;
		map->exits++;
	}
	else if (c == COLLECTIBLE)
		map->collectibles++;
	else if (c != EMPTY && c != WALL)
		return (0);
	return (1);
}

/* 检查地图元素是否有效 */
int	check_elements(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (!check_cell(map, i, j))
				return (0);
			j++;
		}
		i++;
	}
	return (map->players == 1 && map->exits == 1 && map->collectibles >= 1);
}
