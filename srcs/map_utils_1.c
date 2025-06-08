/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 11:33:14 by yufli             #+#    #+#             */
/*   Updated: 2025/06/09 00:53:40 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**duplicate_map(char **src)
{
	char	**dst;
	int		rows;
	int		i;

	rows = 0;
	while (src[rows])
		rows++;
	dst = malloc((rows + 1) * sizeof(char *));
	if (!dst)
		error_exit("Error\nmalloc failed");
	i = 0;
	while (i < rows)
	{
		dst[i] = ft_strdup(src[i]);
		i++;
	}
	dst[rows] = NULL;
	return (dst);
}

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
	error_exit("Error\nNo player start found");
	return (p);
}

int	count_collectibles(char **map)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'C')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

void	free_map_copy(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

int	check_path(t_map map)
{
	char		**copy;
	t_ff_input	input;
	int			collect;
	int			found_exit;

	copy = duplicate_map(map.grid);
	if (!copy)
		return (0);
	input.map = copy;
	input.size = (t_point){map.width, map.height};
	input.start = (t_point){map.player_x, map.player_y};
	input.coins = &collect;
	input.found_exit = &found_exit;
	collect = 0;
	found_exit = 0;
	flood_fill(input);
	free_map_copy(copy);
	if (collect != map.collectibles || !found_exit)
		return (0);
	return (1);
}
