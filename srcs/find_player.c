/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 09:29:13 by yufli             #+#    #+#             */
/*   Updated: 2025/08/29 09:38:04 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_point	find_player(char **map)
{
	t_point	p;
	int		y;
	int		x;

	p.x = -1;
	p.y = -1;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
			{
				p.x = x;
				p.y = y;
				return (p);
			}
			x++;
		}
		y++;
	}
	error_exit("No player start found\n");
	return (p);
}
