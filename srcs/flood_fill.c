/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 21:52:55 by yufli             #+#    #+#             */
/*   Updated: 2025/05/25 21:54:18 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Assignment name  : flood_fill
Expected files   : *.c, *.h
Allowed functions: -
--------------------------------------------------------------------------------
Write a function that takes a char ** as a 2-dimensional array of char, a 
t_point as the dimensions of this array and a t_point as the starting point.
Starting from the given 'begin' t_point, this function fills an entire zone 
by replacing characters inside with the character 'F'. A zone is an group of 
the same character delimitated horizontally and vertically by other characters
or the array boundry.
The flood_fill function won't fill diagonally.
The flood_fill function will be prototyped like this:
  void  flood_fill(char **tab, t_point size, t_point begin);
The t_point structure is prototyped like this:
  typedef struct  s_point
  {
    int           x;
    int           y;
  }               t_point;
Example:
$> cat test_main.c
#include "test_functions.h"
#include "flood_fill.h"
int main(void)
{
	char **area;
	t_point size = {8, 5};
	t_point begin = {2, 2};
	char *zone[] = {
		"1 1 1 1 1 1 1 1",
		"1 0 0 0 1 0 0 1",
		"1 0 0 1 0 0 0 1",
		"1 0 1 1 0 0 0 1",
		"1 1 1 0 0 0 0 1",
	}
	area = make_area(zone);
	print_tab(area);
	flood_fill(area, size, begin);
	putc('\n');
	print_tab(area);
	return (0);
}
$> gcc flood_fill.c test_main.c test_functions.c -o flood_fill; ./flood_fill
1 1 1 1 1 1 1 1
1 0 0 0 1 0 0 1
1 0 0 1 0 0 0 1
1 0 1 0 0 0 0 1
1 1 0 0 0 0 0 0
1 1 1 1 1 1 1 1
1 F F F 1 0 0 1
1 F F 1 0 0 0 1
1 F 1 0 0 0 0 1
1 1 0 0 0 0 0 0
$> 
------------------------------------------------------------------------------*/

/*
** 创建地图副本用于Flood Fill检查
*/
char **create_map_copy(t_map *map)
{
    char **copy;
    int i;

    copy = (char **)malloc(sizeof(char *) * (map->height + 1));
    if (!copy)
        return (NULL);
    i = 0;
    while (i < map->height)
    {
        copy[i] = strdup(map->grid[i]);
        if (!copy[i])
        {
            while (--i >= 0)
                free(copy[i]);
            free(copy);
            return (NULL);
        }
        i++;
    }
    copy[i] = NULL;
    return (copy);
}

/*
** Flood Fill算法实现
*/
void flood_fill(char **map, int height, int width, t_pos pos)
{
    // 检查边界条件
    if (pos.y < 0 || pos.y >= height || pos.x < 0 || pos.x >= width)
        return;

    // 如果当前位置是墙或已经被访问过，则返回
    if (map[pos.y][pos.x] == '1' || map[pos.y][pos.x] == 'F')
        return;

    // 标记当前位置为已访问
    map[pos.y][pos.x] = 'F';

    // 递归访问上下左右四个方向
    t_pos up = {pos.x, pos.y - 1};
    t_pos down = {pos.x, pos.y + 1};
    t_pos left = {pos.x - 1, pos.y};
    t_pos right = {pos.x + 1, pos.y};

    flood_fill(map, height, width, up);
    flood_fill(map, height, width, down);
    flood_fill(map, height, width, left);
    flood_fill(map, height, width, right);
}

/*
** 检查地图是否有效（所有收集品和出口都可达）
*/
int check_map_valid_path(t_game *game)
{
    char **map_copy;
    int i, j;
    int valid = 1;

    // 创建地图副本
    map_copy = create_map_copy(&game->map);
    if (!map_copy)
        return (0);

    // 从玩家位置开始进行Flood Fill
    flood_fill(map_copy, game->map.height, game->map.width, game->map.player_pos);

    // 检查所有收集品和出口是否都被标记为可达
    for (i = 0; i < game->map.height; i++)
    {
        for (j = 0; j < game->map.width; j++)
        {
            if (game->map.grid[i][j] == 'C' || game->map.grid[i][j] == 'E')
            {
                if (map_copy[i][j] != 'F')
                {
                    valid = 0;
                    break;
                }
            }
        }
        if (!valid)
            break;
    }

    // 释放地图副本
    for (i = 0; i < game->map.height; i++)
        free(map_copy[i]);
    free(map_copy);

    return (valid);
}
