#include "so_long.h"

char	**read_map(char *filename)
{
	char	*line;
	char	*content;
	char	*tmp;
	char	**grid;
	int		fd;

	content = NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Cannot open map file.");
	while ((line = get_next_line(fd)))
	{
		tmp = content;
		content = ft_strjoin(tmp, line);
		free(tmp);
		free(line);
	}
	close(fd);
	grid = ft_split(content, '\n');
	free(content);
	return (grid);
}
