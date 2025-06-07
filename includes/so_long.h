/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:05:10 by yufli             #+#    #+#             */
/*   Updated: 2025/06/07 19:17:54 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include "../libft/includes/ft_printf.h"
# include "../minilibx_linux/mlx.h"
# include "../minilibx_linux/mlx_int.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define TILE_SIZE 64
# define WINDOW_TITLE "Jackie Chan: Escape the British Museum"
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define EMPTY '0'
# define WALL '1'
# define COLLECTIBLE 'C'
# define EXIT 'E'
# define PLAYER 'P'

typedef struct s_image
{
	void	*img;
	int		width;
	int		height;
}	t_image;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		collectibles;
	int		exits;
	int		players;
	int		collected;
	int		player_x;
	int		player_y;
	int		exit_x;
	int		exit_y;
}	t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_map	map;
	t_image	img_player;
	t_image	img_wall;
	t_image	img_collectible;
	t_image	img_exit;
	t_image	img_floor;
	int		moves;
	int		game_over;
}	t_game;

int		parse_map(t_game *game, char *filename);
void	free_map(t_map *map);
int		validate_map(t_map *map);
void	flood_fill(char **map, int x, int y, int *count);
int		init_game(t_game *game);
int		load_images(t_game *game);
void	init_map_data(t_map *map);
/* game_render.c */
void	render_game(t_game *game);
void	render_moves(t_game *game);
/* game_events.c */
int		key_press(int keycode, t_game *game);
int		close_window(t_game *game);
/* game_logic.c */
int		move_player(t_game *game, int new_x, int new_y);
void	check_collectible(t_game *game, int x, int y);
void	check_exit(t_game *game);
/* main.c */
void	error_exit(char *message);
void	clean_exit(t_game *game, int status);

#endif
