/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:52:16 by yufli             #+#    #+#             */
/*   Updated: 2025/06/07 21:54:06 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* 初始化地图数据 */
void	init_map_data(t_map *map)
{
	map->collectibles = 0;
	map->exits = 0;
	map->players = 0;
	map->collected = 0;
	map->player_x = 0;
	map->player_y = 0;
	map->exit_x = 0;
	map->exit_y = 0;
}

/* 加载XPM图像 */
static void	*load_xpm_image(void *mlx, char *path, int *width, int *height)
{
	void	*img;

	img = mlx_xpm_file_to_image(mlx, path, width, height);
	if (!img)
		error_exit("Failed to load image");
	return (img);
}

/* 加载游戏所需的所有图像 */
int	load_images(t_game *game)
{
	game->img_player.img = load_xpm_image(game->mlx,
	"../textures/player.xpm", &game->img_player.width, &game->img_player.height);
	game->img_wall.img = load_xpm_image(game->mlx,
	"../textures/wall.xpm", &game->img_wall.width, &game->img_wall.height);
	game->img_collectible.img = load_xpm_image(game->mlx,
	"../textures/collectible.xpm", &game->img_collectible.width, &game->img_collectible.height);
	game->img_exit.img = load_xpm_image(game->mlx,
	"../textures/exit.xpm", &game->img_exit.width, &game->img_exit.height);
	game->img_floor.img = load_xpm_image(game->mlx,
	"../textures/floor.xpm", &game->img_floor.width, &game->img_floor.height);
	if (!game->img_player.img || !game->img_wall.img
		|| !game->img_collectible.img || !game->img_exit.img
		|| !game->img_floor.img)
		return (0);
	return (1);
}

/* 初始化游戏 */
int	init_game(t_game *game)
{
	int	window_width;
	int	window_height;

	window_width = game->map.width * TILE_SIZE;
	window_height = game->map.height * TILE_SIZE;
	game->win = mlx_new_window(game->mlx, window_width,
				window_height, WINDOW_TITLE);
	if (!game->win)
	{
		error_exit("Failed to create window");
		return (0);
	}
	if (!load_images(game))
	{
		error_exit("Failed to load images");
		return (0);
	}
	game->moves = 0;
	game->game_over = 0;
	return (1);
}
