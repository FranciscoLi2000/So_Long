/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:12:28 by yufli             #+#    #+#             */
/*   Updated: 2025/06/09 00:56:13 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	fill(t_ff_input *f, int row, int col)
{
	if (row < 0 || col < 0 || row >= f->size.y || col >= f->size.x)
		return ;
	if (f->map[row][col] == WALL || f->map[row][col] == 'F')
		return ;
	if (f->map[row][col] == COLLECTIBLE)
		(*f->coins)++;
	if (f->map[row][col] == EXIT)
		*(f->found_exit) = 1;
	f->map[row][col] = 'F';
	fill(f, row - 1, col);
	fill(f, row + 1, col);
	fill(f, row, col - 1);
	fill(f, row, col + 1);
}

void	flood_fill(t_ff_input input)
{
	fill(&input, input.start.y, input.start.x);
}
