/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:28:05 by yufli             #+#    #+#             */
/*   Updated: 2025/05/28 23:10:49 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
** Create map copy for flood fill checking
*/
static char	**create_map_copy(t_map *map)
{
	char	**copy;
	int		i;

	copy = (char **)malloc(sizeof(char *) * (map->height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		copy[i] = ft_strdup(map->grid[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

/*
** Flood fill algorithm implementation
*/
static void	flood_fill(char **map, int height, int width, t_pos pos)
{
	int	row;
	int	col;

	row = pos.y;
	col = pos.x;
	if (row < 0 || col < 0 || row >= height || col >= width)
		return ;
	if (map[row][col] == '1' || map[row][col] == 'F')
		return ;
	map[row][col] = 'F';
	flood_fill(map, height, width, (t_pos){pos.x, pos.y - 1});
	flood_fill(map, height, width, (t_pos){pos.x, pos.y + 1});
	flood_fill(map, height, width, (t_pos){pos.x - 1, pos.y});
	flood_fill(map, height, width, (t_pos){pos.x + 1, pos.y});
}

/*
** Check if map has valid path (all collectibles and exit reachable)
*/
static int	check_map_valid_path(t_game *game)
{
	char	**map_copy;
	int		i;
	int		j;
	int		valid;

	map_copy = create_map_copy(&game->map);
	if (!map_copy)
		return (0);
	flood_fill(map_copy, game->map.height, game->map.width,
		game->map.player_pos);
	valid = 1;
	i = 0;
	while (i < game->map.height && valid)
	{
		j = 0;
		while (j < game->map.width)
		{
			if ((game->map.grid[i][j] == 'C' || game->map.grid[i][j] == 'E')
				&& map_copy[i][j] != 'F')
			{
				valid = 0;
				break ;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < game->map.height)
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
	return (valid);
}

/*
** Validate map according to project requirements
*/
int	validate_map(t_game *game)
{
	int	i;
	int	width;

	width = game->map.width;
	i = 0;
	while (i < game->map.height)
	{
		if ((int)ft_strlen(game->map.grid[i]) != width)
			return (0);
		i++;
	}
	i = 0;
	while (i < width)
	{
		if (game->map.grid[0][i] != '1' ||
			game->map.grid[game->map.height - 1][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < game->map.height)
	{
		if (game->map.grid[i][0] != '1' ||
			game->map.grid[i][width - 1] != '1')
			return (0);
		i++;
	}
	if (game->map.collectibles < 1 || game->map.exits != 1 ||
		game->map.players != 1)
		return (0);
	if (!check_map_valid_path(game))
		return (0);
	game->map.start_pos.x = game->map.player_pos.x;
	game->map.start_pos.y = game->map.player_pos.y;
	return (1);
}

/*
** Free map resources
*/
void	free_map(t_map *map)
{
	int	i;

	if (map->grid)
	{
		i = 0;
		while (i < map->height)
		{
			free(map->grid[i]);
			i++;
		}
		free(map->grid);
		map->grid = NULL;
	}
}
