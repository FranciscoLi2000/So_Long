/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 11:20:53 by yufli             #+#    #+#             */
/*   Updated: 2025/06/08 17:44:22 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

/* Libraries */
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <mlx.h>
# include <mlx_int.h>

/* Constants (Optional for readability) */
# define WALL '1'
# define EMPTY '0'
# define PLAYER 'P'
# define EXIT 'E'
# define COLLECTIBLE 'C'
# define TILE_SIZE 64

/* Structs */

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

typedef struct s_ff_input
{
	char		**map;
	t_point		size;
	t_point		start;
	int			*collections;
	int			*found_exit;
}	t_ff_input;

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
}	t_game;

/* Map parsing & validation */
char	**read_map(char *filename);
int		validate_map(t_map *map);
int		check_rectangle(t_map *map);
int		check_walls(t_map *map);
int		check_elements(t_map *map);
int		check_cell(t_map *map, int i, int j);
int		check_path(t_map map);

/* Flood fill */
void	start_flood_fill(t_ff_input input);

/* Utilities */
char	**duplicate_map(char **src);
void	free_map_copy(char **map);
t_point	find_player(char **map);
int		count_collectibles(char **map);

/* Error handling */
void	error_exit(char *msg);

#endif
