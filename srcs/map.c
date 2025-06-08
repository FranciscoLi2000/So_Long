/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 11:11:27 by yufli             #+#    #+#             */
/*   Updated: 2025/06/09 00:52:20 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**read_map(char *filename)
{
	int		fd;
	char	*line;
	char	*map_str;
	char	*tmp;
	char	**map;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Error\nCannot open map file");
	map_str = ft_strdup("");
	line = get_next_line(fd);
	while (line)
	{
		tmp = ft_strjoin(map_str, line);
		free(map_str);
		free(line);
		map_str = ft_strjoin(tmp, "\n");
		free(tmp);
		line = get_next_line(fd);
	}
	close(fd);
	map = ft_split(map_str, '\n');
	free(map_str);
	return (map);
}

int	validate_map(t_map *map)
{
	if (!check_rectangle(map))
		error_exit("Map is not rectangular");
	if (!check_walls(map))
		error_exit("Map is not surrounded by walls");
	if (!check_elements(map))
		error_exit("Map has invalid or missing required elements");
	if (!check_path(*map))
		error_exit("No valid path found in the map");
	return (1);
}
