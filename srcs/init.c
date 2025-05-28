/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 02:22:25 by yufli             #+#    #+#             */
/*   Updated: 2025/05/29 00:42:14 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
** Initialize map data
*/
void	init_map_data(t_map *map)
{
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
	map->collectibles = 0;
	map->exits = 0;
	map->players = 0;
	map->player_pos.x = 0;
	map->player_pos.y = 0;
	map->start_pos.x = 0;
	map->start_pos.y = 0;
}

/*
** Initialize game data
*/
int	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = NULL;
	game->collected = 0;
	game->moves = 0;
	game->game_state = GAME_RUNNING;
	init_map_data(&game->map);
	return (1);
}

/*
** Initialize game window
*/
int	init_window(t_game *game)
{
	int	win_width;
	int	win_height;

	win_width = game->map.width * IMG_SIZE;
	win_height = game->map.height * IMG_SIZE;
	game->win = mlx_new_window(game->mlx, win_width, win_height,
		"Jackie Chan: Escape the British Museum");
	if (!game->win)
		return (0);
	return (1);
}

/*
** Load single image with error checking
*/
static int	load_image(t_game *game, t_img *img, char *path)
{
	int	width;
	int	height;

	img->img = mlx_xpm_file_to_image(game->mlx, path, &width, &height);
	if (!img->img)
		return (0);
	img->width = width;
	img->height = height;
	return (1);
}

/*
** Initialize game images
*/
int	init_images(t_game *game)
{
	if (!load_image(game, &game->img_player, "textures/player.xpm"))
		return (0);
	if (!load_image(game, &game->img_wall, "textures/wall.xpm"))
		return (0);
	if (!load_image(game, &game->img_collectible, "textures/collectible.xpm"))
		return (0);
	if (!load_image(game, &game->img_exit, "textures/exit.xpm"))
		return (0);
	if (!load_image(game, &game->img_floor, "textures/floor.xpm"))
		return (0);
	return (1);
}
