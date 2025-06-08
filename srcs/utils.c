/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:15:34 by yufli             #+#    #+#             */
/*   Updated: 2025/06/09 00:59:04 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_lines(char **grid)
{
	int	i;

	i = 0;
	while (grid[i])
		i++;
	return (i);
}

int	handle_exit(void *param)
{
	(void)param;
	ft_printf("Game closed with [X]\n");
	exit(0);
}
