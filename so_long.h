#ifndef SO_LONG_H
# define SO_LONG_H

/* ========== standard libs & 42 ========== */
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "mlx.h"

/* ========== tile types ========== */
# define WALL '1'
# define EMPTY '0'
# define PLAYER 'P'
# define EXIT 'E'
# define COLLECTIBLE 'C'
# define TILE_SIZE 64

# define KEY_UP    13
# define KEY_DOWN  1
# define KEY_LEFT  0
# define KEY_RIGHT 2
# define KEY_ESC   53

/* ========== structures ========== */
typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_map
{
	char	**grid;			/* 原始地图字符网格 */
	int		width;		/* 地图宽度（列数）*/
	int		height;		/* 地图高度（行数）*/
	int		player_x;	/* 玩家起始 X 坐标 */
	int		player_y;	/* 玩家起始 Y 坐标 */
	int		exit_x;		/* 出口 X 坐标 */
	int		exit_y;		/* 出口 Y 坐标 */
	int		players;	/* 地图中 P 的数量 */
	int		exits;		/* 地图中 E 的数量 */
	int		collectibles;	/* 地图中 C 的数量 */
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
	void	*img_enemy;
	void	*img_ui_panel;
	int		frame_count;
	int		moves;
	int		win_status;
}	t_game;

typedef struct s_ff_input
{
	char	**map;			// 地图拷贝
	t_point		size;		// 地图尺寸
	t_point		start;		// 起始点坐标（P）
	int			*coins;	// 遇到的 C 数量
	int			*found_exit;	// 是否遇到过 E
}	t_ff_input;

/* ========== utils ========== */
void	error_exit(char *msg);
int		count_lines(char **grid);
void	free_split(char **strs);
int		str_ends_with(const char *str, const char *suffix);
int		is_valid_file(const char *filename);

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
void	flood_fill(t_ff_input *input);

#endif
