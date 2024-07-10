/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:02:26 by tsurma            #+#    #+#             */
/*   Updated: 2024/07/10 11:57:59 by tsurma           ###   ########.fr       */
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
#include <float.h>
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

# define PI 3.1415
# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480
# define TURN_SPEED 0.05
# define MOVE_SPEED 2
# define MOVE_SPEED_FORWARD 5.0
# define MOVE_SPEED_BACKWARD 2.5
# define TEXTURE_SIZE 64
# define MLX_KEY_W 87
# define MLX_KEY_S 83
# define MLX_KEY_A 65
# define MLX_KEY_D 68
# define MLX_KEY_ESCAPE 256
# define LATERAL_MOVE_SPEED_FACTOR 1

# define N 78
# define S 83
# define E 69
# define W 87
# define FLOOR 0
# define WALL 1
# define NOTHING -1

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
	mlx_texture_t *no_t;
	mlx_texture_t *so_t;
	mlx_texture_t *we_t;
	mlx_texture_t *ea_t;
	mlx_image_t	*bg;
	mlx_image_t	*p_layer;
	mlx_image_t	*test;
	double px, py, pa;
	double pdx, pdy;
	double plane_x, plane_y;
	int			mapx;
	int			mapy;
	int			*mapp;
	int			colour_c;
	int			colour_f;
}	t_map;


int		parser(char *path, t_map *map);
void	parser_exit(char **file, t_map *map, int err_nr, const char *message);
int		rgb_extractor(char *line);
void	window(t_map *map);
void	fill_background(t_map *map);
void	fill_test(t_map *map);
void	fill_wall(t_map *map);
void	keyhook(void *param);
void	draw_map(t_map *map);
void	raycaster(t_map *map);
void update_player_position(t_map *map, int d, int sideways);
unsigned int	tex_to_rgb(mlx_texture_t *tex, int x, int y);
void	reverse_texture(mlx_texture_t *tex);



char	**ft_pointjoin(char **dest, char *src);
int	parse_line(t_map *map, char *line);
int	parse_map(t_map *map, char **lines);
mlx_texture_t	*path_extractor(char *line);
int	get_map_dimensions(t_map *map, char **lines);
void check_ext(const char *filename);
void update_player_direction(t_map *map);

void initiate_cub3dmap(t_map *map);

int find_player_position(t_map *map, int *player_x, int *player_y);
void	flood_fill(int x, int y, int *tiles, t_map *map);
int check_valid_map(t_map *map, int player_x, int player_y);






#endif
