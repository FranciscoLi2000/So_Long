# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/08 17:23:02 by yufli             #+#    #+#              #
#    Updated: 2025/06/09 03:24:10 by yufli            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yufli <yufli@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/08 17:23:02 by yufli             #+#    #+#              #
#    Updated: 2025/06/09 22:10:00 by yufli            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# === Project ===

NAME        = so_long

# === Directories ===

SRC_DIR     = srcs
INC_DIR     = includes
LIBFT_DIR   = libft
MLX_DIR     = minilibx_linux

# === Flags ===

INCLUDE     = -I$(INC_DIR) -I$(LIBFT_DIR)/includes -I$(MLX_DIR)
MLXFLAGS    = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
CFLAGS      = -Wall -Wextra -Werror $(INCLUDE)

# === Sources & Objects ===

SRCS        = $(SRC_DIR)/main.c \
              $(SRC_DIR)/init.c \
              $(SRC_DIR)/map.c \
              $(SRC_DIR)/map_utils_1.c \
              $(SRC_DIR)/map_utils_2.c \
              $(SRC_DIR)/flood_fill.c \
              $(SRC_DIR)/render.c \
              $(SRC_DIR)/move.c \
              $(SRC_DIR)/utils.c

OBJS        = $(SRCS:.c=.o)

# === Libraries ===

LIBFT       = $(LIBFT_DIR)/libft.a
MLX         = $(MLX_DIR)/libmlx.a

# === Colors ===

GREEN       = \033[1;32m
YELLOW      = \033[1;33m
RED         = \033[1;31m
RESET       = \033[0m

# === Rules ===

all: $(LIBFT) $(MLX) $(NAME)

$(LIBFT):
	@echo "$(YELLOW)Compiling Libft...$(RESET)"
	@make -C $(LIBFT_DIR)

$(MLX):
	@echo "$(YELLOW)Compiling MiniLibX...$(RESET)"
	@make -C $(MLX_DIR)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLXFLAGS) -o $(NAME)
	@echo "$(GREEN)Compilation successful: $(NAME)$(RESET)"

clean:
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean
	@echo "$(YELLOW)Temporary object files cleaned.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "$(RED)Executable and all objects removed.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
