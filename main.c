/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 11:17:30 by yufli             #+#    #+#             */
/*   Updated: 2025/08/29 09:54:50 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
/*
static int	has_ber_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
        return (len > 4 && ft_strncmp(filename + len - 4, ".ber", 4) == 0);
}*/

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		error_exit("Usage: ./so_long map.ber\n");
	game.map.grid = read_map(argv[1]);
	if (!game.map.grid)
		error_exit("Error: Failed to read map\n");
//	if (!has_ber_extension(argv[1]))
//		error_exit("Error: Map file must have .ber extension\n");
	game.map.height = count_lines(game.map.grid);
	game.map.width = ft_strlen(game.map.grid[0]);
	game.map.players = 0;
	game.map.exits = 0;
	game.map.collectibles = 0;
	validate_map(&game.map);
	init_game(&game);
	render_map(&game);
	mlx_hook(game.win, 2, 1L << 0, handle_key, &game);
	mlx_hook(game.win, 17, 0, handle_exit, &game);
	mlx_loop(game.mlx);
	return (0);
}
