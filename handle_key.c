/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 11:15:21 by yufli             #+#    #+#             */
/*   Updated: 2025/08/29 11:20:11 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_key(int key, t_game *game)
{
	if (key == 65307)
	{
		ft_putstr_fd("Game Over\n", 1);
		clean_exit(game);
	}
	if (key == 'w' || key == 'W')
		move_player(game, 0, -1);
	else if (key == 's' || key == 'S')
		move_player(game, 0, 1);
	else if (key == 'a' || key == 'A')
		move_player(game, -1, 0);
	else if (key == 'd' || key == 'D')
		move_player(game, 1, 0);
	return (0);
}
