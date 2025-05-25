/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 02:21:43 by yufli             #+#    #+#             */
/*   Updated: 2025/05/25 21:50:22 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	// 检查命令行参数
	if (argc != 2)
	{
		printf("Error\nUsage: %s <map_file.ber>\n", argv[0]);
		return (1);
	}

	// 检查地图文件扩展名
	if (!strstr(argv[1], ".ber") || strstr(argv[1], ".ber")[4] != '\0')
	{
		printf("Error\nMap file must have .ber extension\n");
		return (1);
	}

	// 初始化游戏数据
	if (!init_game(&game))
	{
		printf("Error\nFailed to initialize game\n");
		return (1);
	}

	// 解析地图
	if (!parse_map(&game, argv[1]))
	{
		printf("Error\nFailed to parse map\n");
		free_game(&game);
		return (1);
	}

	// 验证地图
	if (!validate_map(&game))
	{
		printf("Error\nInvalid map\n");
		free_game(&game);
		return (1);
	}

	// 初始化窗口和图像
	if (!init_window(&game) || !init_images(&game))
	{
		printf("Error\nFailed to initialize window or images\n");
		free_game(&game);
		return (1);
	}

	// 渲染游戏
	render_game(&game);

	// 设置键盘钩子
	mlx_key_hook(game.win, key_handler, &game);
	// 设置关闭窗口钩子
	mlx_hook(game.win, 17, 0, close_game, &game);

	// 启动游戏循环
	mlx_loop(game.mlx);

	return (0);
}
