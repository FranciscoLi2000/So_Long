#include "so_long.h"

static int	check_rectangle(t_map *map)
{
	int	width;
	int	y;

	width = ft_strlen(map->grid[0]);
	y = 0;
	while (map->grid[y])
	{
		if (ft_strlen(map->grid[y]) != width)
			return (0);
		y++;
	}
	map->height = y;
	map->width = width;
	return (1);
}

static int	check_elements(t_map *map)
{
	char	c;
	int		y;
	int		x;

	y = 0;
	while (map->grid[y])
	{
		x = 0;
		while (map->grid[y][x])
		{
			c = map->grid[y][x];
			if (c == PLAYER)
			{
				map->player_x = x;
				map->player_y = y;
				map->players++;
			}
			else if (c == EXIT)
			{
				map->exit_x = x;
				map->exit_y = y;
				map->exits++;
			}
			else if (c == COLLECTIBLE)
				map->collectibles++;
			else if (c != EMPTY && c != WALL)
				return (0); // 非法字符
			x++;
		}
		y++;
	}
	return (map->players == 1 && map->exits == 1 && map->collectibles > 0);
}

static int	check_walls(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->width)
	{
		if (map->grid[0][i] != WALL || map->grid[map->height - 1][i] != WALL)
			return (0);
		i++;
	}
	i = 0;
	while (i < map->height)
	{
		if (map->grid[i][0] != WALL || map->grid[i][map->width - 1] != WALL)
			return (0);
		i++;
	}
	return (1);
}

int	validate_map(t_map *map)
{
	if (!check_rectangle(map))
		error_exit("Error: Map is not rectangular.");
	if (!check_walls(map))
		error_exit("Error: Map is not closed with walls.");
	if (!check_elements(map))
		error_exit("Error: Map must have 1 P, 1 E, and at least 1 C.");
	if (!check_path(*map))
		error_exit("Error: Map path is not valid.");
	return (1);
}
