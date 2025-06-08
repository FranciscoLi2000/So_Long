/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:12:28 by yufli             #+#    #+#             */
/*   Updated: 2025/06/08 20:40:11 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	fill(t_ff_input *f, int row, int col)
{
	if (row < 0 || col < 0 || row >= f->size.y || col >= f->size.x)
		return ;
	if (f->map[row][col] == '1' || f->map[row][col] == 'F')
		return ;
	if (f->map[row][col] == 'C')
		(*f->coins)++;
	if (f->map[row][col] == 'E')
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
