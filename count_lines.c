#include "so_long.h"

int	count_lines(char **grid)
{
	int	i;

	i = 0;
	while (grid[i])
		i++;
	return (i);
}
