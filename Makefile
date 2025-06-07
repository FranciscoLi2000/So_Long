# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/07 16:00:11 by yufli             #+#    #+#              #
#    Updated: 2025/06/07 19:02:53 by yufli            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= so_long

CC		= cc
CFLAGS		= -Wall -Wextra -Werror
RM		= rm -f

SRCS_DIR	= srcs
INCS_DIR	= includes
LIBFT_DIR	= libft
MLX_DIR		= minilibx_linux

LIBFT		= $(LIBFT_DIR)/libft.a
MLX		= $(MLX_DIR)/libmlx.a

INCS		= -I$(INCS_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

SRCS_FILES	= flood_fill.c game_events.c game_init.c game_logic.c \
		game_render.c main.c map_parser.c map_validator.c

SRCS		= $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
OBJS		= $(SRCS:.c=.o)

LIBS		= -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(MLX)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
