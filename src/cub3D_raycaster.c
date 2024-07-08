/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_raycaster.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:47:22 by tsurma            #+#    #+#             */
/*   Updated: 2024/07/08 13:57:49 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	raycaster(t_map *map)
{
	int		x;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	unsigned int		color;
	int		y;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		ray_dir_x = map->pdx + map->plane_x * camera_x;
		ray_dir_y = map->pdy + map->plane_y * camera_x;
		map_x = (int)(map->px / TEXTURE_SIZE);
		map_y = (int)(map->py / TEXTURE_SIZE);
		delta_dist_x = fabs(1 / ray_dir_x);
		delta_dist_y = fabs(1 / ray_dir_y);
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (map->px / TEXTURE_SIZE - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - map->px / TEXTURE_SIZE) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (map->py / TEXTURE_SIZE - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - map->py / TEXTURE_SIZE) * delta_dist_y;
		}
		hit = 0;
		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (map_x >= 0 && map_x < map->mapx && map_y >= 0
				&& map_y < map->mapy && map->mapp[map_y * map->mapx
					+ map_x] == 1)
				hit = 1;
		}
		if (side == 0)
			perp_wall_dist = (map_x - map->px / TEXTURE_SIZE + (1 - step_x) / 2)
				/ ray_dir_x;
		else
			perp_wall_dist = (map_y - map->py / TEXTURE_SIZE + (1 - step_y) / 2)
				/ ray_dir_y;
		line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);
		draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_end >= SCREEN_HEIGHT)
			draw_end = SCREEN_HEIGHT - 1;
		if (side == 1)
			color = 0x8888ff;
		else
			color = 0x1111ff;
		y = draw_start;
		while (y < draw_end)
		{
			color = (*(int *)(map->no_t->pixels)) >> 1;
			mlx_put_pixel(map->p_layer, x, y, color);
			y++;
		}
		x++;
	}
}

int	rgb_to_int(int r, int g, int b)
{
	int	rgb;

	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	rgb = (r << (3 * 8)) + (g << (2 * 8)) + (b << (1 * 8));
	return (rgb);
}
