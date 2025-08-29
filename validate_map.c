/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 09:30:57 by yufli             #+#    #+#             */
/*   Updated: 2025/08/29 09:33:24 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	validate_map(t_map *map)
{
	if (!check_rectangle(map))
		error_exit("Error: Map is not rectangular\n");
	if (!check_walls(map))
		error_exit("Error: Map is not surrounded by walls\n");
	if (!check_elements(map))
		error_exit("Error: Map has invalid or missing required elements\n");
	if (!check_path(*map))
		error_exit("Error: No valid path found in the map\n");
	return (1);
}
