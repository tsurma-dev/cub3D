/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:02:26 by tsurma            #+#    #+#             */
/*   Updated: 2024/07/01 17:52:15 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include "../libft/libft.h"
# include "../../MLX42/include/MLX42/MLX42.h"

# define PI 3.1415
# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define TURN_SPEED 0.1
# define MOVE_SPEED 2

typedef enum parserr
{
	NOLINE,
	RGB_OOR,
	UNEX_CHAR
}	t_parserr;

typedef enum BOOL
{
	FALSE,
	TRUE
}	t_BOOL;

typedef struct cub3D_map
{
	void		*mlx;
	mlx_image_t	*no_i;
	mlx_image_t	*so_i;
	mlx_image_t	*we_i;
	mlx_image_t	*ea_i;
	mlx_image_t	*bg;
	mlx_image_t	*test;
	float		px;
	float		py;
	float		pdx;
	float		pdy;
	float		pa;
	int			mapx;
	int			mapy;
	int			*mapp;
	int			colour_c;
	int			colour_f;
}	t_map;

int		parser(char *path, t_map *map);
int		rgb_extractor(char *line);
void	window(t_map *map);
void	fill_background(t_map *map);
void	fill_test(t_map *map);
void	fill_wall(t_map *map);
void	keyhook(mlx_key_data_t keydata, void *ma);
void	draw_map(t_map *map);
void	raycaster(t_map *map);
void	draw_line(t_map	*map, int beginx, int beginy, int endx, int endy);

#endif
