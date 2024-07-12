/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:26:27 by tsurma            #+#    #+#             */
/*   Updated: 2024/07/12 15:33:47 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	update_player_direction(t_map *map)
{
	map->pdx = cos(map->pa);
	map->pdy = sin(map->pa);
	map->plane_x = -0.66 * map->pdy;
	map->plane_y = 0.66 * map->pdx;
}

void	update_player_position(t_map *map, int d, int sideways)
{
	double	f_move_speed;
	double	lat_move_speed;
	double	forward_px;
	double	forward_py;
	double	sdways_px;
	double	sdways_py;
	int		forward_map_x;
	int		forward_map_y;
	int		sdways_map_x;
	int		sdways_map_y;

	if (d == 1)
		f_move_speed = MOVE_SPEED_FORWARD;
	else if (d == -1)
		f_move_speed = -MOVE_SPEED_BACKWARD;
	else
		f_move_speed = 0;
	lat_move_speed = MOVE_SPEED_FORWARD * LATERAL_MOVE_SPEED_FACTOR;
	forward_px = map->px + map->pdx * f_move_speed;
	forward_py = map->py + map->pdy * f_move_speed;
	sdways_px = map->px + map->plane_x * lat_move_speed * sideways;
	sdways_py = map->py + map->plane_y * lat_move_speed * sideways;
	forward_map_x = (int)(forward_px / TEXTURE_SIZE);
	forward_map_y = (int)(forward_py / TEXTURE_SIZE);
	sdways_map_x = (int)(sdways_px / TEXTURE_SIZE);
	sdways_map_y = (int)(sdways_py / TEXTURE_SIZE);
	if (map->mapp[forward_map_y * map->mapx + forward_map_x] == 1)
	{
		if (map->mapp[sdways_map_y * map->mapx + sdways_map_x] != 1)
		{
			map->px = sdways_px;
			map->py = sdways_py;
		}
	}
	else
	{
		map->px = forward_px;
		map->py = forward_py;
		if (sideways != 0 && map->mapp[sdways_map_y * map->mapx
			+ sdways_map_x] != 1)
		{
			map->px = sdways_px;
			map->py = sdways_py;
		}
	}
	printf("New player position: px = %f, py = %f\n", map->px, map->py);
}

void	keyhook(void *param)
{
	t_map	*map;

	map = (t_map *)param;
	if (mlx_is_key_down(map->mlx, MLX_KEY_W))
		update_player_position(map, 1, 0);
	if (mlx_is_key_down(map->mlx, MLX_KEY_S))
		update_player_position(map, -1, 0);
	if (mlx_is_key_down(map->mlx, MLX_KEY_A))
		update_player_position(map, 1, -1);
	if (mlx_is_key_down(map->mlx, MLX_KEY_D))
		update_player_position(map, 1, 1);
	if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
	{
		map->pa -= TURN_SPEED;
		if (map->pa < 0)
			map->pa += 2 * PI;
		update_player_direction(map);
		printf("Turned left. New direction vectors: pdx = %f, pdy = %f\n",
			map->pdx, map->pdy);
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
	{
		map->pa += TURN_SPEED;
		if (map->pa > 2 * PI)
			map->pa -= 2 * PI;
		update_player_direction(map);
		printf("Turned right. New direction vectors: pdx = %f, pdy = %f\n",
			map->pdx, map->pdy);
	}
	ft_bzero(map->p_layer->pixels, (map->p_layer->height * map->p_layer->width)
		* 4);
	raycaster(map);
}

void	update_view(t_map *map, double delta_x, double delta_y)
{
	const double	damping_factor = 0.002;

	map->pa += delta_x * damping_factor;
	map->pa = fmod(map->pa, 2 * PI);
	map->view_z += delta_y * damping_factor * 50;
	map->view_z = fmin(fmax(map->view_z, SOME_MIN_HEIGHT), SOME_MAX_HEIGHT);
	update_player_direction(map);
}

void	mouse_hook(double xpos, double ypos, void *param)
{
	static double	last_x = SCREEN_WIDTH / 2;
	static double	last_y = SCREEN_HEIGHT / 2;
	t_map			*map;
	double			delta_x;
	double			delta_y;

	map = (t_map *)param;
	delta_x = xpos - last_x;
	delta_y = ypos - last_y;
	update_view(map, delta_x, delta_y);
	if (fabs(delta_x) > 1 || fabs(delta_y) > 1)
	{
		mlx_set_mouse_pos(map->mlx, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		last_x = SCREEN_WIDTH / 2;
		last_y = SCREEN_HEIGHT / 2;
	}
	else
	{
		last_x = xpos;
		last_y = ypos;
	}
}
