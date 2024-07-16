# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/28 15:37:07 by tsurma            #+#    #+#              #
#    Updated: 2024/07/16 14:18:29 by tsurma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address
NAME = cub3D
LIBMLX = ./MLX42
MLXFLAGS = -Iinclude -I$(LIBMLX)/include -ldl -lglfw -pthread -lm
MAKEFLAGS = --no-print-directory

SRC = src/cub3D.c \
      src/parser.c src/parsing_utils.c src/parsing_utils2.c\
	  src/cub3D_movement.c src/cub3D_mlx_utils.c src/cub3D_raycaster.c\
	  src/cub3D_raycaster2.c src/parsing_utils3.c src/parsing_utils4.c\
	  src/cub3D_utils.c src/cub3D_minimap.c src/cub3D_movement2.c\
	  src/cub3D_borders.c

OBJ = $(SRC:.c=.o)

all: $(LIBMLX) $(NAME)

$(LIBMLX):
	if [ ! -d "$(LIBMLX)" ]; then \
	git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX); \
	cmake -S $(LIBMLX) -B $(LIBMLX)/build -DDEBUG=1 && make -C $(LIBMLX)/build -j4; \
	fi

$(NAME): $(OBJ) $(LIBMLX) libft/libft.a
	@make -C libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) libft/libft.a $(LIBMLX)/build/libmlx42.a $(MLXFLAGS)

libft/libft.a:
	@make -C libft

clean:
	@make clean -C libft
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C libft
	@rm -rf $(LIBMLX)
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all




