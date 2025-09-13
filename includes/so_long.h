/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 11:20:53 by yufli             #+#    #+#             */
/*   Updated: 2025/08/29 11:20:54 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "minilibx_linux/mlx.h"
# include "minilibx_linux/mlx_int.h"

# define WALL '1'
# define EMPTY '0'
# define PLAYER 'P'
# define EXIT 'E'
# define COLLECTIBLE 'C'
# define TILE_SIZE 64
# define BUFFER_SIZE 42

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

int		check_cell(t_map *map, int i, int j);
int		check_elements(t_map *map);
int		check_path(t_map map);
int		check_rectangle(t_map *map);
int		check_walls(t_map *map);
void	clean_exit(t_game *game);
int		count_collectibles(char **map);
int		count_lines(char **grid);
void	error_exit(char *message);
t_point	find_player(char **map);
void	flood_fill(t_ff_input input);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strchr(const char *s, int c);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strdup(char *src);
char	*ft_strjoin_and_free(char *s1, char *s2);
int		ft_strlen(const char *str);
char	*get_next_line(int fd);
int		handle_exit(void *param);
int		handle_key(int key, t_game *game);
void	init_game(t_game *game);
void	init_window(t_game *game);
void	load_images(t_game *game);
void	move_player(t_game *g, int dx, int dy);
char	**read_map(char *filename);
void	render_map(t_game *g);
int		validate_map(t_map *map);

#endif
