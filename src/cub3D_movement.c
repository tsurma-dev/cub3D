/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:26:27 by tsurma            #+#    #+#             */
/*   Updated: 2024/07/12 17:06:49 by tsurma           ###   ########.fr       */
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

void calculate_move_speeds(t_player_movement *movement, int d)
{
    if (d == 1)
        movement->f_move_speed = MOVE_SPEED_FORWARD;
    else if (d == -1)
        movement->f_move_speed = -MOVE_SPEED_BACKWARD;
    else
        movement->f_move_speed = 0;
    movement->lat_move_speed = MOVE_SPEED_FORWARD * LATERAL_MOVE_SPEED_FACTOR;
}

void calculate_positions(t_map *map, t_player_movement *movement, int sideways)
{
    movement->forward_px = map->px + map->pdx * movement->f_move_speed;
    movement->forward_py = map->py + map->pdy * movement->f_move_speed;
    movement->sdways_px = map->px + map->plane_x * movement->lat_move_speed * sideways;
    movement->sdways_py = map->py + map->plane_y * movement->lat_move_speed * sideways;

    movement->forward_map_x = (int)(movement->forward_px);
    movement->forward_map_y = (int)(movement->forward_py);
    movement->sdways_map_x = (int)(movement->sdways_px);
    movement->sdways_map_y = (int)(movement->sdways_py);
}

void update_player_position(t_map *map, int d, int sideways)
{
    t_player_movement movement;

    calculate_move_speeds(&movement, d);
    calculate_positions(map, &movement, sideways);

    if (map->mapp[movement.forward_map_y * map->mapx + movement.forward_map_x] == 1)
	{
        if (map->mapp[movement.sdways_map_y * map->mapx + movement.sdways_map_x] != 1)
		{
            map->px = movement.sdways_px;
            map->py = movement.sdways_py;
        }
    }
	else
	{
        map->px = movement.forward_px;
        map->py = movement.forward_py;
        if (sideways != 0 && map->mapp[movement.sdways_map_y * map->mapx + movement.sdways_map_x] != 1)
		{
            map->px = movement.sdways_px;
            map->py = movement.sdways_py;
        }
    }
}

void	handle_movement_keys(t_map *map)
{
	if (mlx_is_key_down(map->mlx, MLX_KEY_W))
		update_player_position(map, 1, 0);
	if (mlx_is_key_down(map->mlx, MLX_KEY_S))
		update_player_position(map, -1, 0);
	if (mlx_is_key_down(map->mlx, MLX_KEY_A))
		update_player_position(map, 1, -1);
	if (mlx_is_key_down(map->mlx, MLX_KEY_D))
		update_player_position(map, 1, 1);
}


