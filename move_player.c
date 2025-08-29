/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 11:15:21 by yufli             #+#    #+#             */
/*   Updated: 2025/08/29 10:03:19 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	apply_move(t_game *g, int new_x, int new_y, char next_tile)
{
	g->map.grid[g->map.player_y][g->map.player_x] = EMPTY;
	g->map.player_x = new_x;
	g->map.player_y = new_y;
	g->map.grid[new_y][new_x] = PLAYER;
	g->moves++;
	ft_putstr_fd("Moves: ", 1);
	ft_putnbr_fd(g->moves, 1);
	ft_putchar_fd('\n', 1);
	render_map(g);
	if (next_tile == EXIT && g->map.collectibles == 0)
	{
		ft_putstr_fd("Jackie Chan won in ", 1);
		ft_putnbr_fd(g->moves, 1);
		ft_putstr_fd(" moves!\n", 1);
		clean_exit(g);
	}
}

void	move_player(t_game *g, int dx, int dy)
{
	char	next_tile;
	int		new_x;
	int		new_y;

	new_x = g->map.player_x + dx;
	new_y = g->map.player_y + dy;
	if (new_x < 0 || new_x >= g->map.width
		|| new_y < 0 || new_y >= g->map.height)
		return ;
	next_tile = g->map.grid[new_y][new_x];
	if (next_tile == WALL)
		return ;
	if (next_tile == COLLECTIBLE)
		g->map.collectibles--;
	if (next_tile == EXIT && g->map.collectibles > 0)
		return ;
	apply_move(g, new_x, new_y, next_tile);
}
