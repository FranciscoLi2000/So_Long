/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:48:03 by yufli             #+#    #+#             */
/*   Updated: 2025/06/07 17:51:31 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/* 使用深度优先搜索检查是否存在有效路径 */
void	flood_fill(char **map, int x, int y, int *count)
{
	if (map[y][x] == WALL || map[y][x] == 'V')
		return ;
	if (map[y][x] == COLLECTIBLE)
		(*count)++;
	if (map[y][x] == EXIT)
	{
		map[y][x] = 'X';
		return ;
	}
	map[y][x] = 'V';
	flood_fill(map, x + 1, y, count);
	flood_fill(map, x - 1, y, count);
	flood_fill(map, x, y + 1, count);
	flood_fill(map, x, y - 1, count);
}
