/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:48:03 by yufli             #+#    #+#             */
/*   Updated: 2025/06/08 09:49:33 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* 使用深度优先搜索检查是否存在有效路径 */
static void	fill(char **tab, t_point size, char target, int row, int col)
{
	if (row < 0 || col < 0 || row >= size.y || col >= size.x)
		return ;
	if (tab[row][col] == 'F' || tab[row][col] != target)
		return ;
	tab[row][col] = 'F';
	fill(tab, size, target, row - 1, col);
	fill(tab, size, target, row + 1, col);
	fill(tab, size, target, row, col - 1);
	fill(tab, size, target, row, col + 1);
}

void	flood_fill(char **tab, t_point size, t_point begin)
{
	char	target;

	target = tab[begin.y][begin.x];
	fill(tab, size, target, begin.y, begin.x);
}
