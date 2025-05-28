# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/28 22:29:28 by yufli             #+#    #+#              #
#    Updated: 2025/05/28 22:36:25 by yufli            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
INCLUDE	= -I../includes
CC	= cc
CFLAGS	= -Wall -Wextra -Werror $(INCLUDE)

SRCS	= ft_atoi.c ft_isprint.c ft_printf.c ft_strdup.c ft_strncmp.c \
	get_next_line.c ft_bzero.c ft_itoa.c ft_putchar_fd.c ft_striteri.c \
	ft_strnstr.c print_char.c ft_calloc.c ft_memchr.c ft_putendl_fd.c \
	ft_strjoin.c ft_strrchr.c print_hex.c ft_isalnum.c ft_memcmp.c \
	ft_putnbr_fd.c ft_strlcat.c ft_strtrim.c print_int.c ft_isalpha.c \
	ft_memcpy.c ft_putstr_fd.c ft_strlcpy.c ft_substr.c print_ptr.c \
	ft_isascii.c ft_memmove.c ft_split.c ft_strlen.c ft_tolower.c \
	print_str.c ft_isdigit.c ft_memset.c ft_strchr.c ft_strmapi.c \
	ft_toupper.c print_uint.c

OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
