/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:02:26 by tsurma            #+#    #+#             */
/*   Updated: 2024/07/17 13:18:59 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define PI 3.1415
# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480
# define TURN_SPEED 0.05
# define MOVE_SPEED
# define MOVE_SPEED_FORWARD 0.15
# define MOVE_SPEED_BACKWARD 0.1
# define TEXTURE_SIZE 64
# define LATERAL_MOVE_SPEED_FACTOR 1
# define SOME_MAX_HEIGHT 1.0
# define SOME_MIN_HEIGHT -1.0
# define SOME_MAX_PITCH 0.9
# define SOME_MIN_PITCH -0.9

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
}					t_parserr;

typedef enum BOOL
{
	FALSE,
	TRUE
}					t_BOOL;

typedef struct cub3D_map
{
	void			*mlx;
	mlx_texture_t	*no_t;
	mlx_texture_t	*so_t;
	mlx_texture_t	*we_t;
	mlx_texture_t	*ea_t;
	mlx_image_t		*wall;
	mlx_image_t		*bg;
	mlx_image_t		*p_layer;
	mlx_image_t		*m_layer;
	double			px;
	double			py;
	double			pa;
	double			pdx;
	double			pdy;
	double			plane_x;
	double			plane_y;
	int				mapx;
	int				minx;
	int				miny;
	int				cube;
	int				mapy;
	int				*mapp;
	int				colour_c;
	int				colour_f;
	double			view_z;
	double			pitch;
}					t_map;

typedef struct player_movement
{
	double			f_move_speed;
	double			lat_move_speed;
	double			forward_px;
	double			forward_py;
	double			sdways_px;
	double			sdways_py;
	int				forward_map_x;
	int				forward_map_y;
	int				sdways_map_x;
	int				sdways_map_y;
}					t_player_movement;

typedef struct cub3D_ray
{
	mlx_texture_t	*tex;
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			side_dist_x;
	double			side_dist_y;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	double			perp_wall_dist;
	int				line_height;
	int				draw_start;
	int				draw_end;
	unsigned int	color;
	double			wallx;
	int				texx;
	int				texy;
	double			step;
	double			tex_pos;
	int				x;
	int				y;
}					t_ray;

// Parsing
int					parser(char *path, t_map *map);
void				parser_exit(char **file, t_map *map, int err_nr,
						const char *message);
void				check_ext(const char *filename);
int					parse_map(t_map *map, char **lines);
int					parse_line(t_map *map, char *line);
char				**ft_pointjoin(char **dest, char *src);
int					check_valid_map(t_map *map, int player_x, int player_y);
int					valid_map(int *map, int width, int height);
int					valid_char(char c);
mlx_texture_t		*path_extractor(char *line);
int					rgb_extractor(char *line);
int					get_map_dimensions(t_map *map, char **lines);
int					check_player_surroundings(t_map *map, int player_x,
						int player_y);
int					process_map_lines(t_map *map, char **lines);
void				trim_whitespace(char **line);
int					process_map_line(t_map *map, char *line, int y);
// mlx
void				window(t_map *map);
void				load_images_tex(t_map *map);
void				delete_tex_img(t_map *map);
void				reverse_texture(mlx_texture_t *tex);
void				mouse_hook(double xpos, double ypos, void *param);
void				keyhook(void *param);
void				keyhook2(mlx_key_data_t keydata, void *ma);
void				fill_background(t_map *map);
void				handle_movement_keys(t_map *map);
void				update_player_direction(t_map *map);
void				initiate_cub3dmap(t_map *map);
void				draw_map(t_map *map);
void				draw_player(t_map *map);
// raycasting
void				raycaster(t_map *map);
void				update_player_position(t_map *map, int d, int sideways);
unsigned int		tex_to_rgb(mlx_texture_t *tex, int x, int y);
mlx_texture_t		*select_texture(t_map *map, int side, double rdx,
						double rdy);
void				find_tex_hit(t_ray *r, float px, float py);
void				find_coll(t_map *map, t_ray *r);
void				draw_column(t_map *map, t_ray *r);
void				set_step_dist(t_map *map, t_ray *r);
void				set_draw_pos(t_ray *r);
int					find_player_position(t_map *map, int *player_x,
						int *player_y);
int					borders(char **map);
int					crawler(char **map, int x, int y);
int					ft_is_edge(char **map, int x, int y);
int					ft_strchr_i(const char *s, int c);
int					ft_strrchr_i(const char *s, int c);

#endif
