/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 11:20:53 by yufli             #+#    #+#             */
/*   Updated: 2025/06/09 02:11:50 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

/* ========== standard libs & 42 ========== */
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"

/* ========== tile types ========== */
# define WALL '1'
# define EMPTY '0'
# define PLAYER 'P'
# define EXIT 'E'
# define COLLECTIBLE 'C'
# define TILE_SIZE 64

/* ========== structures ========== */
typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	int		exit_x;
	int		exit_y;
	int		players;
	int		exits;
	int		collectibles;
}	t_map;

typedef struct s_game
{
	t_map	map;
	void	*mlx;
	void	*win;
	void	*img_wall;
	void	*img_floor;
	void	*img_player;
	void	*img_exit;
	void	*img_collect;
	int		moves;
	int		win_status;
}	t_game;

typedef struct s_ff_input
{
	char		**map;
	t_point		size;
	t_point		start;
	int			*coins;
	int			*found_exit;
}	t_ff_input;

/* ========== utils ========== */
void	error_exit(char *msg);
int		count_lines(char **grid);

/* ========== map / parsing ========== */
char	**read_map(char *filename);
int		validate_map(t_map *map);
int		check_rectangle(t_map *map);
int		check_walls(t_map *map);
int		check_elements(t_map *map);
int		check_path(t_map map);
char	**duplicate_map(char **src);
void	free_map_copy(char **map);
int		count_collectibles(char **map);
t_point	find_player(char **map);

/* ========== rendering ========== */
void	init_game(t_game *game);
void	render_map(t_game *game);

/* ========== input events ========== */
int		handle_key(int key, t_game *game);
int		handle_exit(void *param);

/* ========== pathfinding ========== */
void	flood_fill(t_ff_input input);

#endif
