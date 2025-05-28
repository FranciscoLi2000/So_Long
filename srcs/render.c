/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 02:23:47 by yufli             #+#    #+#             */
/*   Updated: 2025/05/25 02:24:07 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Render single map element */
static void	render_element(t_game *game, int x, int y)
{
	int	pos_x;
	int	pos_y;

	pos_x = x * IMG_SIZE;
	pos_y = y * IMG_SIZE;
	mlx_put_image_to_window(game->mlx, game->win,
		game->img_floor.img, pos_x, pos_y);
	if (game->map.grid[y][x] == WALL)
		mlx_put_image_to_window(game->mlx, game->win,
			game->img_wall.img, pos_x, pos_y);
	else if (game->map.grid[y][x] == COLLECTIBLE)
		mlx_put_image_to_window(game->mlx, game->win,
			game->img_collectible.img, pos_x, pos_y);
	else if (game->map.grid[y][x] == EXIT)
		mlx_put_image_to_window(game->mlx, game->win,
			game->img_exit.img, pos_x, pos_y);
}

/* Render map */
void	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			render_element(game, x, y);
			x++;
		}
		y++;
	}
}

/* Render player */
void	render_player(t_game *game)
{
	int	pos_x;
	int	pos_y;

	pos_x = game->map.player_pos.x * IMG_SIZE;
	pos_y = game->map.player_pos.y * IMG_SIZE;
	mlx_put_image_to_window(game->mlx, game->win,
		game->img_player.img, pos_x, pos_y);
}

/* Render UI (move count information) */
void	render_ui(t_game *game)
{
	char	*moves_str;
	char	*collectibles_str;

	moves_str = ft_itoa(game->moves);
	if (moves_str)
	{
		mlx_string_put(game->mlx, game->win, 10, 20, 0xFFFFFF, "Moves: ");
		mlx_string_put(game->mlx, game->win, 70, 20, 0xFFFFFF, moves_str);
		free(moves_str);
	}
	collectibles_str = ft_itoa(game->collected);
	if (collectibles_str)
	{
		mlx_string_put(game->mlx, game->win, 10, 40, 0xFFFFFF, "Items: ");
		mlx_string_put(game->mlx, game->win, 70, 40, 0xFFFFFF, collectibles_str);
		free(collectibles_str);
	}
	if (game->game_state == GAME_WIN)
		mlx_string_put(game->mlx, game->win,
			game->map.width * IMG_SIZE / 2 - 50,
			game->map.height * IMG_SIZE / 2, 0x00FF00, "You Win!");
}

/* Render entire game */
void	render_game(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	render_map(game);
	render_player(game);
	render_ui(game);
}
