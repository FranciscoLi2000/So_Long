# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/29 11:15:25 by yufli             #+#    #+#              #
#    Updated: 2025/08/29 11:28:05 by yufli            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nombre del ejecutable
NAME = so_long

# Directorios de los archivos fuente
SRCS_DIR = .
MLX_DIR = minilibx_linux

# Archivos fuente del proyecto, listados de manera explícita
SRCS = \
	$(SRCS_DIR)/check_cell.c \
	$(SRCS_DIR)/check_elements.c \
	$(SRCS_DIR)/check_path.c \
	$(SRCS_DIR)/check_rectangle.c \
	$(SRCS_DIR)/check_walls.c \
	$(SRCS_DIR)/clean_exit.c \
	$(SRCS_DIR)/count_collectibles.c \
	$(SRCS_DIR)/count_lines.c \
	$(SRCS_DIR)/error_exit.c \
	$(SRCS_DIR)/find_player.c \
	$(SRCS_DIR)/flood_fill.c \
	$(SRCS_DIR)/ft_memcpy.c \
	$(SRCS_DIR)/ft_putchar_fd.c \
	$(SRCS_DIR)/ft_putnbr_fd.c \
	$(SRCS_DIR)/ft_putstr_fd.c \
	$(SRCS_DIR)/ft_strchr.c \
	$(SRCS_DIR)/ft_strcpy.c \
	$(SRCS_DIR)/ft_strdup.c \
	$(SRCS_DIR)/ft_strjoin_free.c \
	$(SRCS_DIR)/ft_strlen.c \
	$(SRCS_DIR)/get_next_line.c \
	$(SRCS_DIR)/handle_exit.c \
	$(SRCS_DIR)/handle_key.c \
	$(SRCS_DIR)/init_game.c \
	$(SRCS_DIR)/init_window.c \
	$(SRCS_DIR)/load_images.c \
	$(SRCS_DIR)/main.c \
	$(SRCS_DIR)/move_player.c \
	$(SRCS_DIR)/read_map.c \
	$(SRCS_DIR)/render_map.c \
	$(SRCS_DIR)/validate_map.c

# Archivos de objeto, se generan a partir de los archivos fuente
OBJS = $(SRCS:.c=.o)

# Flags del compilador
CFLAGS = -Wall -Wextra -Werror -g

# Flags de la biblioteca MiniLibX
LDFLAGS = -Lminilibx_linux -lmlx -lXext -lX11

# Regla predeterminada: compilar el ejecutable
all: $(MLX_DIR)/libmlx.a $(NAME)

# Regla para compilar la biblioteca MiniLibX
$(MLX_DIR)/libmlx.a:
	@echo "Compilando MiniLibX..."
	@make -C $(MLX_DIR)

# Regla para enlazar tu programa
$(NAME): $(OBJS)
	@echo "Enlazando archivos de objeto..."
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "¡Compilación exitosa! Ejecutable creado: $(NAME)"

# Regla para compilar los archivos de objeto
%.o: %.c
	@echo "Compilando $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Regla de limpieza para los objetos
clean:
	@echo "Limpiando archivos de objeto..."
	@rm -f $(OBJS)
	@echo "Archivos de objeto eliminados."

# Regla de limpieza total
fclean: clean
	@echo "Limpiando ejecutable..."
	@rm -f $(NAME)
	@echo "Ejecutable eliminado."

# Regla para recompilar
re: fclean all

.PHONY: all clean fclean re
