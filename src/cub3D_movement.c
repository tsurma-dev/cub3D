/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:26:27 by tsurma            #+#    #+#             */
/*   Updated: 2024/07/08 11:54:41 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	update_player_direction(t_map *map)
{
	map->pdx = cos(map->pa);
	map->pdy = sin(map->pa);
	map->plane_x = -0.66 * map->pdy;
	map->plane_y = 0.66 * map->pdx;
	printf("Updated dir vectors: pdx = %f, pdy = %f\n", map->pdx, map->pdy);
}

void update_player_position(t_map *map, int d, int sideways)
{
    double	move_speed;
    double	new_px;
	double	new_py;
    int	new_map_x;
	int	new_map_y;

    if (d == 1)
	{
        move_speed = MOVE_SPEED_FORWARD;
    }
	else
	{
        move_speed = -MOVE_SPEED_BACKWARD;
    }
    if (!sideways)
	{
        new_px = map->px + map->pdx * move_speed;
        new_py = map->py + map->pdy * move_speed;
    }
	else
	{
        new_px = map->px + map->plane_x * move_speed * sideways;
        new_py = map->py + map->plane_y * move_speed * sideways;
    }
    new_map_x = (int)(new_px / TEXTURE_SIZE);
    new_map_y = (int)(new_py / TEXTURE_SIZE);

    if (new_map_x >= 0 && new_map_x < map->mapx && new_map_y >= 0 && new_map_y < map->mapy &&
        map->mapp[new_map_y * map->mapx + new_map_x] != 1)
	{
        map->px = new_px;
        map->py = new_py;
        printf("Moved to (%f, %f)\n", map->px, map->py);
    }
	else
	{
        printf("Hit a wall at (%f, %f) in map cell (%d, %d)\n", new_px, new_py, new_map_x, new_map_y);
    }
}

void keyhook(void *param)
{
    t_map *map = (t_map *)param;

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
        printf("Turned left. New direction vectors: pdx = %f, pdy = %f\n", map->pdx, map->pdy);
    }
    if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
    {
        map->pa += TURN_SPEED;
        if (map->pa > 2 * PI)
            map->pa -= 2 * PI;
        update_player_direction(map);
        printf("Turned right. New direction vectors: pdx = %f, pdy = %f\n", map->pdx, map->pdy);
    }

    ft_bzero(map->p_layer->pixels, (map->p_layer->height * map->p_layer->width) * 4);
    raycaster(map);
    if (mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(map->mlx);
}

