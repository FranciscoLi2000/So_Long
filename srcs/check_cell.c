/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 09:02:55 by yufli             #+#    #+#             */
/*   Updated: 2025/08/29 09:04:41 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
