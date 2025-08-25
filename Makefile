# ========= CONFIG ============
NAME		= so_long

CC		= cc
CFLAGS		= -Wall -Wextra -Werror

MLX_DIR		= ./minilibx_linux
MLX_LIB		= $(MLX_DIR)/libmlx.a
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -lXext -lX11
MLX_INC		= -I$(MLX_DIR)

SRCS		= \
		main.c init_game.c render_map.c draw_tile.c input.c \
		read_map.c check_path.c validate_map.c check_rectangle.c \
		check_elements.c check_walls.c flood_fill.c \
		error_exit.c free_map.c count_lines.c ft_strlen.c exit.c

OBJS		= $(SRCS:.c=.o)

INCLUDES	= so_long.h

# ========= RULES =============
all: $(MLX_LIB) $(NAME)

$(MLX_LIB):
	@make -C $(MLX_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) $(MLX_INC) -c $< -o $@

# ========= CLEANING ==========
clean:
	rm -f $(OBJS)
	@make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
