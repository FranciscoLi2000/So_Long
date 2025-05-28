/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 02:25:27 by yufli             #+#    #+#             */
/*   Updated: 2025/05/29 00:34:58 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
** Error exit function
*/
void	error_exit(char *message)
{
	ft_printf("Error\n%s\n", message);
	exit(1);
}

/*
** Free game resources function
*/
void	free_game(t_game *game)
{
	if (game->map.grid)
		free_map(&game->map);
	if (game->img_player.img)
		mlx_destroy_image(game->mlx, game->img_player.img);
	if (game->img_wall.img)
		mlx_destroy_image(game->mlx, game->img_wall.img);
	if (game->img_collectible.img)
		mlx_destroy_image(game->mlx, game->img_collectible.img);
	if (game->img_exit.img)
		mlx_destroy_image(game->mlx, game->img_exit.img);
	if (game->img_floor.img)
		mlx_destroy_image(game->mlx, game->img_floor.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

/*
** Close game function
*/
int	close_game(t_game *game)
{
	free_game(game);
	exit(0);
	return (0);
}

/*
** Keyboard event handler function
*/
int	key_handler(int keycode, t_game *game)
{
	if (game->game_state != GAME_RUNNING && keycode != KEY_ESC)
		return (0);
	if (keycode == KEY_ESC)
		close_game(game);
	else if (keycode == KEY_W || keycode == KEY_UP)
		move_player(game, keycode);
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		move_player(game, keycode);
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		move_player(game, keycode);
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		move_player(game, keycode);
	return (0);
}
