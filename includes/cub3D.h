/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:02:26 by tsurma            #+#    #+#             */
/*   Updated: 2024/07/03 22:16:38 by tsurma           ###   ########.fr       */
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
# include "../MLX42/include/MLX42/MLX42.h"

# define PI 3.1415926535
# define PI2 PI / 2
# define PI3 3*PI / 2
# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define MOVE_SPEED 1
# define DR 0.0174533
# define SQUARE_SIZE 64
# define GREEN 0xff00ff
# define BLUE 0x00ffff
# define FOV 100
# define DARKBLUE 0x00d7ff


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

typedef struct cub3D_ray
{
	float	ra;
	float	rx;
	float	ry;
	float	xo;
	float	yo;
	float	atan;
	float	dist;
	int		r;
	int		mx;
	int		my;
	int		mp;
	int		dof;
}	t_ray;

/*
mlx = pointer to mlx-instance
no_i - ea_i = images for each side to be displayed
bg = background image
test = current player image
px & py = player x and y position
pdx & pdy = player x and y direction
pa = player angle (0 - 2*PI)
mapx & mapy = map dimensions
mapp = pointer to map as int array
colour_c & _f = colours for ceiling and floor
*/
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
void	draw_line(t_map	*map, float beginx, float beginy, float endx, float endy, int col);
void	vertical_ray(t_map *map, t_ray *r, float offset);
void	horizontal_ray(t_map *map, t_ray *r, float offset);
float	distance(float ax, float ay, float bx, float by);
void	drawwall(t_map *map, int x, int y, int yend, int color);

#endif
