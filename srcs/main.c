/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:10:34 by yufli             #+#    #+#             */
/*   Updated: 2025/06/07 21:17:52 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* 错误退出函数 打印错误信息并退出程序 */
void	error_exit(char *message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

/* 清理并退出函数 释放资源并退出程序 */
void	clean_exit(t_game *game, int status)
{
	if (game->map.grid)
		free_map(&game->map);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(status);
}

/* 主函数 初始化游戏并启动主循环 */
int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		error_exit("Usage: ./so_long <map_file.ber>");
		return (EXIT_FAILURE);
	}
	ft_bzero(&game, sizeof(t_game));
	game.mlx = mlx_init();
	if (!game.mlx)
		error_exit("Cannot initialize MLX");
	if (!parse_map(&game, argv[1]))
		clean_exit(&game, EXIT_FAILURE);
	if (!validate_map(&game.map))
		clean_exit(&game, EXIT_FAILURE);
	if (!init_game(&game))
		clean_exit(&game, EXIT_FAILURE);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	render_game(&game);
	mlx_loop(game.mlx);
	return (0);
}
