#include "so_long.h"

void	try_move(t_game *g, int new_x, int new_y)
{
	char	next_tile;

	next_tile = g->map.grid[new_y][new_x];
	if (next_tile == WALL)
		return ;
	// 如果是 Collectible
	if (next_tile == COLLECTIBLE)
		g->map.collectibles--;
	// 如果是 Exit 且已收集完所有 C
	if (next_tile == EXIT)
	{
		if (g->map.collectibles == 0)
		{
			g->moves++;
			ft_putstr_fd("You win in ", 1);
			ft_putnbr_fd(g->moves, 1);
			ft_putstr_fd(" moves!\n", 1);
			g->win_status = 1;
			handle_exit(g);
		}
		return ;
	}
	// 替换旧位置为 EMPTY
	g->map.grid[g->map.player_y][g->map.player_x] = EMPTY;
	// 更新新位置为 PLAYER
	g->map.grid[new_y][new_x] = PLAYER;
	// 更新 player 坐标
	g->map.player_x = new_x;
	g->map.player_y = new_y;
	g->moves++;
	ft_putstr_fd("Moves: ", 1);
	ft_putnbr_fd(g->moves, 1);
	ft_putchar_fd('\n', 1);
	render_map(g);
}

int	handle_key(int key, t_game *g)
{
	int	x;
	int	y;

	x = g->map.player_x;
	y = g->map.player_y;
	if (key == 53)		// ESC 退出
		handle_exit(g);
	else if (key == 13)	// W 上
		try_move(g, x, y - 1);
	else if (key == 1)	// S 下
		try_move(g, x, y + 1);
	else if (key == 0)	// A 左
		try_move(g, x - 1, y);
	else if (key == 2)	// D 右
		try_move(g, x + 1, y);
	return (0);
}
