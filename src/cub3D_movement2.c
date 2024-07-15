/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_movement2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olobresh <olobresh@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:56:45 by olobresh          #+#    #+#             */
/*   Updated: 2024/07/11 15:56:47 by olobresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	handle_turning_keys(t_map *map)
{
	if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
	{
		map->pa -= TURN_SPEED;
		if (map->pa < 0)
			map->pa += 2 * PI;
		update_player_direction(map);
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
	{
		map->pa += TURN_SPEED;
		if (map->pa > 2 * PI)
			map->pa -= 2 * PI;
		update_player_direction(map);
	}
}

void	keyhook(void *param)
{
	t_map	*map;

	map = (t_map *)param;
	handle_movement_keys(map);
	handle_turning_keys(map);
	ft_bzero(map->p_layer->pixels, (map->p_layer->height * map->p_layer->width)
		* 4);
	raycaster(map);
	draw_player(map);
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
