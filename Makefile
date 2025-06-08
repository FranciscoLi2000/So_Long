# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/08 17:23:02 by yufli             #+#    #+#              #
#    Updated: 2025/06/08 17:57:50 by yufli            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= so_long

# Directories
SRC_DIR		= srcs
INC_DIR		= includes
LIBFT_DIR	= libft

# Source files
SRCS		= $(SRC_DIR)/map.c \
		$(SRC_DIR)/map_utils_1.c \
		$(SRC_DIR)/map_utils_2.c \
		$(SRC_DIR)/flood_fill.c \
		$(SRC_DIR)/init.c \
		$(SRC_DIR)/main.c

OBJS		= $(SRCS:.c=.o)

CC		= cc
CFLAGS		= -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR)/includes

LIBFT		= $(LIBFT_DIR)/libft.a

# Colors
GREEN		= \033[1;32m
RED		= \033[1;31m
YELLOW		= \033[1;33m
RESET		= \033[0m

all: $(LIBFT) $(NAME)

$(LIBFT):
	@printf "$(YELLOW)Compiling libft...$(RESET)\n"
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $^ $(LIBFT) -o $(NAME)
	@printf "$(GREEN)Compilation successful: $(NAME)$(RESET)\n"

clean:
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@printf "$(YELLOW)Temporary object files cleaned.$(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@printf "$(RED)Executable and objects removed.$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re
