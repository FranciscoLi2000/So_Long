/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 11:17:30 by yufli             #+#    #+#             */
/*   Updated: 2025/06/08 19:42:39 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* ESC 和窗口关闭时释放资源退出 */
/* 错误退出函数 打印错误信息并退出程序 */
void	error_exit(char *message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

static void	debug_print_map_info(t_map *map)
{
	ft_printf("Map size: %d x %d\n", map->width, map->height);
	ft_printf("Player pos: %d,%d\n", map->player_x, map->player_y);
	ft_printf("Collectibles: %d\n", map->collectibles);
	ft_printf("Exit pos: %d,%d\n", map->exit_x, map->exit_y);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		error_exit("Usage: ./so_long map.ber");
	game.map.grid = read_map(argv[1]);
	game.map.height = count_lines(game.map.grid);
	game.map.width = ft_strlen(game.map.grid[0]);
	game.map.players = 0;
	game.map.exits = 0;
	game.map.collectibles = 0;
	if (!validate_map(&game.map))
		error_exit("Invalid map");
	debug_print_map_info(&game.map);
	init_game(&game);
	render_map(&game);
	mlx_hook(game.win, 2, 1L << 0, handle_key, &game);
	mlx_hook(game.win, 17, 0, handle_exit, NULL);
	mlx_loop(game.mlx);
	return (0);
}
