/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 02:21:43 by yufli             #+#    #+#             */
/*   Updated: 2025/05/28 22:16:46 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;
	int		len;

	if (argc != 2)
	{
		ft_printf("Error\nUsage: %s <map_file.ber>\n", argv[0]);
		return (1);
	}
	len = ft_strlen(argv[1]);
	if (!ft_strnstr(argv[1], ".ber", len)
		|| ft_strnstr(argv[1], ".ber", len)[4] != '\0')
	{
		ft_printf("Error\nMap file must have .ber extension\n");
		return (1);
	}
	if (!init_game(&game))
	{
		ft_printf("Error\nFailed to initialize game\n");
		return (1);
	}
	if (!parse_map(&game, argv[1]))
	{
		ft_printf("Error\nFailed to parse map\n");
		free_game(&game);
		return (1);
	}
	if (!validate_map(&game))
	{
		ft_printf("Error\nInvalid map\n");
		free_game(&game);
		return (1);
	}
	if (!init_window(&game) || !init_images(&game))
	{
		ft_printf("Error\nFailed to initialize window or images\n");
		free_game(&game);
		return (1);
	}
	render_game(&game);
	mlx_key_hook(game.win, key_handler, &game);
	mlx_hook(game.win, 17, 0, close_game, &game);
	mlx_loop(game.mlx);
	return (0);
}
