# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/15 11:46:44 by tsurma            #+#    #+#              #
#    Updated: 2024/07/05 17:10:06 by tsurma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra
NAME = libft.a

SRC = ft_atoi.c\
ft_bzero.c\
ft_calloc.c\
ft_free_matrix.c\
ft_isalnum.c\
ft_isalpha.c\
ft_isascii.c\
ft_isdigit.c\
ft_isprint.c\
ft_isspace.c\
ft_itoa.c\
ft_memchr.c\
ft_memcmp.c\
ft_memcpy.c\
ft_memmove.c\
ft_memset.c\
ft_putchar_fd.c\
ft_putendl_fd.c\
ft_putnbr_fd.c\
ft_putstr_fd.c\
ft_split.c\
ft_strchr.c\
ft_strdup.c\
ft_striteri.c\
ft_strjoin.c\
ft_strlcat.c\
ft_strlcpy.c\
ft_strlen.c\
ft_strmapi.c\
ft_strncmp.c\
ft_strnstr.c\
ft_strrchr.c\
ft_strtrim.c\
ft_trimspace.c\
ft_substr.c\
ft_tolower.c\
ft_toupper.c\
ft_printf.c\
ft_printf_h.c\
get_next_line.c\
ft_noendl.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

.SILENT $(NAME) : $(OBJ)
	@ar -cq $(NAME) $^

fclean : clean
	@-rm -f $(NAME)

clean :
	@rm -f $(OBJ)

re : fclean all

.PHONY : clean fclean re all
