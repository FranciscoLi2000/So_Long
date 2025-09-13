/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 09:10:11 by yufli             #+#    #+#             */
/*   Updated: 2025/08/29 09:37:32 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	**duplicate_map(char **src)
{
	char	**dst;
	int		rows;
	int		i;

	rows = 0;
	while (src[rows])
		rows++;
	dst = malloc((rows + 1) * sizeof(char *));
	if (!dst)
		error_exit("malloc failed\n");
	i = 0;
	while (i < rows)
	{
		dst[i] = ft_strdup(src[i]);
		if (!dst[i])
		{
			while (--i >= 0)
				free(dst[i]);
			free(dst);
			error_exit("ft_strdup failed\n");
		}
		i++;
	}
	dst[rows] = NULL;
	return (dst);
}

static void	free_map_copy(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

int	check_path(t_map *map)
{
	char		**copy;
	t_ff_input	input;
	int			collect;
	int			found_exit;

	copy = duplicate_map(map->grid);
	if (!copy)
		return (0);
	input.map = copy;
	input.size = (t_point){map->width, map->height};
	input.start = (t_point){map->player_x, map->player_y};
	input.coins = &collect;
	input.found_exit = &found_exit;
	collect = 0;
	found_exit = 0;
	flood_fill(input);
	free_map_copy(copy);
	if (collect != map->collectibles || !found_exit)
		return (0);
	return (1);
}
