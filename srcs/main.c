/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 02:21:43 by yufli             #+#    #+#             */
/*   Updated: 2025/05/25 02:56:30 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* 主函数 */

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		write(1, "Error\n", 6);
		write(1, "Usage: <map_file.ber>\n", 22);
		return (1);
	}
	return (0);
}
