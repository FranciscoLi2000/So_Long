/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 11:15:21 by yufli             #+#    #+#             */
/*   Updated: 2025/06/12 14:11:04 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	move_player(t_game *g, int dx, int dy)
{
	int		new_x;
	int		new_y;
	char	next_tile;

	new_x = g->map.player_x + dx;
	new_y = g->map.player_y + dy;
	next_tile = g->map.grid[new_y][new_x];
	if (next_tile == WALL)
		return ;
	if (next_tile == COLLECTIBLE)
		g->map.collectibles--;
	if (next_tile == EXIT && g->map.collectibles > 0)
		return ;
	g->map.grid[g->map.player_y][g->map.player_x] = EMPTY;
	g->map.player_x = new_x;
	g->map.player_y = new_y;
	g->map.grid[new_y][new_x] = PLAYER;
	g->moves++;
	ft_printf("Moves: %d\n", g->moves);
	if (next_tile == EXIT && g->map.collectibles == 0)
	{
		ft_printf("Jackie Chan won in %d moves!\n", ++g->moves);
		mlx_destroy_window(g->mlx, g->win);
		exit(0);
	}
	render_map(g);
}

int	handle_key(int key, t_game *g)
{
	if (key == 65307)
	{
		ft_printf("Game Over\n");
		ft_printf("Window Closed\n");
		exit(0);
	}
	if (g->win_status)
		return (0);
	else if (key == 'w' || key == 'W')
		move_player(g, 0, -1);
	else if (key == 's' || key == 'S')
		move_player(g, 0, 1);
	else if (key == 'a' || key == 'A')
		move_player(g, -1, 0);
	else if (key == 'd' || key == 'D')
		move_player(g, 1, 0);
	return (0);
}
