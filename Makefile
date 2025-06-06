# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/04 09:52:32 by yufli             #+#    #+#              #
#    Updated: 2025/06/06 18:59:29 by yufli            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ========== CONFIG ==========
NAME		= libft.a

# Directories
LIB_DIR		= libft
GNL_DIR		= get_next_line
OBJDIR		= obj
INCDIR		= includes

# Source files split by module
LIBFT_FILES	= \
	ft_atoi_base.c ft_isalpha.c ft_isspace.c ft_memmove.c ft_putnbr.c \
	ft_rrange.c ft_strcpy.c ft_strlcat.c ft_strncmp.c ft_strrev.c ft_swap.c max.c \
	ft_atoi.c ft_isascii.c ft_itoa.c ft_memset.c ft_putnbr_fd.c ft_split.c \
	ft_strcspn.c ft_strlcpy.c ft_strncpy.c ft_strspn.c ft_tolower.c print_bits.c \
	ft_bzero.c ft_isdigit.c ft_memchr.c ft_putchar.c ft_putstr.c ft_strcat.c \
	ft_strdup.c ft_strlen.c ft_strnstr.c ft_strstr.c ft_toupper.c reverse_bits.c \
	ft_calloc.c ft_is_prime.c ft_memcmp.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_strchr.c ft_striteri.c ft_strmapi.c ft_strpbrk.c ft_strtrim.c \
	is_power_of_2.c swap_bits.c ft_isalnum.c ft_isprint.c ft_memcpy.c \
	ft_putendl_fd.c ft_range.c ft_strcmp.c ft_strjoin.c ft_strncat.c \
	ft_strrchr.c ft_substr.c lcm.c

GNL_FILES	= get_next_line.c

SRC_FILES	= $(addprefix $(LIB_DIR)/, $(LIBFT_FILES)) \
			  $(addprefix $(GNL_DIR)/, $(GNL_FILES))

OBJ_FILES	= $(addprefix $(OBJDIR)/, $(notdir $(SRC_FILES:.c=.o)))

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I$(INCDIR)
AR			= ar rcs
RM			= rm -rf
MKDIR		= mkdir -p

# ========== COLORS ==========
GREEN	= \033[0;32m
BLUE	= \033[0;34m
RED		= \033[0;31m
RESET	= \033[0m

# ========== RULES ==========

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@echo "$(BLUE)🔧 Archiving $(NAME)...$(RESET)"
	$(AR) $(NAME) $(OBJ_FILES)
	@echo "$(GREEN)Build complete!$(RESET)"

# Compile .c → obj/ .o
$(OBJDIR)/%.o: $(LIB_DIR)/%.c | $(OBJDIR)
	@echo "$(BLUE)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(GNL_DIR)/%.c | $(OBJDIR)
	@echo "$(BLUE)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

# Create obj directory
$(OBJDIR):
	@$(MKDIR) $(OBJDIR)

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	$(RM) $(OBJDIR) $(OBJ_FILES)

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(RESET)"
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
