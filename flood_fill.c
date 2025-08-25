#include "so_long.h"

void	flood_fill(t_ff_input *in, int x, int y)
{
	char	tile;

	if (x < 0 || y < 0 || x >= in->size.x || y >= in->size.y)
		return ;
	/* 1. 从 start 点出发 */
	tile = in->map[y][x];
	/* 2. 如果当前位置不是墙（WALL = ‘1’）也没被访问过 */
	if (tile == WALL || tile == 'F')
		return ;
	/* 3. 如果是 C，就 (*coins)-- */
	if (tile == COLLECTIBLE)
		(*in->coins)--;
	/* 4. 如果是 E，就 *found_exit = 1 */
	if (tile == EXIT)
		*in->found_exit = 1;
	/* 5. 将当前位置标记为“已访问” */
	in->map[y][x] = 'F';
	/* 6. 对上下左右递归调用 flood_fill() */
	flood_fill(in, x + 1, y);
	flood_fill(in, x - 1, y);
	flood_fill(in, x, y + 1);
	flood_fill(in, x, y - 1);
}
