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
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	lines = 0;
	while ((line = get_next_line(fd)))
	{
		lines++;
		free(line);
	}
	close(fd);
	return (lines);
}

static char	*trim_newline(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

static char	**fill_grid_from_file(int fd, int lines)
{
	char	**grid;
	char	*line;
	int		i;

	grid = malloc(sizeof(char *) * (lines + 1));
	if (!grid)
		return (NULL);
	i = 0;
	while (i < lines)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		line = trim_newline(line);
		grid[i++] = line;
	}
	if (i != lines)
	{
		while (--i >= 0)
			free(grid[i]);
		free(grid);
		return (NULL);
	}
	grid[lines] = NULL;
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
