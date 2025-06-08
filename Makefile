# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/08 17:23:02 by yufli             #+#    #+#              #
#    Updated: 2025/06/08 19:13:23 by yufli            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= so_long

# Directories
SRC_DIR		= srcs
INC_DIR		= includes
LIBFT_DIR	= libft
MLX_DIR		= minilibx_linux

INCLUDE		= -I$(INC_DIR) -I$(LIBFT_DIR)/includes -I$(MLX_DIR)
MLXFLAGS	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Source files
SRCS		= $(SRC_DIR)/map.c \
		$(SRC_DIR)/map_utils_1.c \
		$(SRC_DIR)/map_utils_2.c \
		$(SRC_DIR)/flood_fill.c \
		$(SRC_DIR)/init.c \
		$(SRC_DIR)/render.c \
		$(SRC_DIR)/utils.c \
		$(SRC_DIR)/move.c \
		$(SRC_DIR)/main.c

OBJS		= $(SRCS:.c=.o)

CC		= cc
CFLAGS		= -Wall -Wextra -Werror $(INCLUDE)

LIBFT		= $(LIBFT_DIR)/libft.a

# Colors
GREEN		= \033[1;32m
RED		= \033[1;31m
YELLOW		= \033[1;33m
RESET		= \033[0m

all: $(LIBFT) $(NAME)

$(LIBFT):
	@echo "$(YELLOW)Compiling libft...$(RESET)"
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLXFLAGS) -o $(NAME)
	@echo "$(GREEN)Compilation successful: $(NAME)$(RESET)"

clean:
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@echo "$(YELLOW)Temporary object files cleaned.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "$(RED)Executable and objects removed.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
