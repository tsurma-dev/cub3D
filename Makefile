# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/28 15:37:07 by tsurma            #+#    #+#              #
#    Updated: 2024/06/28 15:43:34 by tsurma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc
CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address
NAME = cub3D
MLXFLAGS = -Iinclude -ldl -lglfw -pthread -lm
MAKEFLAGS = --no-print-directory

SRC = 	src/cub3D.c\
		src/parser.c


OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ)
	@ make -C libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) libft/libft.a ../MLX42/build/libmlx42.a $(MLXFLAGS)

clean :
	make fclean -C libft
	@rm -f $(OBJ)

fclean : clean
	@rm -f $(NAME)

re : fclean all


.PHONY : clean fclean re all
