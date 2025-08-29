/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 10:28:24 by yufli             #+#    #+#             */
/*   Updated: 2025/08/29 11:57:03 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	count_map_lines(char *filename)
{
	int		fd;
	int		lines;
	char	buffer;
	int		bytes_read;

	lines = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	bytes_read = read(fd, &buffer, 1);
	while (bytes_read > 0)
	{
		if (buffer == '\n')
			lines++;
		bytes_read = read(fd, &buffer, 1);
	}
	close(fd);
	if (lines > 0 && buffer != '\n')
		lines++;
	if (lines == 0 && bytes_read == 0)
		return (-1);
	return (lines);
}

static char	**fill_grid_from_file(int fd, int lines)
{
	char	**grid;
	char	*line;
	int		i;

	grid = (char **)malloc(sizeof(char *) * (lines + 1));
	if (!grid)
		return (NULL);
	i = 0;
	while (i < lines)
	{
		line = get_next_line(fd);
		if (!line)
		{
			while (i > 0)
				free(grid[--i]);
			free(grid);
			return (NULL);
		}
		grid[i] = line;
		i++;
	}
	grid[i] = NULL;
	return (grid);
}

char	**read_map(char *filename)
{
	int		fd;
	int		lines;
	char	**grid;
	
	lines = count_map_lines(filename);
	if (lines <= 0)
		error_exit("Map is empty or invalid.\n");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Cannot open map file.\n");
	grid = fill_grid_from_file(fd, lines);
	close(fd);
	if (!grid)
		error_exit("Failed to read map content.\n");
	return (grid);
}
