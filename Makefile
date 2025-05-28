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

NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Directories
SRCDIR = srcs
INCDIR = includes
OBJDIR = objs

# Source files
SRCS = $(SRCDIR)/main.c \
       $(SRCDIR)/init.c \
       $(SRCDIR)/map.c \
       $(SRCDIR)/render.c \
       $(SRCDIR)/player.c \
       $(SRCDIR)/flood_fill.c \
       $(SRCDIR)/utils.c

# Object files
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Libraries
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = minilibx_linux
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib/X11 -lXext -lX11 -lm

# Include directories
INCLUDES = -I$(INCDIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

# Colors for pretty output
GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
RESET = \033[0m

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJDIR) $(OBJS)
	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) created successfully!$(RESET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(LIBFT):
	@echo "$(GREEN)Building libft...$(RESET)"
	@make -C $(LIBFT_DIR)

$(MLX):
	@echo "$(GREEN)Building MLX...$(RESET)"
	@make -C $(MLX_DIR)

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJDIR)
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean

fclean: clean
	@echo "$(RED)Cleaning $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

# Norminette check
norm:
	@echo "$(YELLOW)Checking norminette...$(RESET)"
	@norminette $(SRCDIR) $(INCDIR)

# Test with sample map
test: $(NAME)
	./$(NAME) maps/map1.ber

# Debug version
debug: CFLAGS += -fsanitize=address -g3
debug: re

.PHONY: all clean fclean re norm test debug
