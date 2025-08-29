/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 10:05:05 by yufli             #+#    #+#             */
/*   Updated: 2025/08/29 10:06:48 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_exit(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	ft_putstr_fd("Game closed with [X]\n", 1);
	clean_exit(game);
	return (0);
}
