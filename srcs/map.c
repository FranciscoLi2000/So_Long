/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 02:23:10 by yufli             #+#    #+#             */
/*   Updated: 2025/05/29 00:30:42 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	count_lines(char *filename)
{
	int		fd;
	int		lines;
	char	buffer[1024];
	int		bytes_read;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	lines = 0;
	while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
	{
		i = 0;
		while (i < bytes_read)
		{
			if (buffer[i] == '\n')
				lines++;
			i++;
		}
		if (bytes_read > 0 && buffer[bytes_read - 1] != '\n')
			lines++;
	}
	close(fd);
	return (lines);
}

static char	**read_map_file(char *filename, int height)
{
	int		fd;
	char	**map;
	char	*line;
	int		i;
	int		len;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = (char **)malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (i < height && (line = get_next_line(fd)) != NULL)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		map[i] = line;
		i++;
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

static void	parse_map_elements(t_game *game)
{
	int	i;
	int	j;

	game->map.collectibles = 0;
	game->map.exits = 0;
	game->map.players = 0;
	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (game->map.grid[i][j] == COLLECTIBLE)
				game->map.collectibles++;
			else if (game->map.grid[i][j] == EXIT)
				game->map.exits++;
			else if (game->map.grid[i][j] == PLAYER)
			{
				game->map.players++;
				game->map.player_pos.x = j;
				game->map.player_pos.y = i;
			}
			else if (game->map.grid[i][j] != EMPTY &&
				game->map.grid[i][j] != WALL)
				error_exit("Invalid character in map");
			j++;
		}
		i++;
	}
}

int	parse_map(t_game *game, char *filename)
{
	int	height;

	height = count_lines(filename);
	if (height <= 0)
		return (0);
	game->map.height = height;
	game->map.grid = read_map_file(filename, height);
	if (!game->map.grid)
		return (0);
	game->map.width = ft_strlen(game->map.grid[0]);
	parse_map_elements(game);
	return (1);
}
