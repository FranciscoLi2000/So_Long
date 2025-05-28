# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/28 20:22:00 by yufli             #+#    #+#              #
#    Updated: 2025/05/28 22:38:33 by yufli            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= so_long

# 编译器和编译选项
CC		= cc
CFLAGS		= -Wall -Wextra -Werror -g

# 目录
SRC_DIR		= srcs
INC_DIR 	= includes
LIBFT_DIR	= libft
MLX_DIR		= minilibx_linux

# 源文件
SRC_FILES	= main.c init.c map.c render.c player.c \
		enemy.c utils.c flood_fill.c
SRCS		= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS		= $(SRCS:.c=.o)

# 头文件
INCLUDES	= -I$(INC_DIR) -I$(MLX_DIR)

# 库
LIBFT		= $(LIBFT_DIR)/libft.a
MLX		= $(MLX_DIR)/libmlx_Linux.a
LIBS		= -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm

# 规则
all: $(NAME)

# 编译libft
$(LIBFT):
	@echo "Compiling libft..."
	@make -C $(LIBFT_DIR)

# 编译minilibx
$(MLX):
	@echo "Compiling minilibx..."
	@make -C $(MLX_DIR)

# 编译目标文件
%.o: %.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# 编译最终可执行文件
$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@echo "Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(NAME) compiled successfully!"

# 清理目标文件
clean:
	@echo "Cleaning object files..."
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean

# 清理所有生成的文件
fclean: clean
	@echo "Cleaning executable and libraries..."
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

# 重新编译
re: fclean all

# 运行游戏（使用默认地图）
run: all
	@echo "Running $(NAME) with default map..."
	@./$(NAME) maps/map1.ber

# 检查内存泄漏
valgrind: all
	@echo "Running valgrind on $(NAME)..."
	@valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) maps/map1.ber

.PHONY: all clean fclean re run valgrind
