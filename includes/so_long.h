/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:04:18 by yufli             #+#    #+#             */
/*   Updated: 2025/05/29 00:26:45 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include "../minilibx_linux/mlx.h"

/* Key codes used in the game */
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_DOWN 65364
# define KEY_RIGHT 65363

/* Game elements */
# define EMPTY '0'
# define WALL '1'
# define COLLECTIBLE 'C'
# define EXIT 'E'
# define PLAYER 'P'

/* Image size */
# define IMG_SIZE 32

/* Game states */
# define GAME_RUNNING 0
# define GAME_WIN 1
# define GAME_LOSE 2

/* Position structure */
typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

/* Image structure */
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

/* Game map structure */
typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		collectibles;
	int		exits;
	int		players;
	t_pos	player_pos;
	t_pos	start_pos;
}	t_map;

/* Game structure */
typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_map	map;
	t_img	img_player;
	t_img	img_wall;
	t_img	img_collectible;
	t_img	img_exit;
	t_img	img_floor;
	int		collected;
	int		moves;
	int		game_state;
}	t_game;

/* Initialization functions */
int		init_game(t_game *game);
int		init_window(t_game *game);
int		init_images(t_game *game);
void	init_map_data(t_map *map);

/* Map handling functions */
int		parse_map(t_game *game, char *filename);
int		validate_map(t_game *game);
void	free_map(t_map *map);

/* Rendering functions */
void	render_game(t_game *game);
void	render_map(t_game *game);
void	render_player(t_game *game);
void	render_ui(t_game *game);

/* Player functions */
int		move_player(t_game *game, int key);
int		check_collision(t_game *game, int x, int y);
void	collect_item(t_game *game, int x, int y);
int		check_exit(t_game *game);
void	reset_player(t_game *game);

/* Utility functions */
void	error_exit(char *message);
int		key_handler(int keycode, t_game *game);
int		close_game(t_game *game);
void	free_game(t_game *game);

#endif
